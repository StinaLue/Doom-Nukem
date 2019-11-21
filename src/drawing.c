/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:35:35 by afonck            #+#    #+#             */
/*   Updated: 2019/11/21 17:49:48 by afonck           ###   ########.fr       */
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

void		blit_in_rect(SDL_Surface *surf, SDL_Surface *winsurf, int whichsurf)
{
	SDL_Rect rect;

	if (whichsurf == FIX_MAP_SHOW)
		rect = assign_SDLrect(WIN_WIDTH / 8, 0, WIN_WIDTH / 8, WIN_HEIGHT / 4);
	else if (whichsurf == ROT_MAP_SHOW)
		rect = assign_SDLrect(0, 0, WIN_WIDTH / 8, WIN_HEIGHT / 4);
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
		((Uint32 *)surf->pixels)[x + y * surf->w] = color;
}
