/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/18 17:00:43 by phaydont         ###   ########.fr       */
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

t_vecdb simple_intersect(t_vecdb start, t_vecdb end, t_vecdb cross)
{
	t_vecdb	intersection;
	double	tmp;

	tmp = cross_product(start, end) / vxs(start.x - end.x, start.y - end.y, cross.x, cross.y);
	intersection.x = tmp * cross.x;
	intersection.y = tmp * cross.y;
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
	top.y = limit_value(top.y, 0, surf->h - 1);
	bottom.y = limit_value(bottom.y, 0, surf->h - 1);
	while (top.y >= bottom.y)
	{
		fill_pix(surf, top.x, top.y, color);
		top.y--;
	}
}

void	fill_wall_color(SDL_Surface *surf, const t_wall3d *display_wall, int color)
{
	double x;
	t_vec current_top;
	t_vec current_bottom;

	if (display_wall->top_right.x > display_wall->top_left.x)
	{
		x = display_wall->top_right.x;
		while (x > display_wall->top_left.x)
		{
			current_top.y = display_wall->top_right.y + (x - display_wall->top_right.x) * (long)(display_wall->top_left.y - display_wall->top_right.y) / (abs(display_wall->top_left.x - display_wall->top_right.x) == 0 ? 1 : (display_wall->top_left.x - display_wall->top_right.x));
			current_bottom.y = display_wall->bottom_right.y + (x - display_wall->top_right.x) * (long)(display_wall->bottom_left.y - display_wall->bottom_right.y) / (abs(display_wall->top_left.x - display_wall->top_right.x) ==0 ? 1 : (display_wall->top_left.x - display_wall->top_right.x));
			current_top.x = x;
			current_bottom.x = x;
			draw_vertical(current_top, current_bottom, surf, color);
			x--;
		}
	}
}

int		intersect_fov(t_wall *wall, t_vecdb fov)
{
	if (cross_product(wall->end_wall, fov) > 0)
	{
		if (cross_product(wall->start_wall, fov) > 0)
			return (0);
		wall->end_wall = simple_intersect(wall->start_wall, wall->end_wall, fov);
	}
	else if (wall->end_wall.y < 0)
		return (0);

	fov.x *= -1;
	if (cross_product(wall->start_wall, fov) < 0)
	{
		if (cross_product(wall->end_wall, fov) < 0)
			return (0);
		wall->start_wall = simple_intersect(wall->start_wall, wall->end_wall, fov);
	}
	else if (wall->start_wall.y < 0)
		return (0);

	return (1);
}

void	create_perspective_wall(t_wall3d *display_wall, t_wall wall, SDL_Surface *surf, t_player *player)
{
	double	fov_ratio;
	int		x;
	int		y;
	double	surf_center;

	surf_center = ((double)surf->w - 1) / 2;

	fov_ratio = player->fov.y / player->fov.x / wall.start_wall.y;
	x = surf->w / 2 + wall.start_wall.x * fov_ratio * surf_center;
	y = fov_ratio * surf->w;

	display_wall->top_left.x = x;
	display_wall->top_left.y = surf->h / 2 - player->view_z + y;
	display_wall->bottom_left.x = display_wall->top_left.x;
	display_wall->bottom_left.y = surf->h / 2 - player->view_z - y;

	fov_ratio = player->fov.y / player->fov.x / wall.end_wall.y;
	x = surf->w / 2 + wall.end_wall.x * fov_ratio * surf_center;
	y = fov_ratio * surf->w;

	display_wall->top_right.x = x;
	display_wall->top_right.y = surf->h / 2 - player->view_z + y;
	display_wall->bottom_right.x = display_wall->top_right.x;
	display_wall->bottom_right.y = surf->h / 2 - player->view_z - y;
}

void	draw_3dwall(t_wall3d display_wall, SDL_Surface *surf, t_wall wall)
{
	if (ft_strncmp(surf->userdata, "yescolor", 8) == 0)
		fill_wall_color(surf, &display_wall, wall.color);
	draw_line(display_wall.top_left, display_wall.top_right, surf, wall.color); // drawing a line for each line around wall
	draw_line(display_wall.top_right, display_wall.bottom_right, surf, wall.color);
	draw_line(display_wall.bottom_right, display_wall.bottom_left, surf, wall.color);
	draw_line(display_wall.bottom_left, display_wall.top_left, surf, wall.color);
}

void	draw_perspective_view(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall wall_tmp;
	int i = 0;
	t_wall3d display_wall;
	t_vecdb map_center;

	map_center.x = surf->w / 2 + 0.5;
	map_center.y = surf->h / 2 + 0.5;
	if (player->helper)
	{
		//draws 2d fov helper
		draw_line(create_vec(map_center.x,map_center.y), create_vec(map_center.x+player->fov.x,map_center.y+player->fov.y), surf, 0x999999);
		draw_line(create_vec(map_center.x,map_center.y), create_vec(map_center.x-player->fov.x,map_center.y+player->fov.y), surf, 0x999999);
		fill_pix(surf, map_center.x, map_center.y, 0x8800FF);
	}

	while (i < NB_WALLS) // looping through each existing wall
	{
		init_rotate_wall(&wall_tmp, &walls[i], player);
		if ((wall_tmp.start_wall.y > 0 || wall_tmp.end_wall.y > 0) && intersect_fov(&wall_tmp, player->fov)) //wall is at least partly in front of us && crosses the field of view
		{
			//printf("pos:%.50f,%.50f\n",player->pos.x, player->pos.y);
			//printf("fov:%d,%d\n",player->fov.x, player->fov.y);
			create_perspective_wall(&display_wall, wall_tmp, surf, player);
			draw_3dwall(display_wall, surf, walls[i]);

			if (player->helper)
			{
				//draws 2d map
				wall_tmp.start_wall.x = map_center.x + wall_tmp.start_wall.x;
				wall_tmp.start_wall.y = map_center.y + wall_tmp.start_wall.y;
				wall_tmp.end_wall.x = map_center.x + wall_tmp.end_wall.x;
				wall_tmp.end_wall.y = map_center.y + wall_tmp.end_wall.y;
				draw_line(vecdb_to_vec(wall_tmp.start_wall), vecdb_to_vec(wall_tmp.end_wall), surf, walls[i].color / 2);
			}
		}
		i++;
	}
}
