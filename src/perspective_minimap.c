/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/28 17:36:45 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
double vxs(double xone, double yone, double xtwo, double ytwo)
{
	return (xone * ytwo - yone * xtwo);
}

t_vecdb intersect(t_vecdb one, t_vecdb two, t_vecdb three, t_vecdb four)
{
	t_vecdb intersection;
	intersection.x = vxs(vxs(one.x, one.y, two.x, two.y), one.x - two.x, vxs(three.x, three.y, four.x, four.y), three.x - four.x) / vxs(one.x - two.x, one.y - two.y, three.x - four.x, three.y - four.y);
	intersection.y = vxs(vxs(one.x, one.y, two.x, two.y), one.y - two.y, vxs(three.x, three.y, four.x, four.y), three.y - four.y) / vxs(one.x - two.x, one.y - two.y, three.x - four.x, three.y - four.y);
	return (intersection);
}
/*
t_vecdb	intersect(t_vecdb one, t_vecdb two, t_vecdb three, t_vecdb four)
{
	t_vecdb test;
	double tempx;
	double det;

	test.x = fn_cross(one.x, one.y, two.x, two.y);
	test.y = fn_cross(three.x, three.y, four.x, four.y);
	det = fn_cross(one.x - two.x, one.y - two.y, three.x - four.x, three.y - four.y);
	//test.x = fn_cross(test.x, one.x - two.x, test.y, three.x - four.x) / det;
	tempx = fn_cross(test.x, one.x - two.x, test.y, three.x - four.x) / det;
	test.y = fn_cross(test.x, one.y - two.y, test.y, three.y - four.y) / det;
	test.x = tempx;
	return (test);
}*/

t_vecdb rotate3d(t_vecdb vector, double angle)
{
	t_vecdb newvector;

	newvector.x = vector.x * cos(angle) + vector.y * sin(angle);
	newvector.y = vector.x * sin(angle) - vector.y * cos(angle);
	return (newvector);
}

void draw_vertical(t_vec top, t_vec bottom, SDL_Surface *surf, int color)
{
	//while (top.y <= bottom.y)
	while (top.y >= bottom.y)
	{
		fill_pix(surf, top.x, top.y, color);
		//top.y++;
		top.y--;
	}
}

void fill_wall_color(SDL_Surface *surf, const t_wall3d *transfo_wall, int color)
{
	//(void)color;
	//(void)surf;
	double x;
	t_vecdb current_top;
	t_vecdb current_bottom;

	if (transfo_wall->top_right.x < transfo_wall->top_left.x)
	{
		x = transfo_wall->top_right.x;
		while (x < transfo_wall->top_left.x)
		{
			//current_top.y = transfo_wall->top_right.y + (x - transfo_wall->top_right.x) * (long)(transfo_wall->top_left.y - transfo_wall->top_right.y) / (fabs(transfo_wall->top_left.x - transfo_wall->top_right.x) < 0.001 ? 1 : (transfo_wall->top_left.x - transfo_wall->top_right.x));
			//current_bottom.y = transfo_wall->bottom_right.y + (x - transfo_wall->top_right.x) * (long)(transfo_wall->bottom_left.y - transfo_wall->bottom_right.y) / (fabs(transfo_wall->top_left.x - transfo_wall->top_right.x) < 0.001 ? 1 : (transfo_wall->top_left.x - transfo_wall->top_right.x));
			current_top.y = transfo_wall->top_right.y + (x - transfo_wall->top_right.x) * (long)(transfo_wall->top_left.y - transfo_wall->top_right.y) / (abs(transfo_wall->top_left.x - transfo_wall->top_right.x) == 0 ? 1 : (transfo_wall->top_left.x - transfo_wall->top_right.x));
			current_bottom.y = transfo_wall->bottom_right.y + (x - transfo_wall->top_right.x) * (long)(transfo_wall->bottom_left.y - transfo_wall->bottom_right.y) / (abs(transfo_wall->top_left.x - transfo_wall->top_right.x) ==0 ? 1 : (transfo_wall->top_left.x - transfo_wall->top_right.x));
			if (fabs(current_top.y) < 0.0001)
				current_top.y = 0;
			if (fabs(current_bottom.y) < 0.0001)
				current_bottom.y = 0;
			current_top.x = x;
			current_bottom.x = x;
			if (current_top.y <= surf->h && current_bottom.y <= surf->h && current_top.x <= surf->w)
				draw_vertical(vecdb_to_vec(current_top), vecdb_to_vec(current_bottom), surf, color);
			x++;
		}
	}
}

