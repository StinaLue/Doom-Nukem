/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:35:35 by afonck            #+#    #+#             */
/*   Updated: 2020/01/16 14:02:01 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Rect	assign_SDLrect(int x, int y, int w, int h)
{
	SDL_Rect newrect;

	newrect.x = x;
	newrect.y = y;
	newrect.w = w;
	newrect.h = h;
	return (newrect);
}

void	draw_border_options(SDL_Rect *rect, int color, SDL_Surface *surf)
{
	t_vec top_left;
	t_vec top_right;
	t_vec bottom_left;
	t_vec bottom_right;
	int i;

	i = 0;
	while (i < 3)
	{
		give_vec_values(&top_left, rect->x - 1 - i, surf->h - rect->y + i);
		give_vec_values(&top_right, rect->x + rect->w + i, surf->h - rect->y + i);
		give_vec_values(&bottom_left, rect->x - 1 - i, surf->h - rect->y - rect->h - 1 - i);
		give_vec_values(&bottom_right, rect->x + i + rect->w, surf->h - rect->y - rect->h - 1 - i);
		draw_line(bottom_left, bottom_right, surf, color);
		draw_line(bottom_right, top_right, surf, color);
		draw_line(top_right, top_left, surf, color);
		draw_line(top_left, bottom_left, surf, color);
		i++;
	}
}

void	draw_border(SDL_Surface *surf, int color)
{
	t_vec top_left;
	t_vec top_right;
	t_vec bottom_left;
	t_vec bottom_right;

	give_vec_values(&top_left, 0, surf->h - 1);
	give_vec_values(&top_right, surf->w - 1, surf->h - 1);
	give_vec_values(&bottom_left, 0, 0);
	give_vec_values(&bottom_right, surf->w - 1, 0);
	draw_line(bottom_left, top_left, surf, color);
	draw_line(top_left, top_right, surf, color);
	draw_line(top_right, bottom_right, surf, color);
	draw_line(bottom_right, bottom_left, surf, color);
}

int		draw_map(t_sdlmain *sdlmain, t_game *game, const t_map *map, char *hud_flags)
{
	int ret;

	ret = 0;
	game->surfs.fixed_mmap->userdata = "1map";
	if ((*hud_flags & ROT_MAP_SHOW) && (*hud_flags & FIX_MAP_SHOW) == 0)
		ret = draw_full_rotmap(game->surfs.rot_mmap, &game->player, map, sdlmain->win_surf);
	else if ((*hud_flags & FIX_MAP_SHOW) && (*hud_flags & ROT_MAP_SHOW) == 0)
		ret = draw_full_fixedmap(game->surfs.fixed_mmap, &game->player, map, sdlmain->win_surf);
	else if ((*hud_flags & ROT_MAP_SHOW) && (*hud_flags & FIX_MAP_SHOW))
	{
		game->surfs.fixed_mmap->userdata = "2maps";
		ret = draw_full_rotmap(game->surfs.rot_mmap, &game->player, map, sdlmain->win_surf);
		if (ret == 1)
			return (1);
		ret = draw_full_fixedmap(game->surfs.fixed_mmap, &game->player, map, sdlmain->win_surf);
	}
	return (ret);
}

int			blit_in_rect(SDL_Surface *surf, SDL_Surface *winsurf, int whichsurf)
{
	SDL_Rect rect;

	if (whichsurf == FIX_MAP_SHOW + ROT_MAP_SHOW)
		//rect = create_sdlrect(WIN_W / 8, 0, 0, 0);
		rect = create_sdlrect(winsurf->w / 6, 0, winsurf->w / 6, winsurf->h / 3);
		//rect = create_sdlrect(MINIMAP_WIDTH * 2, 0, MINIMAP_WIDTH * 2, MINIMAP_HEIGHT * 2);
	else if (whichsurf == ROT_MAP_SHOW || whichsurf == FIX_MAP_SHOW)
		//rect = create_sdlrect(0, 0, 0, 0);
		rect = create_sdlrect(0, 0, winsurf->w / 6, winsurf->h / 3);
		//rect = create_sdlrect(0, 0, MINIMAP_WIDTH * 2, MINIMAP_HEIGHT * 2);
	else
		//rect = create_sdlrect(0, 0, 0, 0);
		rect = create_sdlrect(0, 0, winsurf->w, winsurf->h);
	if ((SDL_BlitScaled(surf, NULL, winsurf, &rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	return (0);
}

void		fill_pix(SDL_Surface *surf, int x, int y, int color)
{
	if (x < surf->w && y < surf->h && x >= 0 && y >= 0)
		((Uint32 *)surf->pixels)[x + (surf->h - y - 1) * surf->w] = color;
}
