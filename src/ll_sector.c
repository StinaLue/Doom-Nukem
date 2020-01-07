/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_sector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:02:35 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/07 15:04:24 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector_node	*add_sector_node(t_sector_node **sector_list)
{
	if(*sector_list == NULL)
	{
		*sector_list = malloc(sizeof(t_sector_node));
		return (*sector_list);
	}
	else if ((*sector_list)->next == NULL)
	{
		(*sector_list)->next = malloc(sizeof(t_sector_node));
		return ((*sector_list)->next);
	}
	else
		return (add_sector_node(&((*sector_list)->next)));
}

t_sector_node	*create_sector_node(t_sector_node **sector_head)
{
	t_sector_node *new_node;

	new_node = add_sector_node(sector_head);
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->wall_head = NULL;
	return (new_node);
}