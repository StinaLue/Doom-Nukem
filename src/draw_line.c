/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:06:42 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/11 15:17:53 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	draw_vertical(t_bresen *bresen, Uint32 *img_ptr, int color)
{
	int i;
	int cumul;

	i = 1;
	cumul = bresen->dy / 2;
	while (i <= bresen->dy)
	{
		bresen->point_one.y += bresen->yinc;
		cumul += bresen->dx;
		if (cumul >= bresen->dy)
		{
			cumul -= bresen->dy;
			bresen->point_one.x += bresen->xinc;
		}
		fill_pix(img_ptr, bresen->point_one.x, bresen->point_one.y, color);
		i++;
	}
}

void	draw_horizontal(t_bresen *bresen, Uint32 *img_ptr, int color)
{
	int i;
	int cumul;

	i = 1;
	cumul = bresen->dx / 2;
	while (i <= bresen->dx)
	{
		bresen->point_one.x += bresen->xinc;
		cumul += bresen->dy;
		if (cumul >= bresen->dx)
		{
			cumul -= bresen->dx;
			bresen->point_one.y += bresen->yinc;
		}
		fill_pix(img_ptr, bresen->point_one.x, bresen->point_one.y, color);
		i++;
	}
}

void	assign_vec(t_vec *one, const t_vec *two)
{
	one->x = two->x;
	one->y = two->y;
}

int		pos_or_neg(int i)
{
	if (i > 0)
		return (1);
	else
		return (-1);
}

void	draw_line(const t_vec *point_one, const t_vec *point_two, Uint32 *img_ptr, int color)
{
	t_bresen bresen;

	bresen.point_one.x = point_one->x;
	bresen.point_one.y = point_one->y;
	bresen.point_two.x = point_two->x;
	bresen.point_two.y = point_two->y;
	bresen.dx = point_two->x - point_one->x;
	bresen.dy = point_two->y - point_one->y;
	bresen.xinc = pos_or_neg(bresen.dx);
	bresen.yinc = pos_or_neg(bresen.dy);
	bresen.dx = ft_absolute(bresen.dx);
	bresen.dy = ft_absolute(bresen.dy);
	//fill_pix(point_one->x, point_one->y, map->altitude_z, map);
	if (bresen.dx > bresen.dy)
		draw_horizontal(&bresen, img_ptr, color);
	else
		draw_vertical(&bresen, img_ptr, color);
}
