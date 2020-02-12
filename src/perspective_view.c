/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/12 02:17:04 by afonck           ###   ########.fr       */
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

void			base_values_dspwall(t_display_wall *display, double wall_len, \
				SDL_Surface *tex, t_view *old_view)
{
	display->dist_left = display->intersect.a.y;
	display->dist_right = display->intersect.b.y;
	display->length = wall_len;
	display->texture = tex;
	display->top_limit = old_view->top_limit;
	display->bot_limit = old_view->bot_limit;
}

void			init_display_wall(t_display_wall *display, \
		t_wall_node *current_wall, t_view old_view, SDL_Surface **wall_textures)
{
	double	len;

	base_values_dspwall(display, current_wall->length, \
	wall_textures[current_wall->tex_index], &old_view);
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

void			draw_portal_untextured(t_display_wall *win, \
				SDL_Surface *surf)
{
	draw_line(win->top_left, win->top_right, surf, 0xff8800);
	draw_line(win->top_right, win->bottom_right, surf, 0xffff00);
	draw_line(win->bottom_right, win->bottom_left, surf, 0x88ff00);
	draw_line(win->bottom_left, win->top_left, surf, 0xffff00);
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
		draw_portal_untextured(window, surf);
	else
		draw_texture(surf, window->texture, window, 1);
	window->top_left.y = tmp_values.x;
	window->top_right.y = tmp_values.y;
	window->bottom_left.y = wall->bottom_left.y;
	window->bottom_right.y = wall->bottom_right.y;
	if (ft_strncmp(surf->userdata, "textured", 8) != 0)
		draw_portal_untextured(window, surf);
	else
		draw_texture(surf, window->texture, window, 2);
}

void			init_wall_rec(t_view_rec *viewrec, t_game *game, \
				t_sector_node *sector, SDL_Surface **wall_textures)
{
	create_perspective_wall(&viewrec->dspwall, \
		game->surfs.perspective_view, &game->player, sector);
	init_display_wall(&viewrec->dspwall, viewrec->current_wall, \
		viewrec->view, wall_textures);
	viewrec->dspwall.texture_ratio = viewrec->dspwall.length \
		/ (sector->ceiling_height - sector->floor_height);
}

void			draw_next_sec(t_view_rec *viewrec, t_game *game, \
				SDL_Surface **wall_textures)
{
	viewrec->window = set_window_height(viewrec->dspwall, &game->player, \
	viewrec->current_wall->neighbor_sector, game->surfs.perspective_view);
	viewrec->new_view = create_view(&viewrec->dspwall, \
		&viewrec->window, viewrec->view);

	draw_view_recursive(game, wall_textures, viewrec->new_view, \
							viewrec->current_wall->neighbor_sector);
	draw_portal(&viewrec->dspwall, &viewrec->window, \
		game->surfs.perspective_view);
}

void			draw_view_recursive(t_game *game, \
				SDL_Surface **wall_textures, t_view view, \
						t_sector_node *sector)
{
	t_view_rec		viewrec;

	viewrec.view = view;
	viewrec.current_wall = sector->wall_head;
	while (viewrec.current_wall != NULL)
	{
		viewrec.dspwall.relative = rotate_wall_relative(viewrec.current_wall, \
			&game->player);
		if (intersect_view(&viewrec.dspwall.relative, \
			&viewrec.dspwall.intersect, view.fov))
		{
			init_wall_rec(&viewrec, game, sector, wall_textures);
			if (viewrec.current_wall->neighbor_sector != NULL \
						&& viewrec.current_wall->neighbor_sector != sector)
				draw_next_sec(&viewrec, game, wall_textures);
			else
				draw_3dwall(&viewrec.dspwall, game->surfs.perspective_view);
		}
		viewrec.current_wall = viewrec.current_wall->next;
	}
}
