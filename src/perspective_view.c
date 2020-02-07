/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/07 15:35:27 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

double		vxs(double xstart, double ystart, double xtwo, double ytwo)
{
	return (xstart * ytwo - ystart * xtwo);
}

t_vecdb		intersect(t_vecdb start, t_vecdb end, t_vecdb origin, t_vecdb cross)
{
	t_vecdb intersection;
	intersection.x = vxs(vxs(start.x, start.y, end.x, end.y), start.x - end.x, vxs(origin.x, origin.y, cross.x, cross.y), origin.x - cross.x) / vxs(start.x - end.x, start.y - end.y, origin.x - cross.x, origin.y - cross.y);
	intersection.y = vxs(vxs(start.x, start.y, end.x, end.y), start.y - end.y, vxs(origin.x, origin.y, cross.x, cross.y), origin.y - cross.y) / vxs(start.x - end.x, start.y - end.y, origin.x - cross.x, origin.y - cross.y);
	return (intersection);
}

t_vecdb		simple_intersect(t_vecdb start, t_vecdb end, t_vecdb cross)
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

int			intersect_view(t_segment *wall, t_segment *intersect, t_segment view)
{
	if (cross_product(wall->a, wall->b) > 0 || (wall->a.y <= 0 && wall->b.y <= 0))
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

void		create_perspective_wall(t_display_wall *dsp_wall, SDL_Surface *surf, t_player *player, t_sector_node *sector)
{
	double		fov_ratio;
	double		x;
	double		top;
	double		bot;

	fov_ratio = player->view.b.y / player->view.b.x / dsp_wall->intersect.a.y * surf->w;
	x = dsp_wall->intersect.a.x * fov_ratio;
	top = (sector->ceiling_height - (player->posz + player->height)) * fov_ratio;
	bot = (sector->floor_height - (player->posz + player->height)) * fov_ratio;

	dsp_wall->top_left.x = (surf->w + x) / 2;
	dsp_wall->top_left.y = (surf->h + top) / 2 - player->view_z;
	dsp_wall->bottom_left.x = dsp_wall->top_left.x;
	dsp_wall->bottom_left.y = (surf->h + bot) / 2 - player->view_z;

	fov_ratio = player->view.b.y / player->view.b.x / dsp_wall->intersect.b.y * surf->w;
	x = dsp_wall->intersect.b.x * fov_ratio;
	top = (sector->ceiling_height - (player->posz + player->height)) * fov_ratio;
	bot = (sector->floor_height - (player->posz + player->height)) * fov_ratio;

	dsp_wall->top_right.x = (surf->w + x) / 2;
	dsp_wall->top_right.y = (surf->h + top) / 2 - player->view_z;
	dsp_wall->bottom_right.x = dsp_wall->top_right.x;
	dsp_wall->bottom_right.y = (surf->h + bot) / 2 - player->view_z;
}

//remove wall and send texture directly
void	draw_3dwall(t_display_wall *dsp_wall, SDL_Surface *surf)
{
	if (ft_strncmp(surf->userdata, "yescolor", 8) != 0)
	{
		draw_line(dsp_wall->top_left, dsp_wall->top_right, surf, 0xffffff);
		draw_line(dsp_wall->top_right, dsp_wall->bottom_right, surf, 0xffdddd);
		draw_line(dsp_wall->bottom_right, dsp_wall->bottom_left, surf, 0xdddddd);
		draw_line(dsp_wall->bottom_left, dsp_wall->top_left, surf, 0xddddff);
	}
	else
		draw_texture(surf, dsp_wall->texture, dsp_wall);
}

void		init_display_wall(t_display_wall *display, t_wall_node *current_wall, t_view old_view, SDL_Surface **wall_textures)
{
	double	length;

	display->dist_left = display->intersect.a.y;
	display->dist_right = display->intersect.b.y;
	display->length = current_wall->length;
	display->texture = wall_textures[current_wall->tex_index];
	display->top_limit = old_view.top_limit;
	display->bot_limit = old_view.bot_limit;
	if (fabs(display->relative.a.x - display->relative.b.x) > 0.001)
	{
		length = display->relative.b.x - display->relative.a.x;
		display->start_pos = (display->intersect.a.x - display->relative.a.x) / length;
		display->end_pos = (display->intersect.b.x - display->relative.a.x) / length;
	}
	else if (fabs(display->relative.a.y - display->relative.b.y) > 0.001)
	{
		length = display->relative.b.y - display->relative.a.y;
		display->start_pos = (display->intersect.a.y - display->relative.a.y) / length;
		display->end_pos = (display->intersect.b.y - display->relative.a.y) / length;
	}
	else
	{
		display->start_pos = 0;
		display->end_pos = 1;
	}
}

t_view		create_view(t_display_wall *display, t_view old_view)
{
	t_view	view;

	view.fov.a = display->intersect.a;
	view.fov.b = display->intersect.b;
	view.top_limit = old_view.top_limit;
	view.bot_limit = old_view.bot_limit;
	if (display->top_left.y < view.top_limit && display->top_left.y >= display->top_right.y)
		view.top_limit = display->top_left.y;
	else if (display->top_right.y < view.top_limit && display->top_left.y <= display->top_right.y)
		view.top_limit = display->top_right.y;
	if (display->bottom_left.y > view.bot_limit && display->bottom_left.y <= display->bottom_right.y)
		view.bot_limit = display->bottom_left.y;
	else if (display->bottom_right.y > view.bot_limit && display->bottom_left.y >= display->bottom_right.y)
		view.bot_limit = display->bottom_right.y;
	return (view);
}

void		draw_view_recursive(SDL_Surface *surf, SDL_Surface **wall_textures, t_view view, t_sector_node *sector, t_player *player)
{
	t_display_wall	display_wall;
	t_wall_node		*current_wall;
	t_view			new_view;

	current_wall = sector->wall_head;
	while (current_wall != NULL)
	{
		display_wall.relative = rotate_wall_relative(current_wall, player);
		if (intersect_view(&display_wall.relative, &display_wall.intersect, view.fov))
		{
			create_perspective_wall(&display_wall, surf, player, sector);
			init_display_wall(&display_wall, current_wall, view, wall_textures);//set cuts, set distance, set length;
			if (current_wall->neighbor_sector != NULL && current_wall->neighbor_sector != sector)
			{
				new_view = create_view(&display_wall, view);
				draw_view_recursive(surf, wall_textures, new_view, current_wall->neighbor_sector, player);
				//draw portal top and bot
			}
			else
				draw_3dwall(&display_wall, surf);
		}
		current_wall = current_wall->next;
	}
}