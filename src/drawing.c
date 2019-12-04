/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:35:35 by afonck            #+#    #+#             */
/*   Updated: 2019/12/03 13:33:30 by phaydont         ###   ########.fr       */
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

void		draw_map(t_sdl *sdl, t_player *player, t_wall *walls, char *hud_flags)
{
	sdl->fixed_mmap->userdata = "1map";
	if ((*hud_flags & ROT_MAP_SHOW) && (*hud_flags & FIX_MAP_SHOW) == 0)
		draw_full_rotmap(sdl->rot_mmap, player, walls, sdl->win_surf);
	else if ((*hud_flags & FIX_MAP_SHOW) && (*hud_flags & ROT_MAP_SHOW) == 0)
		draw_full_fixedmap(sdl->fixed_mmap, player, walls, sdl->win_surf);
	if ((*hud_flags & ROT_MAP_SHOW) && (*hud_flags & FIX_MAP_SHOW))
	{
		sdl->fixed_mmap->userdata = "2maps";
		draw_full_rotmap(sdl->rot_mmap, player, walls, sdl->win_surf);
		draw_full_fixedmap(sdl->fixed_mmap, player, walls, sdl->win_surf);
	}
}

void		blit_in_rect(SDL_Surface *surf, SDL_Surface *winsurf, int whichsurf)
{
	SDL_Rect rect;

	if (whichsurf == FIX_MAP_SHOW + ROT_MAP_SHOW)
		rect = assign_SDLrect(MINIMAP_WIDTH * 2, 0, MINIMAP_WIDTH * 2, MINIMAP_HEIGHT * 2);
	else if (whichsurf == ROT_MAP_SHOW || whichsurf == FIX_MAP_SHOW)
		rect = assign_SDLrect(0, 0, MINIMAP_WIDTH * 2, MINIMAP_HEIGHT * 2);
	else
		rect = assign_SDLrect(0, 0, WIN_WIDTH, WIN_HEIGHT);
	if ((SDL_BlitScaled(surf, NULL, winsurf, &rect)) < 0)
	{
		printf("BlitScale error = %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void		fill_pix(SDL_Surface *surf, int x, int y, int color)
{
	if (x < surf->w && y < surf->h && x >= 0 && y >= 0)
		((Uint32 *)surf->pixels)[x + (surf->h - y - 1) * surf->w] = color;
}
