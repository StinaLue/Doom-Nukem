/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/12 11:10:05 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int				min(int a, int b)
{
	return (a < b ? a : b);
}

void			create_perspective_wall(t_display_wall *dsp_wall, \
				SDL_Surface *surf, t_player *player, t_sector_node *sector)
{
	double		d;
	double		x;
	double		top;
	double		bot;

	dsp_wall->fov_ratio = player->view.b.y / player->view.b.x;
	d = dsp_wall->fov_ratio / dsp_wall->intersect.a.y * surf->w;
	x = dsp_wall->intersect.a.x * d;
	top = (sector->ceiling_height - (player->posz + player->height)) * d;
	bot = (sector->floor_height - (player->posz + player->height)) * d;
	dsp_wall->top_left.x = (surf->w + x) / 2;
	dsp_wall->top_left.y = (surf->h + top) / 2 - player->view_z;
	dsp_wall->bottom_left.x = dsp_wall->top_left.x;
	dsp_wall->bottom_left.y = (surf->h + bot) / 2 - player->view_z;
	d = dsp_wall->fov_ratio / dsp_wall->intersect.b.y * surf->w;
	x = dsp_wall->intersect.b.x * d;
	top = (sector->ceiling_height - (player->posz + player->height)) * d;
	bot = (sector->floor_height - (player->posz + player->height)) * d;
	dsp_wall->top_right.x = (surf->w + x) / 2;
	dsp_wall->top_right.y = (surf->h + top) / 2 - player->view_z;
	dsp_wall->bottom_right.x = dsp_wall->top_right.x;
	dsp_wall->bottom_right.y = (surf->h + bot) / 2 - player->view_z;
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
