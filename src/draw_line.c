/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:06:42 by sluetzen          #+#    #+#             */
/*   Updated: 2019/03/29 11:45:37 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vertical(int yinc, int xinc, t_map *map)
{
	int i;
	int cumul;

	i = 1;
	cumul = map->dy / 2;
	while (i <= map->dy)
	{
		map->point_one.y += yinc;
		cumul += map->dx;
		if (cumul >= map->dy)
		{
			cumul -= map->dy;
			map->point_one.x += xinc;
		}
		fill_pix(map->point_one.x, map->point_one.y, map->altitude_z, map);
		i++;
	}
}

void	draw_horizontal(int yinc, int xinc, t_map *map)
{
	int i;
	int cumul;

	i = 1;
	cumul = map->dx / 2;
	while (i <= map->dx)
	{
		map->point_one.x += xinc;
		cumul += map->dy;
		if (cumul >= map->dx)
		{
			cumul -= map->dx;
			map->point_one.y += yinc;
		}
		fill_pix(map->point_one.x, map->point_one.y, map->altitude_z, map);
		i++;
	}
}

int		pos_or_neg(int i)
{
	if (i > 0)
		return (1);
	else
		return (-1);
}

void	draw_line(t_map *map)
{
	int xinc;
	int yinc;

	map->dx = map->point_two.x - map->point_one.x;
	map->dy = map->point_two.y - map->point_one.y;
	xinc = pos_or_neg(map->dx);
	yinc = pos_or_neg(map->dy);
	map->dx = ft_absolute(map->dx);
	map->dy = ft_absolute(map->dy);
	fill_pix(map->point_one.x, map->point_one.y, map->altitude_z, map);
	if (map->dx > map->dy)
		draw_horizontal(yinc, xinc, map);
	else
		draw_vertical(yinc, xinc, map);
}
