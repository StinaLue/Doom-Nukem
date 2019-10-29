/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:47:59 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/29 13:15:17 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libbmp.h"
#include "doom.h"
#include <math.h>

void	fill_tex_loop(int tex[TEX_W * TEX_H], char raw[(TEX_W * TEX_H) * 4], \
			char buf[5])
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
	if ((simpleparse_bmp("textures/flower.bmp", texture[0])) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	if ((simpleparse_bmp("textures/mandala.bmp", texture[1])) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	if ((simpleparse_bmp("textures/weirdo.bmp", texture[2])) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	if ((simpleparse_bmp("textures/brick.bmp", texture[3])) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	//load_tex("textures/friends1.txt", texture[0]);
	//load_tex("textures/friends2.txt", texture[1]);
	//load_tex("textures/friends3.txt", texture[2]);
	//load_tex("textures/friends4.txt", texture[3]);
	while (x < TEX_W)
	{
		y = 0;
		while (y < TEX_H)
		{
			xorcolor = x * y / TEX_H - 2333 * 128;
			xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
			texture[4][TEX_W * y + x] = xycolor + 256 * xycolor;
			texture[5][TEX_W * y + x] = (xycolor + 256 * xycolor) >> 8;
			texture[6][TEX_W * y + x] = xorcolor * xorcolor * 655;
			texture[7][TEX_W * y + x] = xorcolor * xorcolor * 65536;
			y++;
		}
		x++;
	}
}

void	fill_texel(t_player const *player, t_wall_find *find_wall,
					t_raycast *raycast, t_data *data)
{
	int		d;
	int		y;

	y = raycast->start_line;
	while (y < raycast->end_line)
	{
		d = y - (WIN_HEIGHT / 2) + (raycast->height / 2)
			- (player->up_and_down - player->crouch);
		data->tex_y = (((d) * (TEX_H)) / (raycast->height));
		if (data->tex_x >= 0 && data->tex_y >= 0 && data->tex_x < TEX_W && \
			data->tex_y < TEX_H)
		{
			data->color =
				data->texture[data->tex_num][TEX_H * (data->tex_y) \
					+ data->tex_x];
			if (find_wall->side == 1)
				data->color = (data->color >> 1) & 8355711;
			fill_pix(data->img_ptr, raycast->current_x, y, data->color);
		}
		//else
		//	fill_pix(data->img_ptr, raycast->current_x, y, 0x000000);
		y++;
	}
	/* int floor;

	floor = raycast->end_line;
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
		//4 different wall directions possible
		if (find_wall->side == 0 && raycast->dir_x > 0)
		{
			floorXWall = raycast->map_x;
			floorYWall = raycast->map_y + find_wall->wall_x;
		}
		else if (find_wall->side == 0 && raycast->dir_x < 0)
		{
			floorXWall = raycast->map_x + 1.0;
			floorYWall = raycast->map_y + find_wall->wall_x;
		}
		else if (find_wall->side == 1 && raycast->dir_y > 0)
		{
			floorXWall = raycast->map_x + find_wall->wall_x;
			floorYWall = raycast->map_y;
		}
		else
		{
			floorXWall = raycast->map_x + find_wall->wall_x;
			floorYWall = raycast->map_y + 1.0;
		}
		//printf("mapx: %d, mapy: %d, find_wall->wall_x: %f\n", raycast->map_x, raycast->map_y, find_wall->wall_x);
		//printf("floorx: %f, floory: %f, find_wall->wall_x: %f\n", floorXWall, floorYWall, find_wall->wall_x);
		double distWall, distPlayer, currentDist;
		distWall = find_wall->distance_wall;
		distPlayer = 0.0;
			if (raycast->end_line < 0)
				raycast->end_line = WIN_HEIGHT; //becomes < 0 when the integer overflows
			//draw the floor from raycast->end_line to the bottom of the screen
			//printf("end_line: %d, WIN_HEIGHT: %d\n", raycast->end_line, WIN_HEIGHT);
			for(int y = raycast->end_line + 1; y < WIN_HEIGHT; y++)
		{
			currentDist = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
			double weight = (currentDist - distPlayer) / (distWall - distPlayer);
			double currentFloorX = weight * floorXWall + (1.0 + weight) * player->x;
			double currentFloorY = weight * floorYWall + (1.0 + weight) * player->y;
			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * TEX_W) % TEX_W;
			//printf("floortexx: %d, currentfloor: %f, TEX_W: %d\n", floorTexX, currentFloorX, TEX_W);
			floorTexY = (int)(currentFloorY * TEX_H) % TEX_H;
			//int checkerBoardPattern = (int)(currentFloorX + currentFloorY) % 2;
			//if(checkerBoardPattern == 0)
		//		data->tex_num = 3;
	//		else
				data->tex_num = 4;
			//floor
			//fill_texel(player, find_wall, raycast, data);
			//if (find_wall->side == 1)
			data->color = data->texture[data->tex_num][TEX_W * floorTexY + floorTexX];
			printf("color: %d\n", data->color);
			fill_pix(data->img_ptr, floorTexX, floorTexY, data->color);
		//data->texture[WIN_HEIGHT - y][find_wall->wall_x] = data->texture[data->tex_num][TEX_W * floorTexY + floorTexX]; //color
		//buffer[y][x] = (texture[floorTexture][TEX_W * floorTexY + floorTexX] >> 1) & 8355711;
		// buffer[WIN_HEIGHT - y][x] = texture[6][TEX_W * floorTexY + floorTexX]; // ceiling
		} */
}

void	draw_tex(t_player const *player, t_wall_find *find_wall, \
			t_raycast *raycast, t_data *data)
{
	int		offset;

	offset = (*data->map_ptr)[raycast->map_y][raycast->map_x] == 2 ? 4 : 0;
	if ((is_valid_wall((*data->map_ptr)[raycast->map_y][raycast->map_x])) == 1)
		data->tex_num = 0 + offset;
	if (find_wall->side == 0 && player->x < raycast->map_x)
		data->tex_num = 1 + offset;
	if (find_wall->side == 1)
		data->tex_num = (player->y < raycast->map_y ? 2 + offset : 3 + offset);
	if (find_wall->side == 0)
		find_wall->wall_x = player->y + find_wall->distance_wall * raycast->dir_y;
	else
		find_wall->wall_x = player->x + find_wall->distance_wall * raycast->dir_x;
	find_wall->wall_x -= floor(find_wall->wall_x);
	data->tex_x = (int)(find_wall->wall_x * (double)TEX_W);
	if ((find_wall->side == 0 && raycast->dir_x > 0)
		|| (find_wall->side == 1 && raycast->dir_y < 0))
		data->tex_x = TEX_W - data->tex_x - 1;
	fill_texel(player, find_wall, raycast, data);
}
