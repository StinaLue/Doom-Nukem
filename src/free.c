/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/14 13:27:15 by afonck           ###   ########.fr       */
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

int		free_sdl_quit(SDL_Window **win)
{
	free_sdl(win);
	return (EXIT_FAILURE);
}
