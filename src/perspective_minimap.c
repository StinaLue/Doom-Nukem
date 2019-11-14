/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/14 21:38:07 by sluetzen         ###   ########.fr       */
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

void	draw_perspective_minimap(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall3d transfo_wall; // need t_wall3d because we have to access more values than just x and y (top/bottom/left/right)
	(void)player;
	int i = 0;
	while (i < NB_WALLS) // looping through each existing wall
	{
		double tx1 = walls[i].start_wall.x - player->pos.x; // x distance between player and startwall
		double ty1 = walls[i].start_wall.y - player->pos.y; // y distance between player and startwall

		double tx2 = walls[i].end_wall.x - player->pos.x; // x distance between player and endwall
		double ty2 = walls[i].end_wall.y - player->pos.y; // y distance between player and endwall

		double tz1 = tx1 * cos(player->angle) + ty1 * sin(player->angle); // rotationvalue startwall
		double tz2 = tx2 * cos(player->angle) + ty2 * sin(player->angle); // rotationvalue endwall

		tx1 = tx1 * sin(player->angle) - ty1 * cos(player->angle); // some mathematic shit
		tx2 = tx2 * sin(player->angle) - ty2 * cos(player->angle);
		/* 
		if (tz1 == 0)
			tz1 = 0.00001;
		if (tz2 == 0)
			tz2 = 0.00001; */
		if (tz1 > 0 || tz2 > 0)
		{
			t_vecdb one = {tx1, tz1};
			t_vecdb two = {tx2, tz2};
			t_vecdb three = {-0.0001, 0.0001};
			t_vecdb four = {-20, 5};
			t_vecdb i1 = intersect(one, two, three, four);
			three.x = fabs(three.x);
			four.x = fabs(four.x);
			t_vecdb i2 = intersect(one, two, three, four);
			//CALL Intersect(tx1,tz1, tx2,tz2, -0.0001,0.0001, -20,5, ix1,iz1)
    		//CALL Intersect(tx1,tz1, tx2,tz2,  0.0001,0.0001,  20,5, ix2,iz2)
    		if (tz1 <= 0) 
			{
				if (i1.y > 0)
				{
					tx1=i1.x;
					tz1=i1.y;
				}
				else
				{
					tx1=i2.x;
					tz1=i2.y;
				}
			}
   			if (tz2 <= 0)
			{
				if (i1.y > 0)
				{
					tx2=i1.x;
					tz2=i1.y;
				}
				else
				{
					tx2=i2.x;
					tz2=i2.y;
				}
			}
			double x1 = -tx1 * 16 / tz1; // perspective works because of division of x and y coordinates by z -> matrix
			double x2 = -tx2 * 16 / tz2;
			double y1a = -50 / tz1;
			double y2a = -50 / tz2;
			double y1b = 50 / tz1;
			double y2b = 50 / tz2;
			transfo_wall.top_left.x = 50 + x1;
			transfo_wall.top_left.y = 50 + y1a;
			transfo_wall.top_right.x = 50 + x2;
			transfo_wall.top_right.y = 50 + y2a;
			transfo_wall.bottom_left.x = 50 + x1;
			transfo_wall.bottom_left.y = 50 + y1b;
			transfo_wall.bottom_right.x = 50 + x2;
			transfo_wall.bottom_right.y = 50 + y2b;
			draw_line(transfo_wall.top_left, transfo_wall.top_right, surf, 0xFFFFFF); // drawing a line for each line around wall
			draw_line(transfo_wall.top_right, transfo_wall.bottom_right, surf, 0xFFFFFF);
			draw_line(transfo_wall.bottom_right, transfo_wall.bottom_left, surf, 0xFFFFFF);
			draw_line(transfo_wall.bottom_left, transfo_wall.top_left, surf, 0xFFFFFF);
		}
		i++;
	}
}