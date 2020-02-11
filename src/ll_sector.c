/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_sector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:02:35 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/11 19:29:13 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			free_sector_list(t_sector_node **sector_list)
{
	if (*sector_list)
	{
		free_sector_list(&(*sector_list)->next);
		free_wall_list(&(*sector_list)->wall_head);
		free(*sector_list);
		*sector_list = NULL;
	}
}

int				itt_sectors_true(t_sector_node *sector_node, \
									int (*f)(t_sector_node *))
{
	while (sector_node)
	{
		if (f(sector_node) == 0)
			return (0);
		sector_node = sector_node->next;
	}
	return (1);
}

void			itt_sector_wall_heads(t_sector_node *sector_node, \
							void (*f)(t_wall_node *wall_node))
{
	while (sector_node)
	{
		f(sector_node->wall_head);
		sector_node = sector_node->next;
	}
}

t_sector_node	*get_sector_by_index(t_sector_node *sector_list, \
										unsigned int index)
{
	if (sector_list == NULL)
		return (NULL);
	else if (index == 0)
		return (sector_list);
	else
		return (get_sector_by_index(sector_list->next, index - 1));
}

void			set_sector_position(t_sector_node *sector_list)
{
	if (sector_list == NULL)
		return ;
	else if (sector_list->wall_head != NULL)
		sector_list->sector_center = \
					point_average_position(sector_list->wall_head);
	set_sector_position(sector_list->next);
}
