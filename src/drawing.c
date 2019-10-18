/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:35:35 by afonck            #+#    #+#             */
/*   Updated: 2019/10/18 12:38:08 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_pix(Uint32 *pixels, int x, int y, int color)
{
	if (x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
		pixels[x + y * WIN_WIDTH] = color;
}

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
