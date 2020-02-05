/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:39:25 by afonck            #+#    #+#             */
/*   Updated: 2020/02/05 12:42:30 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "errno.h"

int		read_walls(int fd, t_wall_node **wall_head, int nb_walls_file)
{
	int nb_walls;
    t_wall_node *current_wall;

	nb_walls = 0;
    current_wall = NULL;
	while (nb_walls < nb_walls_file)
	{
        if ((current_wall = insert_wall_node(wall_head)) == NULL)
            return (error_return("error inserting wall node\n", NULL));
        if (read(fd, &current_wall->start.x, sizeof(double)) != sizeof(double))
			return (error_return("error reading start wall\n", NULL));
		if (read(fd, &current_wall->start.y, sizeof(double)) != sizeof(double))
			return (error_return("error reading start wall\n", NULL));
		if (read(fd, &current_wall->end.x, sizeof(double)) != sizeof(double))
			return (error_return("error reading end wall\n", NULL));
		if (read(fd, &current_wall->end.y, sizeof(double)) != sizeof(double))
			return (error_return("error reading end wall\n", NULL));
		if (read(fd, &current_wall->color, sizeof(int)) != sizeof(int))
			return (error_return("error reading color wall\n", NULL));
		if (read(fd, &current_wall->tex_index, sizeof(int)) != sizeof(int))
			return (error_return("error reading tex index wall\n", NULL));
		if (read(fd, &current_wall->sector_index, sizeof(int)) != sizeof(int))
			return (error_return("error reading sector index wall\n", NULL));
		if (read(fd, &current_wall->wall_type, sizeof(int)) != sizeof(int))
			return (error_return("error reading wall type wall\n", NULL));
		if (read(fd, &current_wall->type_color, sizeof(int)) != sizeof(int))
			return (error_return("error reading type color wall\n", NULL));
		if (read(fd, &current_wall->length, sizeof(int)) != sizeof(int))
			return (error_return("error reading length wall\n", NULL));
		nb_walls++;
	}
	//if (nb_walls != nb_walls_file)
	//	return (error_return("nb walls in file different than nb walls\n", NULL));
	return (0);
}

int		read_sector(int fd, t_sector_node *sector)
{
	if (read(fd, &sector->sector_center.x, sizeof(double)) != sizeof(double))
		return (error_return("error reading sector center\n", NULL));
	if (read(fd, &sector->sector_center.y, sizeof(double)) != sizeof(double))
		return (error_return("error reading sector center\n", NULL));
	if (read(fd, &sector->floor_height, sizeof(double)) != sizeof(double))
		return (error_return("error reading floor height\n", NULL));
	if (read(fd, &sector->ceiling_height, sizeof(double)) != sizeof(double))
		return (error_return("error reading ceiling height\n", NULL));
	if (read(fd, &sector->wall_num, sizeof(int)) != sizeof(int))
		return (error_return("error reading wall num\n", NULL));
	if (read_walls(fd, &sector->wall_head, sector->wall_num) != 0)
		return (error_return("error reading walls\n", NULL));
	return (0);
}

int		read_sectors(int fd, t_sector_node **sector_head, int num_sectors_file)
{
	int num_sectors;
    t_sector_node *current_sector;

	num_sectors = 0;
    current_sector = NULL;
    while (num_sectors < num_sectors_file)
	{
        if ((current_sector = add_sector_node(sector_head)) == NULL)
            return (error_return("error during add sector node\n", NULL));
		if (read_sector(fd, current_sector) != 0)
			return (1);
		num_sectors++;
	}
	if (num_sectors != num_sectors_file)
		return (error_return("differing nb sectors in file\n", NULL));
	return (0);
}

int		read_enemies_info(int fd, t_enemy_info **enemies_info, int num_enemies_file)
{
	int num_enemies;

	num_enemies = 0;
    if (num_enemies_file >= 1)
    {
        if ((*enemies_info = malloc(sizeof(t_enemy_info) * num_enemies_file)) == NULL)
            return (error_return("error malloc enemies info\n", NULL));
        while (num_enemies < num_enemies_file)
	    {
		    if (read(fd, &(*enemies_info)[num_enemies].enemy_spawn.x, sizeof(int)) != sizeof(int))
		    	return (error_return("error reading enemy spawn\n", NULL));
		    if (read(fd, &(*enemies_info)[num_enemies].enemy_spawn.y, sizeof(int)) != sizeof(int))
			    return (error_return("error reading enemy spawn\n", NULL));
    		if (read(fd, &(*enemies_info)[num_enemies].which_enemy, sizeof(int)) != sizeof(int))
			    return (error_return("error reading enemy ID\n", NULL));
	    	num_enemies++;
	    }
    }
	return (0);
}

int		read_map(const char *path, t_map *map)
{
	int fd;
    char buf[8];
	char full_path[22];

    buf[7] = '\0';
	//if (map != NULL || path == NULL)
	if (path == NULL)
		return (error_return("map is not NULL or path is NULL\n", NULL));
	prepend_str(".maps/", path, full_path, 22);
	//if ((fd = open(path, O_RDONLY | O_NOFOLLOW)) == -1)
	if ((fd = open(full_path, O_RDONLY | O_NOFOLLOW)) == -1)
		return (error_return("open error %s\n", strerror(errno)));

	if (read(fd, buf, 4) != 4 || ft_strncmp(buf, "DOOM", 4) != 0)
		return (error_return("Error reading file signature\n", NULL));
	if (read(fd, map->name, ft_strlen(path)) != (ssize_t)ft_strlen(path) || ft_strncmp(map->name, path, ft_strlen(path)) != 0)
		return (error_return("Error reading map name\n", NULL));

	if (read(fd, buf, 5) != 5 || ft_strncmp(buf, "spawn", 5) != 0)
		return (error_return("Error reading spawn mark\n", NULL));
	if (read(fd, &map->player_spawn.x, sizeof(int)) != sizeof(int))
		return (error_return("Error reading player spawn\n", NULL));
	if (read(fd, &map->player_spawn.y, sizeof(int)) != sizeof(int))
		return (error_return("Error reading player spawn\n", NULL));

	if (read(fd, buf, 7) != 7 || ft_strncmp(buf, "sectors", 7) != 0)
		return (error_return("Error reading sectors mark\n", NULL));
	if (read(fd, &map->num_sectors, sizeof(int)) != sizeof(int))
		return (error_return("Error reading num sectors\n", NULL));
	if (read_sectors(fd, &map->sector_head, map->num_sectors) != 0)
		return (error_return("Error reading sectors\n", NULL));

	if (read(fd, buf, 7) != 7 || ft_strncmp(buf, "enemies", 7) != 0)
		return (error_return("Error reading enemies mark\n", NULL));
	if (read(fd, &map->num_enemies, sizeof(int)) != sizeof(int))
		return (error_return("Error reading num enemies\n", NULL));
	if (read_enemies_info(fd, &map->enemy_info, map->num_enemies) != 0)
		return (error_return("Error reading enemies info\n", NULL));

	if (read(fd, buf, 3) != 3 || ft_strncmp(buf, "END", 3) != 0)
		return (error_return("Error reading END mark\n", NULL));
    if (close(fd) != 0)
        return (error_return("Error closing fd\n", NULL));
	return (0);
}