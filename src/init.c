/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:53:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/06 11:59:43 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int		init_sdl(SDL_Window **win, SDL_Surface **surf)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_dprintf(STDERR_FILENO, "SDL_Init Error: %{r}s\n", SDL_GetError());
		return (EXIT_FAILURE);
	}
	if ((*win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN)) \
		== NULL)
	{
		ft_dprintf(STDERR_FILENO, "SDL_CreateWindow Error: %{r}s\n", \
			SDL_GetError());
		return (EXIT_FAILURE);
	}
	if ((*surf = SDL_GetWindowSurface(*win)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "SDL_GetWindowSurface Error: %{r}s\n", \
			SDL_GetError());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	init_doom(t_doom *doom)
{
	init_sdl_struct(&(doom->sdl));
	init_data_struct(&(doom->data));
	init_player_struct(&(doom->player));
}