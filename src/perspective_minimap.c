/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/15 18:04:06 by sluetzen         ###   ########.fr       */
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
	t_vecdb tmp;
	double det;

	test.x = fn_cross(one.x, one.y, two.x, two.y);
	test.y = fn_cross(three.x, three.y, four.x, four.y);
	det = fn_cross(one.x - two.x, one.y - two.y, three.x - four.x, three.y - four.y);
	tmp.x = fn_cross(test.x, one.x - two.x, test.y, three.x - four.x) / det;
	test.y = fn_cross(test.x, one.y - two.y, test.y, three.y - four.y) / det;
	test.x = tmp.x;
	return (test);
}

t_vecdb	rotate3d(t_vecdb vector, double angle)
{
	t_vecdb newvector;

	newvector.x = vector.x * cos(angle) + vector.y * sin(angle);
	newvector.y = vector.x * sin(angle) - vector.y * cos(angle);
	return (newvector);
}

void	draw_perspective_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall3d transfo_wall; // need t_wall3d because we have to access more values than just x and y (top/bottom/left/right)
	(void)player;
	int i = 0;
	while (i < NB_WALLS) // looping through each existing wall
	{
		t_vecdb startwall;
		t_vecdb endwall;
		t_vecdb rotstartwall;
		t_vecdb rotendwall;

		startwall.x = (double)walls[i].start_wall.x - player->pos.x;
		startwall.y = (double)walls[i].start_wall.y - player->pos.y;

		endwall.x = (double)walls[i].end_wall.x - player->pos.x;
		endwall.y = (double)walls[i].end_wall.y - player->pos.y;
		
		rotstartwall = rotate3d(startwall, player->angle); // rotate3d and rotate2d is the same!
		rotendwall = rotate3d(endwall, player->angle);
		
		if (rotstartwall.x > 0 || rotendwall.x > 0)
		{
			t_vecdb one = {rotstartwall.y, rotstartwall.x};
			t_vecdb two = {rotendwall.y, rotendwall.x};
			t_vecdb three = {-0.0001, 0.0001};
			t_vecdb four = {-20, 5};
			t_vecdb intersect1 = intersect(one, two, three, four);
			three.x = fabs(three.x);
			four.x = fabs(four.x);
			t_vecdb intersect2 = intersect(one, two, three, four);
    		if (rotstartwall.x <= 0) 
			{
				if (intersect1.y > 0)
				{
					rotstartwall.y = intersect1.x;
					rotstartwall.x = intersect1.y;
				}
				else
				{
					rotstartwall.y = intersect2.x;
					rotstartwall.x = intersect2.y;
				}
			}
   			if (rotendwall.x <= 0)
			{
				if (intersect1.y > 0)
				{
					rotendwall.y = intersect1.x;
					rotendwall.x = intersect1.y;
				}
				else
				{
					rotendwall.y = intersect2.x;
					rotendwall.x = intersect2.y;
				}
			}
			double x1 = -rotstartwall.y * 16 / rotstartwall.x; // perspective works because of division of x and y coordinates by z -> matrix
			double x2 = -rotendwall.y * 16 / rotendwall.x; // use multiplication to change field of view: higher number = bigger fov
			double y1a = -50 / rotstartwall.x;
			double y2a = -50 / rotendwall.x;
			double y1b = 50 / rotstartwall.x;
			double y2b = 50 / rotendwall.x;
			transfo_wall.top_left.x = 50 + x1;
			transfo_wall.top_left.y = 50 + y1a;
			transfo_wall.top_right.x = 50 + x2;
			transfo_wall.top_right.y = 50 + y2a;
			transfo_wall.bottom_left.x = 50 + x1;
			transfo_wall.bottom_left.y = 50 + y1b;
			transfo_wall.bottom_right.x = 50 + x2;
			transfo_wall.bottom_right.y = 50 + y2b;
			draw_line(transfo_wall.top_left, transfo_wall.top_right, surf, walls[i].color); // drawing a line for each line around wall
			draw_line(transfo_wall.top_right, transfo_wall.bottom_right, surf, walls[i].color);
			draw_line(transfo_wall.bottom_right, transfo_wall.bottom_left, surf, walls[i].color);
			draw_line(transfo_wall.bottom_left, transfo_wall.top_left, surf, walls[i].color);
		}
		i++;
	}
}