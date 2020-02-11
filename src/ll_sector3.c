/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_sector3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:24:29 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 19:29:16 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				point_in_sector(t_sector_node *sector, \
									t_vecdb point)
{
	t_wall_node *wall;
	t_vecdb		a;
	t_vecdb		b;

	wall = sector->wall_head;
	while (wall != NULL)
	{
		a = vecdb_diff(wall->end, wall->start);
		b = vecdb_diff(point, wall->start);
		if (cross_product(a, b) > 0)
			return (0);
		wall = wall->next;
	}
	return (1);
}

t_sector_node	*get_sector_by_pos(t_sector_node *sector_head, t_vecdb point)
{
	double			dist;
	t_sector_node	*sector;
	t_sector_node	*closest_sector;

	dist = 1000;
	closest_sector = NULL;
	sector = sector_head;
	while (sector != NULL)
	{
		if (point_in_sector(sector, point) \
				&& get_point_distance(sector->sector_center, point) < dist)
		{
			closest_sector = sector;
			dist = get_point_distance(sector->sector_center, point);
		}
		sector = sector->next;
	}
	return (closest_sector);
}

int				copy_sector_list(t_sector_node *sector_list, \
							t_sector_node **new_list)
{
	int	ret;

	if (sector_list == NULL)
		return (0);
	*new_list = malloc(sizeof(t_sector_node));
	if (*new_list == NULL)
		return (-1);
	(*new_list)->next = NULL;
	(*new_list)->sector_center = sector_list->sector_center;
	(*new_list)->floor_height = sector_list->floor_height;
	(*new_list)->ceiling_height = sector_list->ceiling_height;
	(*new_list)->wall_num = sector_list->wall_num;
	(*new_list)->is_goal = sector_list->is_goal;
	if (copy_wall_list(sector_list->wall_head, &(*new_list)->wall_head) == -1)
		return (-1);
	ret = copy_sector_list(sector_list->next, &(*new_list)->next);
	if (ret == -1)
		return (-1);
	return (ret + 1);
}

t_sector_node	*get_last_sector(t_sector_node *node)
{
	if (node == NULL)
		return (NULL);
	if (node->next == NULL)
		return (node);
	return (get_last_sector(node->next));
}

t_sector_node	*get_previous_sector(t_sector_node *list, t_sector_node *node)
{
	if (node == NULL || list == NULL)
		return (NULL);
	if (list->next == node)
		return (list);
	return (get_previous_sector(list->next, node));
}
