/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/14 16:44:33 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include "wolf3d.h"

void	free_SDL(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex)
{
	SDL_DestroyTexture(*tex);
	*tex = NULL;
	SDL_DestroyRenderer(*ren);
	*ren = NULL;
	SDL_DestroyWindow(*win);
	*win = NULL;
	SDL_Quit();
}

void	free_TTF(t_ttf *ttf)
{
	TTF_CloseFont(ttf->font);
	ttf->font = NULL;
	SDL_FreeSurface(ttf->surf_message);
	ttf->surf_message = NULL;
	SDL_DestroyTexture(ttf->message);
	ttf->message = NULL;
	ft_memdel((void **)&ttf->fps);
	TTF_Quit();
}