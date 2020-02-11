/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:25:24 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/11 22:27:19 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void		free_wall_list(t_wall_node **wall_list)
{
	if (*wall_list)
	{
		free_wall_list(&(*wall_list)->next);
		free(*wall_list);
		*wall_list = NULL;
	}
}

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
