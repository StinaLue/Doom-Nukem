/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 19:54:49 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

double			vxs(double xstart, double ystart, double xtwo, double ytwo)
{
	return (xstart * ytwo - ystart * xtwo);
}

t_vecdb			simple_intersect(t_vecdb start, t_vecdb end, t_vecdb cross)
{
	t_vecdb	intersection;
	double	tmp;
	double	vcp;

	tmp = 1;
	vcp = vxs(start.x - end.x, start.y - end.y, cross.x, cross.y);
	if (vcp != 0)
		tmp = cross_product(start, end) / vcp;
	intersection.x = tmp * cross.x;
	intersection.y = tmp * cross.y;
	return (intersection);
}

int				intersect_view(t_segment *wall, t_segment *intersect, \
									t_segment view)
{
	if (cross_product(wall->a, wall->b) > 0 \
		|| (wall->a.y <= 0 && wall->b.y <= 0))
		return (0);
	if (cross_product(wall->a, view.a) < 0)
	{
		if (cross_product(wall->b, view.a) < 0)
			return (0);
		intersect->a = simple_intersect(wall->a, wall->b, view.a);
	}
	else if (wall->a.y <= 0)
		return (0);
	else
		intersect->a = wall->a;
	if (cross_product(wall->b, view.b) > 0)
	{
		if (cross_product(wall->a, view.b) > 0)
			return (0);
		intersect->b = simple_intersect(wall->a, wall->b, view.b);
	}
	else if (wall->b.y <= 0)
		return (0);
	else
		intersect->b = wall->b;
	return (1);
}

void			create_perspective_wall(t_display_wall *dsp_wall, \
				SDL_Surface *surf, t_player *player, t_sector_node *sector)
{
	double		distance_ratio;
	double		x;
	double		top;
	double		bot;

	dsp_wall->fov_ratio = player->view.b.y / player->view.b.x;
	distance_ratio = dsp_wall->fov_ratio / dsp_wall->intersect.a.y * surf->w;
	x = dsp_wall->intersect.a.x * distance_ratio;
	top = (sector->ceiling_height - (player->posz + player->height)) \
									* distance_ratio;
	bot = (sector->floor_height - (player->posz + player->height)) \
									* distance_ratio;
	dsp_wall->top_left.x = (surf->w + x) / 2;
	dsp_wall->top_left.y = (surf->h + top) / 2 - player->view_z;
	dsp_wall->bottom_left.x = dsp_wall->top_left.x;
	dsp_wall->bottom_left.y = (surf->h + bot) / 2 - player->view_z;
	distance_ratio = dsp_wall->fov_ratio / dsp_wall->intersect.b.y * surf->w;
	x = dsp_wall->intersect.b.x * distance_ratio;
	top = (sector->ceiling_height - (player->posz + player->height)) \
									* distance_ratio;
	bot = (sector->floor_height - (player->posz + player->height)) \
									* distance_ratio;
	dsp_wall->top_right.x = (surf->w + x) / 2;
	dsp_wall->top_right.y = (surf->h + top) / 2 - player->view_z;
	dsp_wall->bottom_right.x = dsp_wall->top_right.x;
	dsp_wall->bottom_right.y = (surf->h + bot) / 2 - player->view_z;
}

void	draw_3dwall(t_display_wall *dsp_wall, SDL_Surface *surf)
{
	if (ft_strncmp(surf->userdata, "textured", 8) != 0)
	{
		draw_line(dsp_wall->top_left, dsp_wall->top_right, surf, 0xffffff);
		draw_line(dsp_wall->top_right, dsp_wall->bottom_right, surf, 0xffdddd);
		draw_line(dsp_wall->bottom_right, \
					dsp_wall->bottom_left, surf, 0xdddddd);
		draw_line(dsp_wall->bottom_left, dsp_wall->top_left, surf, 0xddddff);
	}
	else
		draw_texture(surf, dsp_wall->texture, dsp_wall, 0);
}

void			init_display_wall(t_display_wall *display, \
		t_wall_node *current_wall, t_view old_view, SDL_Surface **wall_textures)
{
	double	len;

	display->dist_left = display->intersect.a.y;
	display->dist_right = display->intersect.b.y;
	display->length = current_wall->length;
	display->texture = wall_textures[current_wall->tex_index];
	display->top_limit = old_view.top_limit;
	display->bot_limit = old_view.bot_limit;
	if (fabs(display->relative.a.x - display->relative.b.x) > 0.001)
	{
		len = display->relative.b.x - display->relative.a.x;
		display->start_pos = \
			(display->intersect.a.x - display->relative.a.x) / len;
		display->end_pos = \
			(display->intersect.b.x - display->relative.a.x) / len;
	}
	else if (fabs(display->relative.a.y - display->relative.b.y) > 0.001)
	{
		len = display->relative.b.y - display->relative.a.y;
		display->start_pos = \
				(display->intersect.a.y - display->relative.a.y) / len;
		display->end_pos = \
				(display->intersect.b.y - display->relative.a.y) / len;
	}
	else
	{
		display->start_pos = 0;
		display->end_pos = 1;
	}
}