void draw_perspective_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall3d transfo_wall; // need t_wall3d because we have to access more values than just x and y (top/bottom/left/right)
	t_wall wall_tmp;
	int i = 0;
	while (i < NB_WALLS) // looping through each existing wall
	{
		init_rotate_wall(&wall_tmp, &walls[i], player);
		if (!(wall_tmp.start_wall.x <= 0 && wall_tmp.end_wall.x <= 0))
		{
			if ((wall_tmp.start_wall.x <= 0 || wall_tmp.end_wall.x <= 0))
			{
				t_vecdb one = {wall_tmp.start_wall.y, wall_tmp.start_wall.x};
				t_vecdb two = {wall_tmp.end_wall.y, wall_tmp.end_wall.x};
				t_vecdb three = {-0.0001, 0.0001};
				t_vecdb four = {-20, 5};
				t_vecdb intersect1 = intersect(one, two, three, four);
				three.x = fabs(three.x);
				four.x = fabs(four.x);
				t_vecdb intersect2 = intersect(one, two, three, four);
				if (wall_tmp.start_wall.x <= 0)
				{
					if (intersect1.y > 0)
					{
						wall_tmp.start_wall.y = intersect1.x;
						wall_tmp.start_wall.x = intersect1.y;
					}
					else
					{
						wall_tmp.start_wall.y = intersect2.x;
						wall_tmp.start_wall.x = intersect2.y;
					}
				}
				if (wall_tmp.end_wall.x <= 0)
				{
					if (intersect1.y > 0)
					{
						wall_tmp.end_wall.y = intersect1.x;
						wall_tmp.end_wall.x = intersect1.y;
					}
					else
					{
						wall_tmp.end_wall.y = intersect2.x;
						wall_tmp.end_wall.x = intersect2.y;
					}
				}
			}
			if (fabs(wall_tmp.start_wall.x) < 0.0001)
				wall_tmp.start_wall.x = 1;
			if (fabs(wall_tmp.end_wall.x) < 0.0001)
				wall_tmp.end_wall.x = 1;

			double xscale1 = HFOV / wall_tmp.start_wall.x;
			double xscale2 = HFOV / wall_tmp.end_wall.x;

			double yscale1 = VFOV / wall_tmp.start_wall.x;
			double yscale2 = VFOV / wall_tmp.end_wall.x;

			int x1 = surf->w / 2 - (int)(wall_tmp.start_wall.y * xscale1);
			int x2 = surf->w / 2 - (int)(wall_tmp.end_wall.y * xscale2);
			int y1a = surf->h / 2 - (int)((wall_tmp.start_wall.x - 10) * yscale1);
			int y2a = surf->h / 2 - (int)((wall_tmp.end_wall.x - 10) * yscale2);
			int y1b = surf->h / 2 - (int)((wall_tmp.start_wall.x + 10) * yscale1);
			int y2b = surf->h / 2 - (int)((wall_tmp.end_wall.x + 10) * yscale2);
			//double y1a = -(surf->h) / wall_tmp.start_wall.x;
			//double y2a = -(surf->h) / wall_tmp.end_wall.x;
			//double y1b = (surf->h) / wall_tmp.start_wall.x;
			//double y2b = (surf->h) / wall_tmp.end_wall.x;
			transfo_wall.top_left.x = x1;
			transfo_wall.top_left.y = y1a + player->view_z;
			transfo_wall.top_right.x = x2;
			transfo_wall.top_right.y = y2a + player->view_z;
			transfo_wall.bottom_left.x = x1;
			transfo_wall.bottom_left.y = y1b + player->view_z;
			transfo_wall.bottom_right.x = x2;
			transfo_wall.bottom_right.y = y2b + player->view_z;
			if (ft_strncmp(surf->userdata, "yescolor", 8) == 0 && (transfo_wall.top_left.x > 0 && transfo_wall.top_right.x))
				fill_wall_color(surf, &transfo_wall, walls[i].color);
			draw_line(transfo_wall.top_left, transfo_wall.top_right, surf, walls[i].color); // drawing a line for each line around wall
			draw_line(transfo_wall.top_right, transfo_wall.bottom_right, surf, walls[i].color);
			draw_line(transfo_wall.bottom_right, transfo_wall.bottom_left, surf, walls[i].color);
			draw_line(transfo_wall.bottom_left, transfo_wall.top_left, surf, walls[i].color);
			/*draw_line(vecdb_to_vec(transfo_wall.top_left), vecdb_to_vec(transfo_wall.top_right), surf, walls[i].color); // drawing a line for each line around wall
			draw_line(vecdb_to_vec(transfo_wall.top_right), vecdb_to_vec(transfo_wall.bottom_right), surf, walls[i].color);
			draw_line(vecdb_to_vec(transfo_wall.bottom_right), vecdb_to_vec(transfo_wall.bottom_left), surf, walls[i].color);
			draw_line(vecdb_to_vec(transfo_wall.bottom_left), vecdb_to_vec(transfo_wall.top_left), surf, walls[i].color);
			*/
		}
		i++;
	}
}