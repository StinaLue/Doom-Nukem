/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:25:24 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/07 16:51:08 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wall_node	*insert_wall_node(t_wall_node **wall_list)
{
	if(*wall_list == NULL)
	{
		*wall_list = malloc(sizeof(t_wall_node));
		return (*wall_list);
	}
	else
		return (insert_wall_node(&((*wall_list)->next)));
}

t_wall_node	*add_wall_node(t_wall_node **wall_head, const t_wall_node *node)
{
	t_wall_node *new_node;

	new_node = insert_wall_node(wall_head);
	if (new_node == NULL)
		return (NULL);
	new_node->start_wall.x = node->start_wall.x;
	new_node->start_wall.y = node->start_wall.y;
	new_node->end_wall.x = node->end_wall.x;
	new_node->end_wall.x = node->end_wall.y;
	new_node->sector_index = node->sector_index;
	new_node->neighbor_sector = node->neighbor_sector;
	return (new_node);
}

t_wall_node	*create_wall_node(t_wall_node **wall_head, t_vecdb a, t_vecdb b, int color)
{
	t_wall_node *new_node;

	new_node = insert_wall_node(wall_head);
	if (new_node == NULL)
		return (NULL);
	new_node->start_wall.x = a.x;
	new_node->start_wall.y = a.y;
	new_node->end_wall.x = b.x;
	new_node->end_wall.y = b.y;
	new_node->color = color;
	new_node->sector_index = -1;
	new_node->neighbor_sector = -1;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

//removewall(int index)
//removewall(t_vecdb position)