/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/19 18:38:38 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


double	fn_cross(double xone, double yone, double xtwo, double ytwo)
{
	return(xone * ytwo - yone * xtwo);
}

t_vecdb	intersect(t_vecdb one, t_vecdb two, t_vecdb three, t_vecdb four)
{
	t_vecdb test;
	double det;

	test.x = fn_cross(one.x, one.y, two.x, two.y);
	test.y = fn_cross(three.x, three.y, four.x, four.y);
	det = fn_cross(one.x - two.x, one.y - two.y, three.x - four.x, three.y - four.y);
	test.x = fn_cross(test.x, one.x - two.x, test.y, three.x - four.x) / det;
	test.y = fn_cross(test.x, one.y - two.y, test.y, three.y - four.y) / det;
	return (test);
}

t_vecdb	rotate3d(t_vecdb vector, double angle)
{
	t_vecdb newvector;

	newvector.x = vector.x * cos(angle) + vector.y * sin(angle);
	newvector.y = vector.x * sin(angle) - vector.y * cos(angle);
	return (newvector);
}

void	transform_to_winsize(t_wall3d *wall3d, int maxw, int maxh)
{
	if (wall3d->top_left.x >= maxw)
		wall3d->top_left.x = maxw;
	if (wall3d->top_left.y >= maxh)
		wall3d->top_left.y = maxh;
	if (wall3d->top_right.x >= maxw)
		wall3d->top_right.x = maxw;
	if (wall3d->top_right.y >= maxh)
		wall3d->top_right.y = maxh;
	if (wall3d->bottom_left.x >= maxw)
		wall3d->bottom_left.x = maxw;
	if (wall3d->bottom_left.y >= maxh)
		wall3d->bottom_left.y = maxh;
	if (wall3d->bottom_right.x >= maxw)
		wall3d->bottom_right.x = maxw;
	if (wall3d->bottom_right.y >= maxh)
		wall3d->bottom_right.y = maxh;

	if (wall3d->top_left.x < 0)
		wall3d->top_left.x = 0;
	if (wall3d->top_left.y < 0)
		wall3d->top_left.y = 0;
	if (wall3d->top_right.x < 0)
		wall3d->top_right.x = 0;
	if (wall3d->top_right.y < 0)
		wall3d->top_right.y = 0;
	if (wall3d->bottom_left.x < 0)
		wall3d->bottom_left.x = 0;
	if (wall3d->bottom_left.y < 0)
		wall3d->bottom_left.y = 0;
	if (wall3d->bottom_right.x < 0)
		wall3d->bottom_right.x = 0;
	if (wall3d->bottom_right.y < 0)
		wall3d->bottom_right.y = 0;
}

void	draw_perspective_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall3d transfo_wall; // need t_wall3d because we have to access more values than just x and y (top/bottom/left/right)
	t_wall wall_tmp;
	int i = 0;
	while (i < NB_WALLS) // looping through each existing wall
	{
		init_rotate_wall(&wall_tmp, &walls[i], player);
		if (wall_tmp.start_wall.x > 0 || wall_tmp.end_wall.x > 0)
		{
			t_vecdb one = {wall_tmp.start_wall.y, wall_tmp.start_wall.x};
			t_vecdb two = {wall_tmp.end_wall.y, wall_tmp.end_wall.x};
			//t_vecdb three = {-0.0001, 0.0001};
			t_vecdb three = {0, 0};
			t_vecdb four = {-600, 5};
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
			double x1 = -wall_tmp.start_wall.y * (surf->w / 2) / wall_tmp.start_wall.x; // perspective works because of division of x and y coordinates by z -> matrix
			double x2 = -wall_tmp.end_wall.y * (surf->w / 2) / wall_tmp.end_wall.x; // use multiplication to change field of view: higher number = bigger fov
			double y1a = -(surf->h ) / wall_tmp.start_wall.x;
			double y2a = -(surf->h ) / wall_tmp.end_wall.x;
			double y1b = (surf->h ) / wall_tmp.start_wall.x;
			double y2b = (surf->h ) / wall_tmp.end_wall.x;
			transfo_wall.top_left.x = (surf->w / 2) + x1;
			transfo_wall.top_left.y = (surf->h / 2) + y1a;
			transfo_wall.top_right.x = (surf->w / 2) + x2;
			transfo_wall.top_right.y = (surf->h / 2) + y2a;
			transfo_wall.bottom_left.x = (surf->w / 2) + x1;
			transfo_wall.bottom_left.y = (surf->h / 2) + y1b;
			transfo_wall.bottom_right.x = (surf->w / 2) + x2;
			transfo_wall.bottom_right.y = (surf->h / 2) + y2b;
			//transform_to_winsize(&transfo_wall, surf->w, surf->h);
			draw_line(vecdb_to_vec(transfo_wall.top_left), vecdb_to_vec(transfo_wall.top_right), surf, walls[i].color); // drawing a line for each line around wall
			draw_line(vecdb_to_vec(transfo_wall.top_right), vecdb_to_vec(transfo_wall.bottom_right), surf, walls[i].color);
			draw_line(vecdb_to_vec(transfo_wall.bottom_right), vecdb_to_vec(transfo_wall.bottom_left), surf, walls[i].color);
			draw_line(vecdb_to_vec(transfo_wall.bottom_left), vecdb_to_vec(transfo_wall.top_left), surf, walls[i].color);
		}
		i++;
	}
}