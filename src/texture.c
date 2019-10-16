/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:47:59 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/16 16:28:28 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include <math.h>

void	fill_tex(int texture[4][TEX_W * TEX_H])
{
	int x;
	int y;
	int	xycolor;
	int xorcolor;

	x = 0;
	while (x < TEX_W)
	{
		y = 0;
		while (y < TEX_H)
		{
			xorcolor = (x * 256 / TEX_W) ^ (y * 256 / TEX_H);
			xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
			texture[0][TEX_W * y + x] = 65536 * 254 * (x != y && x != TEX_W - y);
			texture[1][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			texture[2][TEX_W * y + x] = 256 * xycolor + 65536 * xycolor;
			texture[3][TEX_W * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			y++;
		}
		x++;
	}
}

void	fill_texel(t_player const *player, t_wall_finding *find_wall,
					t_raycast *raycast, t_data *data)
{
	int		d;
	int		y;

	y = raycast->start_line;
	while (y < raycast->end_line)
	{
		d = y * 256 - WIN_HEIGHT * 128 + raycast->height * 128
			- (player->up_and_down - player->crouch) * 256;
		data->tex_y = ((d * TEX_H) / raycast->height) / 256;
		data->color =
			data->texture[data->tex_num][TEX_H * data->tex_y + data->tex_x];
		if (find_wall->side == 1)
			data->color = (data->color >> 1) & 8355711;
		fill_pix(data->img_ptr, raycast->current_x, y, data->color);
		y++;
	}
}

void	draw_tex(t_player const *player, t_wall_finding *find_wall,
					t_raycast *raycast, t_data *data)
{
	double	wallx;

	if ((*data->map_ptr)[raycast->map_y][raycast->map_x] == 1)
		data->tex_num = 0;
	if (find_wall->side == 0 && player->x < raycast->map_x)
		data->tex_num = 1;
	if (find_wall->side == 1)
		data->tex_num = (player->y < raycast->map_y ? 2 : 3);
	if (find_wall->side == 0)
		wallx = player->y + find_wall->distance_wall * raycast->dir_y;
	else
		wallx = player->x + find_wall->distance_wall * raycast->dir_x;
	wallx -= floor(wallx);
	data->tex_x = (int)(wallx * (double)TEX_W);
	if ((find_wall->side == 0 && raycast->dir_x > 0)
		|| (find_wall->side == 1 && raycast->dir_y < 0))
		data->tex_x = TEX_W - data->tex_x - 1;
	fill_texel(player, find_wall, raycast, data);
}

