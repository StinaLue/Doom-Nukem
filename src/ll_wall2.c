/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_wall2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:30:02 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 22:27:02 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

t_wall_node	*create_wall_node(t_wall_node **wall_head, \
					t_vecdb a, t_vecdb b, int tex_index)
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

t_vecdb		point_average_position(t_wall_node *wall_head)
{
	t_vecdb		average;
	int			count;
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

int			copy_wall_list(t_wall_node *wall_list, t_wall_node **new_list)
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
	(*new_list)->color = wall_list->color;
	(*new_list)->length = wall_list->length;
	(*new_list)->sector_index = wall_list->sector_index;
	(*new_list)->tex_index = wall_list->tex_index;
	(*new_list)->wall_type = wall_list->wall_type;
	(*new_list)->type_color = wall_list->type_color;
	//(*new_list)->neighbor_sector = wall_list->neighbor_sector;
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