int				min(int a, int b)
{
	return (a < b ? a : b);
}

int			max(int a, int b)
{
	return (a > b ? a : b);
}

t_view			create_view(t_display_wall *display, \
					t_display_wall *window, t_view old_view)
{
	t_view	view;
	int		*tmp_window;
	int		*tmp_display;

	view.fov = display->intersect;
	tmp_display = display->top_left.y < display->top_right.y ? \
					&display->top_right.y : &display->top_left.y;
	tmp_window = window->top_left.y < window->top_right.y ? \
					&window->top_right.y : &window->top_left.y;
	view.top_limit = min(min(*tmp_window, *tmp_display), \
							old_view.top_limit);
	tmp_display = display->bottom_left.y > display->bottom_right.y ? \
					&display->bottom_right.y : &display->bottom_left.y;
	tmp_window = window->bottom_left.y > window->bottom_right.y ? \
					&window->bottom_right.y : &window->bottom_left.y;
	view.bot_limit = max(max(*tmp_window, *tmp_display), old_view.bot_limit);
	return (view);
}

t_display_wall	set_window_height(t_display_wall window, \
			t_player *player, t_sector_node *sector, SDL_Surface *surf)
{
	double	distance_ratio;
	double	top;
	double	bot;

	distance_ratio = window.fov_ratio / window.intersect.a.y * surf->w;
	top = (sector->ceiling_height \
			- (player->posz + player->height)) * distance_ratio;
	bot = (sector->floor_height \
			- (player->posz + player->height)) * distance_ratio;
	window.top_left.y = (surf->h + top) / 2 - player->view_z;
	window.bottom_left.y = (surf->h + bot) / 2 - player->view_z;
	distance_ratio = window.fov_ratio / window.intersect.b.y * surf->w;
	top = (sector->ceiling_height \
			- (player->posz + player->height)) * distance_ratio;
	bot = (sector->floor_height \
			- (player->posz + player->height)) * distance_ratio;
	window.top_right.y = (surf->h + top) / 2 - player->view_z;
	window.bottom_right.y = (surf->h + bot) / 2 - player->view_z;
	window.texture_ratio *= 10;
	return (window);
}

void			draw_portal(t_display_wall *wall, \
					t_display_wall *window, SDL_Surface *surf)
{
	t_vec	tmp_values;

	tmp_values.x = window->bottom_left.y;
	tmp_values.y = window->bottom_right.y;
	window->bottom_left.y = window->top_left.y;
	window->bottom_right.y = window->top_right.y;
	window->top_left.y = wall->top_left.y;
	window->top_right.y = wall->top_right.y;
	if (ft_strncmp(surf->userdata, "textured", 8) != 0)
	{
		draw_line(window->top_left, window->top_right, surf, 0xff8800);
		draw_line(window->top_right, window->bottom_right, surf, 0xffff00);
		draw_line(window->bottom_right, window->bottom_left, surf, 0x88ff00);
		draw_line(window->bottom_left, window->top_left, surf, 0xffff00);
	}
	else
		draw_texture(surf, window->texture, window, 1);
	window->top_left.y = tmp_values.x;
	window->top_right.y = tmp_values.y;
	window->bottom_left.y = wall->bottom_left.y;
	window->bottom_right.y = wall->bottom_right.y;
	if (ft_strncmp(surf->userdata, "textured", 8) != 0)
	{
		draw_line(window->top_left, window->top_right, surf, 0xff8800);
		draw_line(window->top_right, window->bottom_right, surf, 0xffff00);
		draw_line(window->bottom_right, window->bottom_left, surf, 0x88ff00);
		draw_line(window->bottom_left, window->top_left, surf, 0xffff00);
	}
	else
		draw_texture(surf, window->texture, window, 2);
}

void			draw_view_recursive(SDL_Surface *surf, \
				SDL_Surface **wall_textures, t_view view, \
						t_sector_node *sector, t_player *player)
{
	t_display_wall	display_wall;
	t_wall_node		*current_wall;
	t_view			new_view;
	t_display_wall	window;

	current_wall = sector->wall_head;
	while (current_wall != NULL)
	{
		display_wall.relative = rotate_wall_relative(current_wall, player);
		if (intersect_view(&display_wall.relative, \
					&display_wall.intersect, view.fov))
		{
			create_perspective_wall(&display_wall, surf, player, sector);
			init_display_wall(&display_wall, current_wall, view, wall_textures);
			display_wall.texture_ratio = display_wall.length \
							/ (sector->ceiling_height - sector->floor_height);
			if (current_wall->neighbor_sector != NULL \
						&& current_wall->neighbor_sector != sector)
			{
				window = set_window_height(display_wall, player, \
										current_wall->neighbor_sector, surf);
				new_view = create_view(&display_wall, &window, view);
				draw_view_recursive(surf, wall_textures, new_view, \
										current_wall->neighbor_sector, player);
				draw_portal(&display_wall, &window, surf);
			}
			else
				draw_3dwall(&display_wall, surf);
		}
		current_wall = current_wall->next;
	}
}
