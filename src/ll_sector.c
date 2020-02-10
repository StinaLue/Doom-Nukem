/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_sector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:02:35 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/09 21:15:25 by sluetzen         ###   ########.fr       */
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
		if (*sector_list)
			(*sector_list)->next = NULL;
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
	new_node->wall_num = 0;
    reset_vecdb(&new_node->sector_center);
	//new_node->sector_center.x = -1;
	//new_node->sector_center.y = -1;
	new_node->ceiling_height = 20;
	new_node->floor_height = 2;
	new_node->is_goal = 0;
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
	tmp = NULL;
}

//deletes sector at given index in list and relinks the list
//return next sector adress from the list
void		delete_sector_by_index(t_sector_node **sector_list, unsigned int index)
{
	if (*sector_list == NULL)
		return ;
	else if (index == 0)
		delete_sector(sector_list);
	else
		delete_sector_by_index(&(*sector_list)->next, index - 1);
}

void 		delete_sector_by_address(t_sector_node **sector_list, t_sector_node *node)
{
	if (*sector_list == NULL || node == NULL)
		return ;
	else if (node == *sector_list)
		delete_sector(sector_list);
	else
		delete_sector_by_address(&(*sector_list)->next, node);
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

int				point_in_sector(t_sector_node *sector, t_vecdb point)
{
	t_wall_node *wall;

	t_vecdb		a;
	t_vecdb		b;

	wall = sector->wall_head;
	while(wall != NULL)
	{
		a = vecdb_diff(wall->end, wall->start);
		b = vecdb_diff(point, wall->start);
		if (cross_product(a, b) > 0)
			return (0);
		wall = wall->next;
	}
	return (1);
}

//return first sector that it within a radius r of the given position or NULL if none is found
t_sector_node	*get_sector_by_pos(t_sector_node *sector_head, t_vecdb point)
{
	double			dist;
	t_sector_node	*sector;
	t_sector_node	*closest_sector;

	dist = 1000;
	closest_sector = NULL;
	sector = sector_head;
	while (sector != NULL)
	{
		if (point_in_sector(sector, point) && get_point_distance(sector->sector_center, point) < dist)
		{
			closest_sector = sector;
			dist = get_point_distance(sector->sector_center, point);
		}
		sector = sector->next;
	}
	return (closest_sector);
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
	(*new_list)->next = NULL;
	(*new_list)->sector_center = sector_list->sector_center;
	(*new_list)->floor_height = sector_list->floor_height;
	(*new_list)->ceiling_height = sector_list->ceiling_height;
	(*new_list)->wall_num = sector_list->wall_num;
	(*new_list)->is_goal = sector_list->is_goal;
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

//returns the previous sector adress of the node
t_sector_node	*get_previous_sector(t_sector_node *list, t_sector_node *node)
{
	if (node == NULL || list == NULL)
		return (NULL);
	if (list->next == node)
		return (list);
	return (get_previous_sector(list->next, node));
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

//applies a boolean function on every sector of the sector list
//returns 0 if any of the sector return 0 to the function else return 1
int		itt_sectors_true(t_sector_node *sector_node, int (*f)(t_sector_node *))
{
	while (sector_node)
	{
		if (f(sector_node) == 0)
			return (0);
		sector_node = sector_node->next;
	}
	return (1);
}

//runs void function on every wall_head of a sector list
void		itt_sector_wall_heads(t_sector_node *sector_node, void (*f)(t_wall_node *wall_node))
{
	while (sector_node)
	{
		f(sector_node->wall_head);
		sector_node = sector_node->next;
	}
}
