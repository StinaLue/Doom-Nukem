/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL_sub_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:02:39 by afonck            #+#    #+#             */
/*   Updated: 2020/02/10 17:56:41 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	free_and_null_surf(SDL_Surface *surf)
{
	SDL_FreeSurface(surf);
	surf = NULL;
}

void	assign_sdlcolor(SDL_Color *color, Uint8 red, Uint8 green, Uint8 blue)
{
	color->r = red;
	color->g = green;
	color->b = blue;
}

SDL_Rect	create_sdlrect(int x, int y, int w, int h)
{
	SDL_Rect newrect;

	newrect.x = x;
	newrect.y = y;
	newrect.w = w;
	newrect.h = h;
	return (newrect);
}

void	assign_sdlrect_invert(SDL_Rect *rect, t_vec origin, t_vec size)
{
	rect->x = origin.x;
	rect->y = origin.y - size.y;
	rect->w = size.x;
	rect->h = size.y;
}

void	assign_sdlrect(SDL_Rect *rect, t_vec origin, t_vec size)
{
	rect->x = origin.x;
	rect->y = origin.y;
	rect->w = size.x;
	rect->h = size.y;
}
