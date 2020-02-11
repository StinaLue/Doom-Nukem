/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:25:24 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/11 16:05:15 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//recursively mallocs a node at the end of the wall list
//returns malloced adress
t_wall_node	*insert_wall_node(t_wall_node **wall_list)
{
	if (*wall_list == NULL)
	{
		*wall_list = malloc(sizeof(t_wall_node));
		if (*wall_list)
		{
			(*wall_list)->next = NULL;
			(*wall_list)->neighbor_sector = NULL;
		}
		return (*wall_list);
	}
	else
		return (insert_wall_node(&((*wall_list)->next)));
}

//frees every node of the wall_list and sets them to NULL
void	free_wall_list(t_wall_node **wall_list)
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
t_wall_node	*copy_wall_node(t_wall_node **wall_head, const t_wall_node *node)
{
	t_wall_node *new_node;

	new_node = insert_wall_node(wall_head);
	if (new_node == NULL)
		return (NULL);
	new_node->start.x = node->start.x;
	new_node->start.y = node->start.y;
	new_node->end.x = node->end.x;
	new_node->end.y = node->end.y;
	new_node->sector_index = node->sector_index;
	new_node->neighbor_sector = node->neighbor_sector;
	new_node->next = NULL;
	new_node->tex_index = node->tex_index;
	new_node->type_color = node->type_color;
	new_node->wall_type = node->wall_type;
	new_node->color = 0xFFFFFF;
	return (new_node);
}

//create new node with given params and adds it to the end of list
//returns created node adress
t_wall_node	*create_wall_node(t_wall_node **wall_head, t_vecdb a, t_vecdb b, int tex_index)
{
	t_wall_node *new_node;

	new_node = insert_wall_node(wall_head);
	if (new_node == NULL)
		return (NULL);
	new_node->start.x = a.x;
	new_node->start.y = a.y;
	new_node->end.x = b.x;
	new_node->end.y = b.y;
	new_node->color = 0xffffff;
	new_node->sector_index = -1;
	new_node->neighbor_sector = NULL;
	new_node->next = NULL;
	new_node->tex_index = tex_index;
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
	wall_center.x = wall_list->start.x - wall_list->end.x;
	wall_center.y = wall_list->start.y - wall_list->end.y;
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
t_vecdb	point_average_position(t_wall_node *wall_head)
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
		average.x += current_wall->start.x;
		average.y += current_wall->start.y;
		current_wall = current_wall->next;
	}
	if (count > 0)
	{
		average.x /= count;
		average.y /= count;
	}
	return (average);
}

t_wall_node		*get_last_wall_node(t_wall_node *wall_list)
{
	if (wall_list == NULL)
		return (NULL);
	while (wall_list->next != NULL)
		wall_list = wall_list->next;
	return (wall_list);
}

//removewall(int index)
//removewall(t_vecdb position)

//mallocs and copies a list of walls on a new list adress
//returns the number of walls mallocs or -1 if malloc error
int	copy_wall_list(t_wall_node *wall_list, t_wall_node **new_list)
{
	int	ret;

	if (wall_list == NULL)
	{
		(*new_list) = NULL;
		return (0);
	}
	*new_list = malloc(sizeof(t_wall_node));
	if (*new_list == NULL)
		return (-1);
    (*new_list)->start = wall_list->start;
    (*new_list)->end = wall_list->end;
    //set_vecdb_values(&wall_list->start, &(*new_list)->start);
    //set_vecdb_values(&(*new_list)->end, &wall_list->end);
	//(*new_list)->start.x = wall_list->start.x;
	//(*new_list)->start.y = wall_list->start.y;
	//(*new_list)->end.x = wall_list->end.x;
	//(*new_list)->end.y = wall_list->end.y;
	(*new_list)->color = wall_list->color;
	(*new_list)->length = wall_list->length;
	(*new_list)->sector_index = wall_list->sector_index;
	(*new_list)->tex_index = wall_list->tex_index;
	(*new_list)->wall_type = wall_list->wall_type;
	(*new_list)->type_color = wall_list->type_color;
	(*new_list)->neighbor_sector = wall_list->neighbor_sector;
	ret = copy_wall_list(wall_list->next, &(*new_list)->next);
	if (ret == -1)
		return (-1);
	return (ret + 1);
}

t_wall_node	*undo_wall(t_sector_node *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	if (node->wall_num > 0)
		node->wall_num--;
	return (delete_last_wall(&node->wall_head));
}
