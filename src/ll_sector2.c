/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_sector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:23:40 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 19:28:42 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector_node	*insert_sector_node(t_sector_node **sector_list)
{
	if (*sector_list == NULL)
	{
		*sector_list = malloc(sizeof(t_sector_node));
		if (*sector_list)
			(*sector_list)->next = NULL;
		return (*sector_list);
	}
	else
		return (insert_sector_node(&(*sector_list)->next));
}

t_sector_node	*add_sector_node(t_sector_node **sector_head)
{
	t_sector_node *new_node;

	new_node = insert_sector_node(sector_head);
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->wall_head = NULL;
	new_node->wall_num = 0;
	reset_vecdb(&new_node->sector_center);
	new_node->ceiling_height = 20;
	new_node->floor_height = 2;
	new_node->is_goal = 0;
	return (new_node);
}

void			delete_sector(t_sector_node **node)
{
	t_sector_node	*tmp;

	tmp = *node;
	*node = (*node)->next;
	free_wall_list(&tmp->wall_head);
	free(tmp);
	tmp = NULL;
}

void			delete_sector_by_index(t_sector_node **sector_list, \
									unsigned int index)
{
	if (*sector_list == NULL)
		return ;
	else if (index == 0)
		delete_sector(sector_list);
	else
		delete_sector_by_index(&(*sector_list)->next, index - 1);
}

void			delete_sector_by_address(t_sector_node **sector_list, \
										t_sector_node *node)
{
	if (*sector_list == NULL || node == NULL)
		return ;
	else if (node == *sector_list)
		delete_sector(sector_list);
	else
		delete_sector_by_address(&(*sector_list)->next, node);
}
