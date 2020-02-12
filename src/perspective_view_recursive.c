/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view_recursive.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:54:48 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/12 11:10:32 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

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

void			draw_3dwall(t_display_wall *dsp_wall, SDL_Surface *surf)
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
