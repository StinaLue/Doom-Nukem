/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:35:35 by afonck            #+#    #+#             */
/*   Updated: 2019/11/13 13:14:56 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_pix(Uint32 *pixels, t_vec *point, int color, int rowsize)
{
	if (point->x < WIN_WIDTH && point->y < WIN_HEIGHT && point->x > 0 && point->y > 0)
		//pixels[x + y * WIN_WIDTH] = color;
		pixels[point->x + point->y * rowsize] = color;
}
/*
void	draw_wall_and_floor(Uint32 *pixels, t_raycast *raycast)
{
	int sky;
	int floor;

	sky = raycast->end_line;
	floor = raycast->start_line;
	while (sky < WIN_HEIGHT)
	{
		fill_pix(pixels, raycast->current_x, sky, 0x808080);
		sky++;
	}
	while (floor > 0)
	{
		fill_pix(pixels, raycast->current_x, floor, 0x87CEFA);
		floor--;
	}
}
*/