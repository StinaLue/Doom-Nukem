/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/04 11:53:31 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
double vxs(double xstart, double ystart, double xtwo, double ytwo)
{
	return (xstart * ytwo - ystart * xtwo);
}

t_vecdb intersect(t_vecdb start, t_vecdb end, t_vecdb origin, t_vecdb cross)
{
	t_vecdb intersection;
	intersection.x = vxs(vxs(start.x, start.y, end.x, end.y), start.x - end.x, vxs(origin.x, origin.y, cross.x, cross.y), origin.x - cross.x) / vxs(start.x - end.x, start.y - end.y, origin.x - cross.x, origin.y - cross.y);
	intersection.y = vxs(vxs(start.x, start.y, end.x, end.y), start.y - end.y, vxs(origin.x, origin.y, cross.x, cross.y), origin.y - cross.y) / vxs(start.x - end.x, start.y - end.y, origin.x - cross.x, origin.y - cross.y);
	return (intersection);
}

int	limit_value(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}

void draw_vertical(t_vec top, t_vec bottom, SDL_Surface *surf, int color)
{
	//while (top.y <= bottom.y)
	top.y = limit_value(top.y, 0, surf->h - 1);
	bottom.y = limit_value(bottom.y, 0, surf->h - 1);
	while (top.y >= bottom.y)
	{
		fill_pix(surf, top.x, top.y, color);
		//top.y++;
		top.y--;
	}
}

void fill_wall_color(SDL_Surface *surf, const t_wall3d *transfo_wall, int color)
{
	double x;
	t_vec current_top;
	t_vec current_bottom;

	if (transfo_wall->top_right.x > transfo_wall->top_left.x)
	{
		x = transfo_wall->top_right.x;
		while (x > transfo_wall->top_left.x)
		{
			current_top.y = transfo_wall->top_right.y + (x - transfo_wall->top_right.x) * (long)(transfo_wall->top_left.y - transfo_wall->top_right.y) / (abs(transfo_wall->top_left.x - transfo_wall->top_right.x) == 0 ? 1 : (transfo_wall->top_left.x - transfo_wall->top_right.x));
			current_bottom.y = transfo_wall->bottom_right.y + (x - transfo_wall->top_right.x) * (long)(transfo_wall->bottom_left.y - transfo_wall->bottom_right.y) / (abs(transfo_wall->top_left.x - transfo_wall->top_right.x) ==0 ? 1 : (transfo_wall->top_left.x - transfo_wall->top_right.x));
			current_top.x = x;
			current_bottom.x = x;
			draw_vertical(current_top, current_bottom, surf, color);
			x--;
		}
	}
}

