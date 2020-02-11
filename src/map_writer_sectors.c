/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_writer_sectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 03:00:48 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 18:25:57 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int		write_wall(int fd, t_wall_node *wall)
{
	if (write(fd, &wall->start.x, sizeof(double)) != sizeof(double))
		return (error_return_map("error writing start wall\n", NULL, fd));
	if (write(fd, &wall->start.y, sizeof(double)) != sizeof(double))
		return (error_return_map("error writing start wall\n", NULL, fd));
	if (write(fd, &wall->end.x, sizeof(double)) != sizeof(double))
		return (error_return_map("error writing end wall\n", NULL, fd));
	if (write(fd, &wall->end.y, sizeof(double)) != sizeof(double))
		return (error_return_map("error writing end wall\n", NULL, fd));
	if (write(fd, &wall->color, sizeof(int)) != sizeof(int))
		return (error_return_map("error writing color wall\n", NULL, fd));
	if (write(fd, &wall->tex_index, sizeof(int)) != sizeof(int))
		return (error_return_map("error writing tex index wall\n", NULL, fd));
	if (write(fd, &wall->sector_index, sizeof(int)) != sizeof(int))
		return (error_return_map("error writing sect index wall\n", NULL, fd));
	if (write(fd, &wall->wall_type, sizeof(int)) != sizeof(int))
		return (error_return_map("error writing wall type wall\n", NULL, fd));
	if (write(fd, &wall->type_color, sizeof(int)) != sizeof(int))
		return (error_return_map("error writing type color wall\n", NULL, fd));
	if (write(fd, &wall->length, sizeof(int)) != sizeof(int))
		return (error_return_map("error writing length wall\n", NULL, fd));
	return (0);
}

int		write_walls(int fd, t_wall_node *wall_head, int nb_walls_file)
{
	int nb_walls;

	nb_walls = 0;
	if (wall_head == NULL)
		return (error_return_map("wall head is NULL\n", NULL, fd));
	while (wall_head != NULL)
	{
		if (write_wall(fd, wall_head) != 0)
			return (1);
		wall_head = wall_head->next;
		nb_walls++;
	}
	if (nb_walls != nb_walls_file)
		return (error_return_map("nb walls in file different than nb walls\n", \
				NULL, fd));
		return (0);
}

int		write_sector(int fd, t_sector_node *sector)
{
	if (write(fd, &sector->sector_center.x, sizeof(double)) != sizeof(double))
		return (error_return_map("error writing sector center\n", NULL, fd));
	if (write(fd, &sector->sector_center.y, sizeof(double)) != sizeof(double))
		return (error_return_map("error writing sector center\n", NULL, fd));
	if (write(fd, &sector->floor_height, sizeof(double)) != sizeof(double))
		return (error_return_map("error writing floor height\n", NULL, fd));
	if (write(fd, &sector->ceiling_height, sizeof(double)) != sizeof(double))
		return (error_return_map("error writing ceiling height\n", NULL, fd));
	if (write(fd, &sector->wall_num, sizeof(int)) != sizeof(int))
		return (error_return_map("error writing wall num\n", NULL, fd));
	if (write_walls(fd, sector->wall_head, sector->wall_num) != 0)
		return (error_return_map("error writing walls\n", NULL, fd));
	if (write(fd, &sector->is_goal, sizeof(int)) != sizeof(int))
		return (error_return_map("error writing is_goal\n", NULL, fd));
	return (0);
}

int		write_sectors(int fd, t_sector_node *sector_head, int num_sectors_file)
{
	int num_sectors;

	num_sectors = 0;
	if (sector_head == NULL)
		return (error_return_map("sector head is NULL\n", NULL, fd));
	while (sector_head != NULL)
	{
		if (write_sector(fd, sector_head) != 0)
			return (1);
		sector_head = sector_head->next;
		num_sectors++;
	}
	if (num_sectors != num_sectors_file)
		return (error_return_map("differing nb sectors in file\n", NULL, fd));
	return (0);
}
