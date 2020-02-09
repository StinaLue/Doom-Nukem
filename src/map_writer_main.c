/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_writer_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:54:01 by afonck            #+#    #+#             */
/*   Updated: 2020/02/09 03:03:27 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "errno.h"
#include "sys/stat.h"

int		write_enemies_info(int fd, t_enemy_info *enemies_info, \
		int num_enemies_file)
{
	int num_enemies;

	num_enemies = 0;
	while (num_enemies < num_enemies_file)
	{
		if (write(fd, &enemies_info[num_enemies].enemy_spawn.x, sizeof(int)) \
				!= sizeof(int))
			return (error_return_map("error writing enemy spawn\n", NULL, fd));
		if (write(fd, &enemies_info[num_enemies].enemy_spawn.y, sizeof(int)) \
				!= sizeof(int))
			return (error_return_map("error writing enemy spawn\n", NULL, fd));
		if (write(fd, &enemies_info[num_enemies].which_enemy, sizeof(int)) \
				!= sizeof(int))
			return (error_return_map("error writing enemy ID\n", NULL, fd));
		num_enemies++;
	}
	return (0);
}

int		write_signature_and_spawn(int fd, t_map *map)
{
	if (write(fd, "DOOM", 4) != 4)
		return (error_return_map("Error writing file signature\n", NULL, fd));
	if (write(fd, map->name, ft_strlen(map->name)) \
			!= (ssize_t)ft_strlen(map->name))
		return (error_return_map("Error writing map name\n", NULL, fd));
	if (write(fd, "spawn", 5) != 5)
		return (error_return_map("Error writing playerspawn mark\n", NULL, fd));
	if (write(fd, &map->player_spawn.x, sizeof(int)) != sizeof(int))
		return (error_return_map("Error writing player spawn\n", NULL, fd));
	if (write(fd, &map->player_spawn.y, sizeof(int)) != sizeof(int))
		return (error_return_map("Error writing player spawn\n", NULL, fd));
	return (0);
}

int		write_sectors_and_enemies(int fd, t_map *map)
{
	if (write(fd, "sectors", 7) != 7)
		return (error_return_map("Error writing sectors mark\n", NULL, fd));
	if (write(fd, &map->num_sectors, sizeof(int)) != sizeof(int))
		return (error_return_map("Error writing num sectors\n", NULL, fd));
	if (write_sectors(fd, map->sector_head, map->num_sectors) != 0)
		return (error_return("Error writing sectors\n", NULL));
	if (write(fd, "enemies", 7) != 7)
		return (error_return_map("Error writing enemies mark\n", NULL, fd));
	if (write(fd, &map->num_enemies, sizeof(int)) != sizeof(int))
		return (error_return_map("Error writing num enemies\n", NULL, fd));
	if (write_enemies_info(fd, map->enemy_info, map->num_enemies) != 0)
		return (error_return("Error writing enemies info\n", NULL));
	return (0);
}

int		write_music_and_weapons(int fd, t_map *map)
{
	if (write(fd, "music", 5) != 5)
		return (error_return_map("Error writing music mark\n", NULL, fd));
	if (write(fd, &map->which_music, sizeof(int)) != sizeof(int))
		return (error_return_map("Error writing music choice\n", NULL, fd));
	if (write(fd, "weapons", 7) != 7)
		return (error_return_map("Error writing weapons mark\n", NULL, fd));
	if (write(fd, &map->weapon_choice, sizeof(int)) != sizeof(int))
		return (error_return_map("Error writing weapon choice\n", NULL, fd));
	return (0);
}

int		write_map(t_map *map)
{
	int		fd;
	char	full_path[22];

	prepend_str(".maps/", map->name, full_path, 22);
	if (map == NULL)
		return (error_return("map is NULL\n", NULL));
	if (access(full_path, 0) != 0)
		mkdir(".maps", 0700);
	if ((fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC | O_NOFOLLOW, \
			S_IRUSR | S_IWUSR)) == -1)
		return (error_return("error opening: %s\n", strerror(errno)));
	if (write_signature_and_spawn(fd, map) != 0)
		return (1);
	if (write_sectors_and_enemies(fd, map) != 0)
		return (1);
	if (write_music_and_weapons(fd, map) != 0)
		return (1);
	if (write(fd, "END", 3) != 3)
		return (error_return_map("Error writing END mark\n", NULL, fd));
	if (close(fd) != 0)
		return (error_return("Error closing fd\n", NULL));
	return (0);
}
