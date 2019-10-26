/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/26 12:22:55 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	free_sdl(SDL_Window **win)
{
	SDL_DestroyWindow(*win);
	*win = NULL;
	SDL_Quit();
}

void	free_ttf(t_ttf *ttf)
{
	TTF_CloseFont(ttf->font);
	ttf->font = NULL;
	SDL_FreeSurface(ttf->surf_message);
	ttf->surf_message = NULL;
	TTF_Quit();
}

int		free_sdl_quit(SDL_Window **win)
{
	free_sdl(win);
	return (EXIT_FAILURE);
}

int		free_sdl_ttf_quit(SDL_Window **win, t_ttf *ttf)
{
	free_sdl(win);
	free_ttf(ttf);
	return (EXIT_FAILURE);
}
