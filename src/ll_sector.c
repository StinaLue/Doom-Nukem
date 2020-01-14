/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_sector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:02:35 by phaydont          #+#    #+#             */
/*   Updated: 2020/01/14 13:21:56 by phaydont         ###   ########.fr       */
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

//deletes a sector and replaces it's adress with the next node in the list
void		delete_sector(t_sector_node **node)
{
	t_sector_node	*tmp;

	tmp = *node;
	*node = (*node)->next;
	free_wall_list(&tmp->wall_head);
	free(tmp);
}

//deletes sector at given index in list and relinks the list
//return next sector adress from the list
void		delete_sector_by_index(t_sector_node **sector_list,unsigned int index)
{
	if (*sector_list == NULL)
		return ;
	else if (index == 0)
		delete_sector(sector_list);
	else
		delete_sector_by_index(&(*sector_list)->next, index - 1);
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


//mallocs and copies a linked list of sectors and their walls into a new sector list
//returns the number of sector copied or -1 if malloc error
int			copy_sector_list(t_sector_node *sector_list, t_sector_node **new_list)
{
	int	ret;

	if (sector_list == NULL)
		return (0);
	*new_list = malloc(sizeof(t_sector_node));
	if (*new_list == NULL)
		return (-1);
	(*new_list)->wall_num = sector_list->wall_num;
	(*new_list)->sector_center = sector_list->sector_center;
	(*new_list)->next = NULL;
	if (copy_wall_list(sector_list->wall_head, &(*new_list)->wall_head) == -1)
		return (-1);
	ret = copy_sector_list(sector_list->next, &(*new_list)->next);
	if (ret == -1)
		return (-1);
	return (ret + 1);
}

//returns the last sector adress in a sector list
t_sector_node	*get_last_sector(t_sector_node *node)
{
	if (node == NULL)
		return (NULL);
	if (node->next == NULL)
		return (node);
	return (get_last_sector(node->next));
}

//returns sector count
int			count_sectors(t_sector_node *sector_list)
{
	int i;

	i = 0;
	while (sector_list != NULL)
	{
		i++;
		sector_list = sector_list->next;
	}
	return (i);
}

//applies a given function to every sector in the list
void		itt_sector_wall_heads(t_sector_node *sector_node, void (*f)(t_wall_node *wall_node))
{
	while (sector_node)
	{
		f(sector_node->wall_head);
		sector_node = sector_node->next;
	}
}
