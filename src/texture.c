/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:47:59 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/18 02:41:40 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include <math.h>

void	fill_tex_loop(int tex[TEX_W * TEX_H], char raw[(TEX_W * TEX_H) * 4], char buf[5])
{
	int tex_index;
	int	x;
	int y;

	tex_index = 0;
	x = 0;
	while (x < TEX_W)
	{
		y = 0;
		while (y < TEX_H)
		{
			ft_strncpy(buf, &raw[tex_index], 4);
			tex[TEX_W * y + x] = ft_hextodeci(buf, 4, 1);
			tex[TEX_W * y + x] += tex[TEX_W * y + x] << 8;
			tex[TEX_W * y + x] += tex[TEX_W * y + x] << 16;
			tex_index += 4;
			y++;
		}
		x++;
	}
}

void	load_tex(char *path, int texture[TEX_W * TEX_H])
{
	int		fd;
	char	raw[(TEX_W * TEX_H) * 4];
	char	buf[5];

	if ((fd = open(path, O_RDONLY | O_NOFOLLOW)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "texture file could not be opened\n");
		exit(EXIT_FAILURE);
	}
	if ((read(fd, raw, (TEX_W * TEX_H) * 4)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error while reading texture file\n");
		exit(EXIT_FAILURE);
	}
	if ((close(fd)) == -1)
		ft_dprintf(STDERR_FILENO, "Error while closing texture file\n");
	fill_tex_loop(texture, raw, buf);
}

void	fill_tex(int texture[8][TEX_W * TEX_H])
{
	int x;
	int y;
	int	xycolor;
	int xorcolor;

	x = 0;
	load_tex("textures/friends1.txt", texture[0]);
	load_tex("textures/friends2.txt", texture[1]);
	load_tex("textures/friends3.txt", texture[2]);
	load_tex("textures/friends4.txt", texture[3]);
	while (x < TEX_W)
	{
		y = 0;
		while (y < TEX_H)
		{
			//xorcolor = (x * 256 / TEX_W) ^ (y * 256 / TEX_H);
			//xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
			//xorcolor = (x * 256 / TEX_W + 453453) >> (y * 256);
			xorcolor = x * y / TEX_H - 2333 * 128; // NEEDED FOR RAINBOW
			//xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
			xycolor = y * 128 / TEX_H + x * 128 / TEX_W; // TRIPPY SQUARES
			//texture[0][TEX_W * y + x] = 65536 * 254 * (x != y && x != TEX_W - y);
			//texture[1][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			//texture[2][TEX_W * y + x] = 256 * xycolor + 65536 * xycolor;
			//texture[3][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			//texture[2][TEX_W * y + x] = xorcolor * xorcolor * 6553;
			texture[4][TEX_W * y + x] = xycolor + 256 * xycolor;
			texture[5][TEX_W * y + x] = (xycolor + 256 * xycolor) >> 8;
			texture[6][TEX_W * y + x] = xorcolor * xorcolor * 655;
			texture[7][TEX_W * y + x] = xorcolor * xorcolor * 65536; // NEEDED FOR RAINBOW
			//texture[1][TEX_W * y + x] = (xycolor + 256 * xycolor) << 6; // TRIPPY SQUARES
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
		//d = y * 256 - WIN_HEIGHT * 128 + raycast->height * 128
		//	- (player->up_and_down - player->crouch) * 256;
		//data->tex_y = ((d * TEX_H) / raycast->height) / 256;
		d = y - (WIN_HEIGHT / 2) + (raycast->height / 2)
			- (player->up_and_down - player->crouch);
		data->tex_y = (((d / 2) * (TEX_H / 2)) / (raycast->height / 2));
		//if (data->tex_y < 0)
			//printf("((%d * %d) / %d) / 256 = %lld\n", d, TEX_H, raycast->height, data->tex_y);
			//printf("((%d * %d) / %d) = %lld\n", d, TEX_H, raycast->height, data->tex_y);
		//printf("d = %d and raycast->height = %d\n", d, raycast->height);
		//if (data->tex_y * 2 < 0)
		//{
		//	printf("HEEEEEERE --> d = %d and raycast->height = %d\n", d, raycast->height);
		//	exit(-1);
		//}
		if (data->tex_x >= 0 && data->tex_y * 2 >= 0 && data->tex_x < TEX_W && data->tex_y < TEX_H)
		{
			data->color =
				data->texture[data->tex_num][TEX_H * (data->tex_y * 2) + data->tex_x];
		if (find_wall->side == 1)
			data->color = (data->color >> 1) & 8355711;
		fill_pix(data->img_ptr, raycast->current_x, y, data->color);
		}
		else
			fill_pix(data->img_ptr, raycast->current_x, y, 0x000000);
		y++;
	}
}

void	draw_tex(t_player const *player, t_wall_finding *find_wall,
					t_raycast *raycast, t_data *data)
{
	double	wallx;
	int		offset;

	offset = (*data->map_ptr)[raycast->map_y][raycast->map_x] == 2 ? 4 : 0;
	if ((*data->map_ptr)[raycast->map_y][raycast->map_x] == 1)
		data->tex_num = 0 + offset;
	if (find_wall->side == 0 && player->x < raycast->map_x)
		data->tex_num = 1 + offset;
	if (find_wall->side == 1)
		data->tex_num = (player->y < raycast->map_y ? 2 + offset : 3 + offset);
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
