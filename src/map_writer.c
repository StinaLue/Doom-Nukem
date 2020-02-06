/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:54:01 by afonck            #+#    #+#             */
/*   Updated: 2020/02/06 17:24:11 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "errno.h"
#include "sys/stat.h"

int		write_walls(int fd, t_wall_node *wall_head, int nb_walls_file)
{
	int nb_walls;

	nb_walls = 0;
	if (wall_head == NULL)
		return (error_return("wall head is NULL\n", NULL));
	while (wall_head != NULL)
	{
		if (write(fd, &wall_head->start.x, sizeof(double)) != sizeof(double))
			return (error_return("error writing start wall\n", NULL));
		if (write(fd, &wall_head->start.y, sizeof(double)) != sizeof(double))
			return (error_return("error writing start wall\n", NULL));
		if (write(fd, &wall_head->end.x, sizeof(double)) != sizeof(double))
			return (error_return("error writing end wall\n", NULL));
		if (write(fd, &wall_head->end.y, sizeof(double)) != sizeof(double))
			return (error_return("error writing end wall\n", NULL));
		if (write(fd, &wall_head->color, sizeof(int)) != sizeof(int))
			return (error_return("error writing color wall\n", NULL));
		if (write(fd, &wall_head->tex_index, sizeof(int)) != sizeof(int))
			return (error_return("error writing tex index wall\n", NULL));
		if (write(fd, &wall_head->sector_index, sizeof(int)) != sizeof(int))
			return (error_return("error writing sector index wall\n", NULL));
		if (write(fd, &wall_head->wall_type, sizeof(int)) != sizeof(int))
			return (error_return("error writing wall type wall\n", NULL));
		if (write(fd, &wall_head->type_color, sizeof(int)) != sizeof(int))
			return (error_return("error writing type color wall\n", NULL));
		if (write(fd, &wall_head->length, sizeof(int)) != sizeof(int))
			return (error_return("error writing length wall\n", NULL));
		wall_head = wall_head->next;
		nb_walls++;
	}
	if (nb_walls != nb_walls_file)
		return (error_return("nb walls in file different than nb walls\n", NULL));
	return (0);
}

int		write_sector(int fd, t_sector_node *sector)
{
	if (write(fd, &sector->sector_center.x, sizeof(double)) != sizeof(double))
		return (error_return("error writing sector center\n", NULL));
	if (write(fd, &sector->sector_center.y, sizeof(double)) != sizeof(double))
		return (error_return("error writing sector center\n", NULL));
	if (write(fd, &sector->floor_height, sizeof(double)) != sizeof(double))
		return (error_return("error writing floor height\n", NULL));
	if (write(fd, &sector->ceiling_height, sizeof(double)) != sizeof(double))
		return (error_return("error writing ceiling height\n", NULL));
	if (write(fd, &sector->wall_num, sizeof(int)) != sizeof(int))
		return (error_return("error writing wall num\n", NULL));
	if (write_walls(fd, sector->wall_head, sector->wall_num) != 0)
		return (error_return("error writing walls\n", NULL));
	return (0);
}

int		write_sectors(int fd, t_sector_node *sector_head, int num_sectors_file)
{
	int num_sectors;

	num_sectors = 0;
	if (sector_head == NULL)
		return (error_return("sector head is NULL\n", NULL));
	while (sector_head != NULL)
	{
		if (write_sector(fd, sector_head) != 0)
			return (1);
		sector_head = sector_head->next;
		num_sectors++;
	}
	if (num_sectors != num_sectors_file)
		return (error_return("differing nb sectors in file\n", NULL));
	return (0);
}

int		write_enemies_info(int fd, t_enemy_info *enemies_info, int num_enemies_file)
{
	int num_enemies;

	num_enemies = 0;
	while (num_enemies < num_enemies_file)
	{
		if (write(fd, &enemies_info[num_enemies].enemy_spawn.x, sizeof(int)) != sizeof(int))
			return (error_return("error writing enemy spawn\n", NULL));
		if (write(fd, &enemies_info[num_enemies].enemy_spawn.y, sizeof(int)) != sizeof(int))
			return (error_return("error writing enemy spawn\n", NULL));
		if (write(fd, &enemies_info[num_enemies].which_enemy, sizeof(int)) != sizeof(int))
			return (error_return("error writing enemy ID\n", NULL));
		num_enemies++;
	}
	return (0);
}

void	prepend_str(const char *to_prepend, const char *str, char *new_str, int full_size)
{
	ft_bzero(new_str, full_size);
	ft_strncpy(new_str, to_prepend, ft_strlen(to_prepend));
	ft_strncat(new_str, str, ft_strlen(str));
	new_str[full_size - 1] = '\0';
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
	//if ((fd = open(map->name, O_CREAT | O_WRONLY | O_RDONLY)) == -1)
	//if ((fd = open(map->name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) == -1)
	//if ((fd = open(map->name, O_CREAT | O_WRONLY | O_TRUNC | O_NOFOLLOW, S_IRUSR)) == -1)
	if ((fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC | O_NOFOLLOW, S_IRUSR)) == -1)
		return (error_return("error opening: %s\n", strerror(errno)));
		//return (error_return("error opening %s\n", map->name));

	if (write(fd, "DOOM", 4) != 4)
		return (error_return("Error writing file signature\n", NULL));
	if (write(fd, map->name, ft_strlen(map->name)) != (ssize_t)ft_strlen(map->name))
		return (error_return("Error writing map name\n", NULL));

	if (write(fd, "spawn", 5) != 5)
		return (error_return("Error writing playerspawn mark\n", NULL));
	if (write(fd, &map->player_spawn.x, sizeof(int)) != sizeof(int))
		return (error_return("Error writing player spawn\n", NULL));
	if (write(fd, &map->player_spawn.y, sizeof(int)) != sizeof(int))
		return (error_return("Error writing player spawn\n", NULL));

	if (write(fd, "sectors", 7) != 7)
		return (error_return("Error writing sectors mark\n", NULL));
	if (write(fd, &map->num_sectors, sizeof(int)) != sizeof(int))
		return (error_return("Error writing num sectors\n", NULL));
	if (write_sectors(fd, map->sector_head, map->num_sectors) != 0)
		return (error_return("Error writing sectors\n", NULL));

	if (write(fd, "enemies", 7) != 7)
		return (error_return("Error writing enemies mark\n", NULL));
	if (write(fd, &map->num_enemies, sizeof(int)) != sizeof(int))
		return (error_return("Error writing num enemies\n", NULL));
	if (write_enemies_info(fd, map->enemy_info, map->num_enemies) != 0)
		return (error_return("Error writing enemies info\n", NULL));

	if (write(fd, "END", 3) != 3)
		return (error_return("Error writing END mark\n", NULL));
	if (close(fd) != 0)
		return (error_return("Error closing fd\n", NULL));
	return (0);
}
