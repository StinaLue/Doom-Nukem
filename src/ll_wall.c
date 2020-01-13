/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:25:24 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/08 16:59:42 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//recursively mallocs a node at the end of the wall list
//returns malloced adress
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

//frees every node of the wall_list and sets them to NULL
void		free_wall_list(t_wall_node **wall_list)
{
	if (*wall_list)
	{
		free_wall_list(&(*wall_list)->next);
		free(*wall_list);
		*wall_list = NULL;
	}
}

//deletes the last wall node and sets it to NULL
//return the new last node adress or NULL of none left
t_wall_node	*delete_last_wall(t_wall_node **wall_list)
{
	t_wall_node	*tmp;

	if (*wall_list == NULL)
		return (NULL);
	else if ((*wall_list)->next == NULL)
	{
		free(*wall_list);
		*wall_list = NULL;
		return (NULL);
	}
	else
	{
		tmp = delete_last_wall(&(*wall_list)->next);
		if (tmp == NULL)
			return (*wall_list);
		else
			return (tmp);
	}
}

//adds existing node add the end of the list and copies the variables from given node
//returns created node adress
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
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

//create new node with given params and adds it to the end of list
//returns created node adress
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

//return wall adress from an index
t_wall_node	*get_wall_by_index(t_wall_node *wall_list,unsigned int index)
{
	if (wall_list == NULL)
		return (NULL);
	else if (index == 0)
		return (wall_list);
	else
		return (get_wall_by_index(wall_list->next, index - 1));
}

//returns the first wall for which the distance from the wall center to the position given is under 'dist'
t_wall_node	*get_wall_by_pos(t_wall_node *wall_list, t_vecdb position, double dist)
{
	t_vecdb wall_center;

	if (wall_list == NULL)
		return (NULL);
	wall_center.x = wall_list->start_wall.x - wall_list->end_wall.x;
	wall_center.y = wall_list->start_wall.y - wall_list->end_wall.y;
	if (get_point_distance(position, wall_center) <= dist)
		return (wall_list);
	else
		return (get_wall_by_pos(wall_list->next, position, dist));
}

t_wall_node	*get_closest_wall(t_wall_node *wall_list, t_vecdb position, double dist, double inc)
{
	int		i;
	t_wall_node *node;

	node = NULL;
	i = 0;
	while (i < 30)
	{
		node = get_wall_by_pos(wall_list, position, dist + i * inc);
		if (node)
			return (node);
	}
	return (NULL);
}

//returns a vector of the average position of all the wall_start coordinates of a list of walls
//returns a 0,0 vector if there are no walls
t_vecdb		point_average_position(t_wall_node *wall_head)
{
	t_vecdb	average;
	int		count;
	t_wall_node *current_wall;

	average.x = 0;
	average.y = 0;
	current_wall = wall_head;
	count = 0;
	while (current_wall != NULL)
	{
		count++;
		average.x += current_wall->start_wall.x;
		average.y += current_wall->start_wall.y;
		current_wall = current_wall->next;
	}
	if (count > 0)
	{
		average.x /= count;
		average.y /= count;
	}
	return (average);
}

//removewall(int index)
//removewall(t_vecdb position)