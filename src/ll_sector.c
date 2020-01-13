/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_sector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:02:35 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/08 16:56:52 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//recursively mallocs a node at the end of the sector list
//returns its adress
t_sector_node	*insert_sector_node(t_sector_node **sector_list)
{
	if(*sector_list == NULL)
	{
		*sector_list = malloc(sizeof(t_sector_node));
		return (*sector_list);
	}
	else
		return (insert_sector_node(&(*sector_list)->next));
}

//recursively frees the sector lists and the wall lists inside of them and sets all to NULL
void		free_sector_list(t_sector_node **sector_list)
{
	if (*sector_list)
	{
		free_sector_list(&(*sector_list)->next);
		free_wall_list(&(*sector_list)->wall_head);
		free(*sector_list);
		*sector_list = NULL;
	}
}

//creates a default sector and adds it to the end of sector list
//returns created sector adress
t_sector_node	*add_sector_node(t_sector_node **sector_head)
{
	t_sector_node *new_node;

	new_node = insert_sector_node(sector_head);
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->wall_head = NULL;
	new_node->wall_num = -1;
	new_node->sector_center.x = -1;
	new_node->sector_center.y = -1;
	return (new_node);
}

//deletes sector at given index in list and relinks the list
//return next sector adress from the list
t_sector_node	*delete_sector_node(t_sector_node **sector_list,unsigned int index)
{
	t_sector_node *tmp;

	if (*sector_list == NULL)
		return (NULL);
	else if (index == 0)
	{
		tmp = *sector_list;
		*sector_list = (*sector_list)->next;
		free_wall_list(&tmp->wall_head);
		free(tmp);
		return (*sector_list);
	}
	else
		return (delete_sector_node(&(*sector_list)->next, index - 1));
}

//return sector adress by index or NULL if index out of range
t_sector_node	*get_sector_by_index(t_sector_node *sector_list,unsigned int index)
{
	if (sector_list == NULL)
		return (NULL);
	else if (index == 0)
		return (sector_list);
	else
		return (get_sector_by_index(sector_list->next, index - 1));
}

//sets the sector position of each sector in the sector list from the average position of the walls in the sector
void		set_sector_position(t_sector_node *sector_list)
{
	if (sector_list == NULL)
		return ;
	else if (sector_list->wall_head != NULL)
		sector_list->sector_center = point_average_position(sector_list->wall_head);
	set_sector_position(sector_list->next);
}

//return first sector that it within a radius r of the given position or NULL if none is found
t_sector_node	*get_sector_by_pos(t_sector_node *sector_list, t_vecdb point, double dist)
{
	if (sector_list == NULL)
		return (NULL);
	else if (get_point_distance(sector_list->sector_center, point) <= dist)
		return (sector_list);
	else
		return (get_sector_by_pos(sector_list->next, point, dist));
}