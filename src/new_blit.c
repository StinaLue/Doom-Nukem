/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_blit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:47:58 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 19:49:32 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	simple_blit(SDL_Surface *src, SDL_Surface *dst, \
				SDL_Rect *dst_rect, Uint32 colorkey)
{
	t_vec	screen_start;
	t_vec	surf_start;
	Uint32	color;

	if (dst_rect == NULL)
		give_vec_values(&screen_start, 0, 0);
	else
		give_vec_values(&screen_start, dst_rect->x, dst_rect->y);
	give_vec_values(&surf_start, 0, 0);
	while (surf_start.x < src->w && screen_start.x < dst->w)
	{
		surf_start.y = 0;
		if (dst_rect == NULL)
			screen_start.y = 0;
		else
			screen_start.y = dst_rect->y;
		while (surf_start.y < src->h && screen_start.y < dst->h)
		{
			color = ((Uint32 *)src->pixels)[surf_start.x \
										+ surf_start.y * src->w];
			if (color != colorkey)
				((Uint32 *)dst->pixels)[screen_start.x \
										+ screen_start.y * dst->w] = color;
			surf_start.y++;
			screen_start.y++;
		}
		surf_start.x++;
		screen_start.x++;
	}
}

int		blit(SDL_Surface *src, SDL_Rect *src_rect, \
			SDL_Surface *dst, SDL_Rect *dst_rect)
{
	Uint32 colorkey;

	colorkey = 0;
	if (src == NULL || dst == NULL)
		return (error_return("passed null src or dst surf \
									to blit function\n", NULL));
		if (SDL_GetColorKey(src, &colorkey) != 0)
		;
	if (src_rect == NULL)
		simple_blit(src, dst, dst_rect, colorkey);
	return (0);
}
