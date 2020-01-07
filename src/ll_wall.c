/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:25:24 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/07 15:06:26 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wall_node	*add_wall_node(t_wall_node **wall_list)
{
	if(*wall_list == NULL)
	{
		*wall_list = malloc(sizeof(t_wall_node));
		return (*wall_list);
	}
	else if ((*wall_list)->next == NULL)
	{
		(*wall_list)->next = malloc(sizeof(t_wall_node));
		return ((*wall_list)->next);
	}
	else
		return (add_wall_node(&((*wall_list)->next)));
}

t_wall_node	*create_wall_node(t_wall_node **wall_head, const t_wall_node *node)
{
	t_wall_node *new_node;

	new_node = add_wall_node(wall_head);
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

//removewall(int index)
//removewall(t_vecdb position)