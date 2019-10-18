/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:35:35 by afonck            #+#    #+#             */
/*   Updated: 2019/10/18 03:36:13 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_pix(Uint32 *pixels, int x, int y, int color)
{
	if (x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
		pixels[x + y * WIN_WIDTH] = color;
}

void	draw_vertical(Uint32 *pixels, int x, int y1, int y2, int color)
{
	while (y1 < y2)
	{
		fill_pix(pixels, x, y1, color);
		y1++;
	}
}