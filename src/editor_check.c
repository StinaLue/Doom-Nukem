/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:40:34 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/14 12:58:01 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//checks if the list of walls is closed (loop)
//returns 1 if it is 0 if not
int			wall_loop(t_wall_node *node)
{
	int		loop;
	t_vecdb	*start;

	if (node == NULL)
		return (-1);
	loop = 0;
	start = &node->start_wall;
	while (node->next != NULL)
		node = node->next;
	if (node->end_wall.x == start->x && node->end_wall.y == start->y && &node->start_wall != start)
		loop = 1;
	return (loop);
}

void		set_wall_length(t_wall_node *head)
{
	if (head == NULL)
		return ;
	head->length = get_point_distance(head->start_wall, head->end_wall);
	set_wall_length(head->next);
}
