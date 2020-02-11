/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_sectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 02:41:48 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 18:26:15 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int		read_wall(int fd, t_wall_node *wall)
{
	if (read(fd, &wall->start.x, sizeof(double)) != sizeof(double))
		return (error_return_map("error reading start wall\n", NULL, fd));
	if (read(fd, &wall->start.y, sizeof(double)) != sizeof(double))
		return (error_return_map("error reading start wall\n", NULL, fd));
	if (read(fd, &wall->end.x, sizeof(double)) != sizeof(double))
		return (error_return_map("error reading end wall\n", NULL, fd));
	if (read(fd, &wall->end.y, sizeof(double)) != sizeof(double))
		return (error_return_map("error reading end wall\n", NULL, fd));
	if (read(fd, &wall->color, sizeof(int)) != sizeof(int))
		return (error_return_map("error reading color wall\n", NULL, fd));
	if (read(fd, &wall->tex_index, sizeof(int)) != sizeof(int))
		return (error_return_map("error reading tex index wall\n", NULL, fd));
	if (read(fd, &wall->sector_index, sizeof(int)) != sizeof(int))
		return (error_return_map("error reading sect index wall\n", NULL, fd));
	if (read(fd, &wall->wall_type, sizeof(int)) != sizeof(int))
		return (error_return_map("error reading wall type wall\n", NULL, fd));
	if (read(fd, &wall->type_color, sizeof(int)) != sizeof(int))
		return (error_return_map("error reading type color wall\n", NULL, fd));
	if (read(fd, &wall->length, sizeof(int)) != sizeof(int))
		return (error_return_map("error reading length wall\n", NULL, fd));
	return (0);
}

int		read_walls(int fd, t_wall_node **wall_head, int nb_walls_file)
{
	int				nb_walls;
	t_wall_node		*current_wall;

	nb_walls = 0;
	current_wall = NULL;
	while (nb_walls < nb_walls_file)
	{
		if ((current_wall = insert_wall_node(wall_head)) == NULL)
			return (error_return_map("error inserting wall node\n", NULL, fd));
		if (read_wall(fd, current_wall) != 0)
			return (1);
		nb_walls++;
	}
	if (nb_walls != nb_walls_file)
		return (error_return_map("nb walls in file different than nb walls\n", \
				NULL, fd));
		return (0);
}

int		read_sector(int fd, t_sector_node *sector)
{
	if (read(fd, &sector->sector_center.x, sizeof(double)) != sizeof(double))
		return (error_return_map("error reading sector center\n", NULL, fd));
	if (read(fd, &sector->sector_center.y, sizeof(double)) != sizeof(double))
		return (error_return_map("error reading sector center\n", NULL, fd));
	if (read(fd, &sector->floor_height, sizeof(double)) != sizeof(double))
		return (error_return_map("error reading floor height\n", NULL, fd));
	if (read(fd, &sector->ceiling_height, sizeof(double)) != sizeof(double))
		return (error_return_map("error reading ceiling height\n", NULL, fd));
	if (read(fd, &sector->wall_num, sizeof(int)) != sizeof(int))
		return (error_return_map("error reading wall num\n", NULL, fd));
	if (read_walls(fd, &sector->wall_head, sector->wall_num) != 0)
		return (error_return_map("error reading walls\n", NULL, fd));
	if (read(fd, &sector->is_goal, sizeof(int)) != sizeof(int))
		return (error_return_map("error reading is_goal\n", NULL, fd));
	return (0);
}

int		read_sectors(int fd, t_sector_node **sector_head, int num_sectors_file)
{
	int				num_sectors;
	t_sector_node	*current_sector;

	num_sectors = 0;
	current_sector = NULL;
	while (num_sectors < num_sectors_file)
	{
		if ((current_sector = add_sector_node(sector_head)) == NULL)
			return (error_return_map("error in add sector node\n", NULL, fd));
		if (read_sector(fd, current_sector) != 0)
			return (1);
		num_sectors++;
	}
	if (num_sectors != num_sectors_file)
		return (error_return_map("differing nb sectors in file\n", NULL, fd));
	return (0);
}
