/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:58:18 by afonck            #+#    #+#             */
/*   Updated: 2019/12/08 18:00:59 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int	highlight_text(TTF_Font **font, SDL_Surface **surf, SDL_Color *color, char *text)
{
	//ft_bzero((*surf)->pixels, (*surf)->h * (*surf)->pitch);
	SDL_FreeSurface(*surf);
	TTF_SetFontStyle(*font, TTF_STYLE_BOLD);
	assign_sdlcolor(color, 255, 255, 255);
	if ((*surf = TTF_RenderText_Solid(*font, text, *color)) == NULL)
		return (1);
	return (0);
}

int	reset_text(TTF_Font **font, SDL_Surface **surf, SDL_Color *color, char *text)
{
	//ft_bzero((*surf)->pixels, (*surf)->h * (*surf)->pitch);
	SDL_FreeSurface(*surf);
	TTF_SetFontStyle(*font, TTF_STYLE_NORMAL);
	assign_sdlcolor(color, 255, 0, 0);
	if ((*surf = TTF_RenderText_Solid(*font, text, *color)) == NULL)
		return (1);
	return (0);
}