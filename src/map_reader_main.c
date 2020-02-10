/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:39:25 by afonck            #+#    #+#             */
/*   Updated: 2020/02/09 02:43:56 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "errno.h"

int		read_enemies_info(int fd, t_enemy_info **enemies_info, \
		int num_enemies_file)
{
	int num_enemies;

	num_enemies = 0;
	if (num_enemies_file >= 1)
	{
		if ((*enemies_info = malloc(sizeof(t_enemy_info) * num_enemies_file)) \
				== NULL)
			return (error_return_map("error malloc enemies info\n", NULL, fd));
		while (num_enemies < num_enemies_file)
		{
			if (read(fd, &(*enemies_info)[num_enemies].enemy_spawn.x, \
					sizeof(int)) != sizeof(int))
				return (error_return_map("error read enemy spawn\n", NULL, fd));
			if (read(fd, &(*enemies_info)[num_enemies].enemy_spawn.y, \
					sizeof(int)) != sizeof(int))
				return (error_return_map("error read enemy spawn\n", NULL, fd));
			if (read(fd, &(*enemies_info)[num_enemies].which_enemy, \
					sizeof(int)) != sizeof(int))
				return (error_return_map("error reading enemy ID\n", NULL, fd));
			num_enemies++;
		}
	}
	return (0);
}

int		read_signature_and_spawn(int fd, char *buf, t_map *map, \
		const char *path)
{
	if (read(fd, buf, 4) != 4 || ft_strncmp(buf, "DOOM", 4) != 0)
		return (error_return_map("Error reading file signature\n", NULL, fd));
	if (read(fd, map->name, ft_strlen(path)) != (ssize_t)ft_strlen(path) \
			|| ft_strncmp(map->name, path, ft_strlen(path)) != 0)
		return (error_return_map("Error reading map name\n", NULL, fd));
	if (read(fd, buf, 5) != 5 || ft_strncmp(buf, "spawn", 5) != 0)
		return (error_return_map("Error reading spawn mark\n", NULL, fd));
	if (read(fd, &map->player_spawn.x, sizeof(int)) != sizeof(int))
		return (error_return_map("Error reading player spawn\n", NULL, fd));
	if (read(fd, &map->player_spawn.y, sizeof(int)) != sizeof(int))
		return (error_return_map("Error reading player spawn\n", NULL, fd));
	return (0);
}

int		read_sectors_and_enemies(int fd, char *buf, t_map *map)
{
	if (read(fd, buf, 7) != 7 || ft_strncmp(buf, "sectors", 7) != 0)
		return (error_return_map("Error reading sectors mark\n", NULL, fd));
	if (read(fd, &map->num_sectors, sizeof(int)) != sizeof(int))
		return (error_return_map("Error reading num sectors\n", NULL, fd));
	if (read_sectors(fd, &map->sector_head, map->num_sectors) != 0)
		return (error_return("Error reading sectors\n", NULL));
	if (read(fd, buf, 7) != 7 || ft_strncmp(buf, "enemies", 7) != 0)
		return (error_return_map("Error reading enemies mark\n", NULL, fd));
	if (read(fd, &map->num_enemies, sizeof(int)) != sizeof(int))
		return (error_return_map("Error reading num enemies\n", NULL, fd));
	if (read_enemies_info(fd, &map->enemy_info, map->num_enemies) != 0)
		return (error_return("Error reading enemies info\n", NULL));
	return (0);
}

int		read_music_and_weapons(int fd, char *buf, t_map *map)
{
	if (read(fd, buf, 5) != 5 || ft_strncmp(buf, "music", 5) != 0)
		return (error_return_map("Error reading music mark\n", NULL, fd));
	if (read(fd, &map->which_music, sizeof(int)) != sizeof(int))
		return (error_return_map("Error reading music choice\n", NULL, fd));
	if (read(fd, buf, 7) != 7 || ft_strncmp(buf, "weapons", 7) != 0)
		return (error_return_map("Error reading weapons mark\n", NULL, fd));
	if (read(fd, &map->weapon_choice, sizeof(int)) != sizeof(int))
		return (error_return_map("Error reading weapon choice\n", NULL, fd));
	return (0);
}

int		read_map(const char *path, t_map *map)
{
	int		fd;
	char	buf[8];
	char	full_path[22];

	buf[7] = '\0';
	if (path == NULL)
		return (error_return("path is NULL\n", NULL));
	prepend_str(".maps/", path, full_path, 22);
	if ((fd = open(full_path, O_RDONLY | O_NOFOLLOW)) == -1)
		return (error_return("open error %s\n", strerror(errno)));
	if (read_signature_and_spawn(fd, buf, map, path) != 0)
		return (1);
	if (read_sectors_and_enemies(fd, buf, map) != 0)
		return (1);
	if (read_music_and_weapons(fd, buf, map) != 0)
		return (1);
	if (read(fd, buf, 3) != 3 || ft_strncmp(buf, "END", 3) != 0)
		return (error_return_map("Error reading END mark\n", NULL, fd));
	if (close(fd) != 0)
		return (error_return("Error closing fd\n", NULL));
	return (0);
}