void draw_perspective_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall wall_tmp;
	int i = 0;

	//t_vecdb map_center;
	//map_center.x = surf->w / 2 +0.5;
	//map_center.y = surf->h / 2 +0.5;

	//draw_line(create_vec(map_center.x,map_center.y), create_vec(map_center.x+500,map_center.y+500), surf, 0x999999);
	//draw_line(create_vec(map_center.x,map_center.y), create_vec(map_center.x-500,map_center.y+500), surf, 0x999999);

	while (i < NB_WALLS) // looping through each existing wall
	{
		t_wall3d transfo_wall;
		(void)transfo_wall;
		init_rotate_wall(&wall_tmp, &walls[i], player);
		if (wall_tmp.start_wall.y > 0 || wall_tmp.end_wall.y > 0)
		{
			t_vecdb origin = {0, 0};
			t_vecdb crossleft = {-20, 20};
			t_vecdb crossright = {20, 20};
			t_vecdb intersect1 = intersect(wall_tmp.start_wall, wall_tmp.end_wall, origin, crossleft);
			t_vecdb intersect2 = intersect(wall_tmp.start_wall, wall_tmp.end_wall, origin, crossright);
			(void)intersect2;

			if (wall_tmp.start_wall.x*crossleft.y - wall_tmp.start_wall.y*crossleft.x < 0)
				wall_tmp.start_wall.y = -5555;
			if (wall_tmp.end_wall.x*crossleft.y - wall_tmp.end_wall.y*crossleft.x < 0)
				wall_tmp.end_wall.y = -5555;
			if (wall_tmp.start_wall.y == -5555 && wall_tmp.end_wall.y == -5555)
			{
				i++;
				continue ;
			}
			//intersect1 = intersect(wall_tmp.start_wall, wall_tmp.end_wall, origin, crossleft);
			if (wall_tmp.start_wall.y == -5555)
				wall_tmp.start_wall = intersect1;
			if (wall_tmp.end_wall.y == -5555)
				wall_tmp.end_wall = intersect1;

			if (wall_tmp.start_wall.x*crossright.y - wall_tmp.start_wall.y*crossright.x > 0)
				wall_tmp.start_wall.y = -5555;
			if (wall_tmp.end_wall.x*crossright.y - wall_tmp.end_wall.y*crossright.x > 0)
				wall_tmp.end_wall.y = -5555;
			if (wall_tmp.start_wall.y == -5555 && wall_tmp.end_wall.y == -5555)
			{
				i++;
				continue ;
			}
			//intersect2 = intersect(wall_tmp.start_wall, wall_tmp.end_wall, origin, crossright);
			if (wall_tmp.start_wall.y == -5555)
				wall_tmp.start_wall = intersect2;
			if (wall_tmp.end_wall.y == -5555)
				wall_tmp.end_wall = intersect2;

			int	x1 = (1 + wall_tmp.start_wall.x / wall_tmp.start_wall.y) * surf->w / 2 - 1;
			int	y1 = 1 / wall_tmp.start_wall.y * surf->w;
			int	x2 = (1 + wall_tmp.end_wall.x / wall_tmp.end_wall.y) * surf->w / 2 - 1;
			int	y2 = 1 / wall_tmp.end_wall.y * surf->w;

			transfo_wall.top_left.x = x1;
			transfo_wall.top_left.y = surf->h / 2 - player->view_z + y1;
			transfo_wall.bottom_left.x = transfo_wall.top_left.x;
			transfo_wall.bottom_left.y = surf->h / 2 - player->view_z - y1;
			transfo_wall.top_right.x = x2;
			transfo_wall.top_right.y = surf->h / 2 - player->view_z + y2;
			transfo_wall.bottom_right.x = transfo_wall.top_right.x;
			transfo_wall.bottom_right.y = surf->h / 2 - player->view_z - y2;
			
			if (ft_strncmp(surf->userdata, "yescolor", 8) == 0)
				fill_wall_color(surf, &transfo_wall, walls[i].color);

			draw_line(transfo_wall.top_left, transfo_wall.top_right, surf, walls[i].color); // drawing a line for each line around wall
			draw_line(transfo_wall.top_right, transfo_wall.bottom_right, surf, walls[i].color);
			draw_line(transfo_wall.bottom_right, transfo_wall.bottom_left, surf, walls[i].color);
			draw_line(transfo_wall.bottom_left, transfo_wall.top_left, surf, walls[i].color);

			/*wall_tmp.start_wall.x = map_center.x + wall_tmp.start_wall.x;
			wall_tmp.start_wall.y = map_center.y + wall_tmp.start_wall.y;
			wall_tmp.end_wall.x = map_center.x + wall_tmp.end_wall.x;
			wall_tmp.end_wall.y = map_center.y + wall_tmp.end_wall.y;
			draw_line(vecdb_to_vec(wall_tmp.start_wall), vecdb_to_vec(wall_tmp.end_wall), surf, walls[i].color);
			fill_pix(surf, map_center.x, map_center.y, 0x8800FF);*/
			
			//draw_line(create_vec(x1, 5), create_vec(x2, 5), surf, walls[i].color);
			
			/*
			//double xscale1 = HFOV / wall_tmp.start_wall.x;
			//double xscale2 = HFOV / wall_tmp.end_wall.x;

			double yscale1 = VFOV / wall_tmp.start_wall.x;
			double yscale2 = VFOV / wall_tmp.end_wall.x;

			int x1 = surf->w / 2 + (int)(wall_tmp.start_wall.y / wall_tmp.start_wall.x * surf->w/2);
			int x2 = surf->w / 2 + (int)(wall_tmp.end_wall.y / wall_tmp.end_wall.x * surf->w/2);
			if (x1 >= x2)
			{
				int y1a = surf->h / 2 - (int)((wall_tmp.start_wall.x - 10) * yscale1);
				int y2a = surf->h / 2 - (int)((wall_tmp.end_wall.x - 10) * yscale2);
				int y1b = surf->h / 2 - (int)((wall_tmp.start_wall.x + 10) * yscale1);
				int y2b = surf->h / 2 - (int)((wall_tmp.end_wall.x + 10) * yscale2);
				transfo_wall.top_left.x = (int)x1;
				transfo_wall.top_left.y = (int)y1a + player->view_z;
				transfo_wall.top_right.x = (int)x2;
				transfo_wall.top_right.y = (int)y2a + player->view_z;
				transfo_wall.bottom_left.x = (int)x1;
				transfo_wall.bottom_left.y = (int)y1b + player->view_z;
				transfo_wall.bottom_right.x = (int)x2;
				transfo_wall.bottom_right.y = (int)y2b + player->view_z;
				if (ft_strncmp(surf->userdata, "yescolor", 8) == 0)
					fill_wall_color(surf, &transfo_wall, walls[i].color);
				draw_line(transfo_wall.top_left, transfo_wall.top_right, surf, walls[i].color); // drawing a line for each line around wall
				draw_line(transfo_wall.top_right, transfo_wall.bottom_right, surf, walls[i].color);
				draw_line(transfo_wall.bottom_right, transfo_wall.bottom_left, surf, walls[i].color);
				draw_line(transfo_wall.bottom_left, transfo_wall.top_left, surf, walls[i].color);
			}*/

		}
		i++;
	}
}