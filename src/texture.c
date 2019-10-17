/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:47:59 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/17 19:10:18 by afonck           ###   ########.fr       */
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
	int fd;
	int	texindex = 0;
	char test[(TEX_W * TEX_H) * 4];
	char buf[5];
	unsigned char *access;

	x = 0;
	fd = open("/Users/afonck/Desktop/gitperso/Wolf3d/textures/friends2.txt", O_RDONLY);
	read(fd, test, (TEX_W * TEX_H) * 4);
	//printf("%s\n", test);
	while (x < TEX_W)
	{
		y = 0;
		while (y < TEX_H)
		{
			ft_bzero(buf, 5);
			buf[4] = '\0';
			ft_strncpy(buf, &test[texindex], 4);
			//printf("%s\n", buf);
			texindex += 4;
			xorcolor = (x * 256 / TEX_W) ^ (y * 256 / TEX_H);
			xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
			texture[0][TEX_W * y + x] = (int)strtol(buf, NULL, 0);//65536 * 254 * (x != y && x != TEX_W - y);//ft_itoa(test[TEX_W * y + x]
			texture[0][TEX_W * y + x] += texture[0][TEX_W * y + x] << 8;
			texture[0][TEX_W * y + x] += texture[0][TEX_W * y + x] << 16;
			texture[0][TEX_W * y + x] += texture[0][TEX_W * y + x] << 24;
			access = (unsigned char *)&(texture[0][TEX_W * y + x]);
			*(access + 2) = 0x55;
			printf("%x %x %x %x\n", *access, *(access + 1), *(access + 2), *(access + 3));
			printf("%x\n", texture[0][TEX_W * y + x]);
			//printf("%d\n", texture[0][TEX_W * y + x]);
			texture[1][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			texture[2][TEX_W * y + x] = 256 * xycolor + 65536 * xycolor;
			texture[3][TEX_W * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			/*
			//xorcolor = (x * 256 / TEX_W + 453453) >> (y * 256);
			xorcolor = x * y / TEX_H - 2333 * 128; // NEEDED FOR RAINBOW
			xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
			//xycolor = y * 128 / TEX_H + x * 128 / TEX_W; // TRIPPY SQUARES
			//texture[0][TEX_W * y + x] = 65536 * 254 * (x != y && x != TEX_W - y);
			//texture[1][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			//texture[2][TEX_W * y + x] = 256 * xycolor + 65536 * xycolor;
			//texture[3][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			//texture[2][TEX_W * y + x] = xorcolor * xorcolor * 6553;
			texture[0][TEX_W * y + x] = xycolor + 256 * xycolor;
			texture[1][TEX_W * y + x] = (xycolor + 256 * xycolor) >> 8;
			texture[2][TEX_W * y + x] = xorcolor * xorcolor * 655;
			texture[3][TEX_W * y + x] = xorcolor * xorcolor * 65536; // NEEDED FOR RAINBOW
			//texture[1][TEX_W * y + x] = (xycolor + 256 * xycolor) << 6; // TRIPPY SQUARES
			*/
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
