/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:40:34 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/11 16:08:39 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		is_same_sign(double a, double b)
{
	if (a > 0 && b < 0)
		return (0);
	if (a < 0 && b > 0)
		return (0);
	return (1);
}

int		check_convex_sector(t_sector_node *sector)
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
		angle = atan2(cross_product(a, b), dot_product(a, b));
		if (!is_same_sign(angle, total_angle) || fabs(angle) > 3.1415926)
			return (0);
		total_angle += angle;
		if (fabs(total_angle) > M_PI * 2)
			return (0);
		wall = wall->next;
	}
	return (1);
}

int		check_clockwise_sector(t_sector_node *sector)
{
	t_wall_node	*wall;
	t_vecdb		a;
	t_vecdb		b;
	double		angle;

	if (sector == NULL || sector->wall_head == NULL)
		return (-1);
	wall = sector->wall_head;
	while (wall->next != NULL)
	{
		a = vecdb_diff(wall->end, wall->start);
		b = vecdb_diff(wall->next->end, wall->next->start);
		angle = atan2(cross_product(a, b), dot_product(a, b));
		if (angle > 0)
			return (0);
		wall = wall->next;
	}
	return (1);
}

void	flip_walls(t_sector_node *sector)
{
	t_wall_node	*wall;
	t_vecdb		tmp;

	if (sector == NULL)
		return ;
	wall = sector->wall_head;
	while (wall != NULL)
	{
		tmp = wall->start;
		wall->start = wall->end;
		wall->end = tmp;
		wall = wall->next;
	}
}

void	set_sectors_clockwise(t_sector_node *sector_head)
{
	if (sector_head == NULL)
		return ;
	if (check_clockwise_sector(sector_head) == 0)
		flip_walls(sector_head);
	set_sectors_clockwise(sector_head->next);
}
