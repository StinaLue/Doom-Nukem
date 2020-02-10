/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:58:18 by afonck            #+#    #+#             */
/*   Updated: 2020/02/10 15:39:40 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int		highlight_text(TTF_Font **font, SDL_Surface **surf, \
					SDL_Color *color, char *text)
{
	SDL_FreeSurface(*surf);
	TTF_SetFontStyle(*font, TTF_STYLE_BOLD);
	assign_sdlcolor(color, 255, 255, 255);
	if ((*surf = TTF_RenderText_Solid(*font, text, *color)) == NULL)
		return (1);
	return (0);
}

int		reset_text(TTF_Font **font, SDL_Surface **surf, \
					SDL_Color *color, char *text)
{
	SDL_FreeSurface(*surf);
	TTF_SetFontStyle(*font, TTF_STYLE_NORMAL);
	assign_sdlcolor(color, 255, 0, 0);
	if ((*surf = TTF_RenderText_Solid(*font, text, *color)) == NULL)
		return (1);
	return (0);
}

void	prepend_str(const char *to_prepend, const char *str, char *new_str, \
		int full_size)
{
	ft_bzero(new_str, full_size);
	ft_strncpy(new_str, to_prepend, ft_strlen(to_prepend));
	ft_strncat(new_str, str, ft_strlen(str));
	new_str[full_size - 1] = '\0';
}
