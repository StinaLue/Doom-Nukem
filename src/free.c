/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/04 19:12:32 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	free_sdl(t_sdl *sdl)//SDL_Window **win)
{
	SDL_FreeSurface(sdl->fixed_mmap);
	sdl->fixed_mmap = NULL;
	SDL_FreeSurface(sdl->rot_mmap);
	sdl->rot_mmap = NULL;
	SDL_FreeSurface(sdl->perspective_mmap);
	sdl->perspective_mmap = NULL;
	SDL_DestroyWindow(sdl->win);
	sdl->win = NULL;
	//SDL_DestroyWindow(*win);
	//*win = NULL;
	SDL_Quit();
}

int		free_sdl_quit(t_sdl *sdl)//SDL_Window **win)
{
	SDL_FreeSurface(sdl->fixed_mmap);
	sdl->fixed_mmap = NULL;
	SDL_FreeSurface(sdl->rot_mmap);
	sdl->rot_mmap = NULL;
	SDL_FreeSurface(sdl->perspective_mmap);
	sdl->perspective_mmap = NULL;
	SDL_DestroyWindow(sdl->win);
	sdl->win = NULL;
	//SDL_DestroyWindow(*win);
	//*win = NULL;
	SDL_Quit();
	//free_sdl(win);
	return (EXIT_FAILURE);
}
