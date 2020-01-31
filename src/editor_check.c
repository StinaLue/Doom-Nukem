/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:40:34 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/31 12:21:21 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			get_sign(double num)
{
	if (num > 0)
		return 1;
	if (num < 0)
		return -1;
	return (0);
}

//checks if the list of walls is closed (loop)
//returns 1 if it is 0 if not
int			wall_loop(t_wall_node *node)
{
	int		loop;
	t_vecdb	*start;

	if (node == NULL)
		return (-1);
	loop = 0;
	start = &node->start;
	while (node->next != NULL)
		node = node->next;
	if (node->end.x == start->x && node->end.y == start->y && &node->start != start)
		loop = 1;
	return (loop);
}

//expects a sector with at least 3 walls
int			check_convex_sector(t_sector_node *sector)
{
	t_wall_node	*wall;
	t_vecdb		a;
	t_vecdb		b;
	double		angle;
	double		total_angle;

	if (sector == NULL || sector->wall_head == NULL)
		return (0);
	wall = sector->wall_head;
	total_angle = 0;
	while (wall->next != NULL)
	{
		a = vecdb_diff(wall->end, wall->start);
		b = vecdb_diff(wall->next->end, wall->next->start);
		angle = atan2(fabs(cross_product(a,b)), dot_product(a,b));
		if (fabs(total_angle) > fabs(total_angle + angle))
			return (0);
		total_angle += angle;
		if (fabs(total_angle) > M_PI * 2)
			return (0);
		wall = wall->next;
	}
	return (1);
}

//is clockwise?

void		set_wall_length(t_wall_node *head)
{
	if (head == NULL)
		return ;
	head->length = get_point_distance(head->start, head->end);
	set_wall_length(head->next);
}
