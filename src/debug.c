/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 11:47:21 by afonck            #+#    #+#             */
/*   Updated: 2020/01/15 11:53:07 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void    print_vecdb(const t_vecdb *vecdb, const char *name)
{
    ft_printf("--------------------\n");
    ft_printf("vecdb name %s\n", name);
    ft_printf("\tx = %f\n", vecdb->x);
    ft_printf("\ty = %f\n", vecdb->y);
    ft_printf("--------------------\n");
}

void    print_vec(const t_vec *vec, const char *name)
{
    ft_printf("--------------------\n");
    ft_printf("vec name %s\n", name);
    ft_printf("\tx = %d\n", vec->x);
    ft_printf("\ty = %d\n", vec->y);
    ft_printf("--------------------\n");
}

void    print_map_contents(const t_map *map)
{
    t_sector_node   *tmp_sec;
    t_wall_node     *tmp_wall;
    int             i;
    int             j;

    i = 0;
    if (map == NULL)
        return ;
    tmp_sec = map->sector_head;
    while (tmp_sec != NULL)
    {
        ft_printf("Sector index %d\n\n", i);
        j = 0;
        tmp_wall = tmp_sec->wall_head;
        while (tmp_wall != NULL)
        {
            ft_printf("\tWall index %d\n", j);
            print_vecdb(&tmp_wall->start, "start wall");
            print_vecdb(&tmp_wall->end, "end wall");
            tmp_wall = tmp_wall->next;
            j++;
        }
        ft_printf("--------------------\n");
        tmp_sec = tmp_sec->next;
        i++;
    }
}