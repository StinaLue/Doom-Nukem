/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:53:33 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/07 16:40:12 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int		init_sdl_and_ttf()
{
	int error;

	error = 0;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		ft_dprintf(STDERR_FILENO, "SDL_Init Error: %{r}s\n", SDL_GetError());
		error = 1;
	}
	if (TTF_Init() != 0)
	{
		ft_dprintf(STDERR_FILENO, "TTF_Init Error: %{r}s\n", TTF_GetError());
		error = 1;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		ft_dprintf(STDERR_FILENO, "Mix_OpenAudio Error: %{r}s\n", Mix_GetError());
		error = 1;
	}
	return (error);
}

int		init_sdlmain(t_sdlmain *sdlmain)
{
	if ((sdlmain->win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, sdlmain->win_w, sdlmain->win_h, SDL_WINDOW_SHOWN)) \
		== NULL)
	{
		ft_dprintf(STDERR_FILENO, "SDL_CreateWindow Error: %{r}s\n", \
			SDL_GetError());
		return (EXIT_FAILURE);
	}
	if ((sdlmain->win_surf = SDL_GetWindowSurface(sdlmain->win)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "SDL_GetWindowSurface Error: %{r}s\n", \
			SDL_GetError());
		return (EXIT_FAILURE);
	}
	//if ((sdlmain->music = Mix_LoadMUS("assets/sounds/Story Music.mid")) == NULL)
	if ((sdlmain->music = Mix_LoadMUS("assets/sounds/beet.wav")) == NULL)
		return (error_return("Mix_LoadMUS error: %{r}s\n", Mix_GetError()));
	Mix_PlayMusic(sdlmain->music, -1);
	return (EXIT_SUCCESS);
}

int		init_map(t_map *map)
{
	t_vecdb vec1 = {60, 20}; 
	t_vecdb vec2 = {60, 40};
	t_vecdb vec3 = {70, 90};
	t_vecdb vec4 = {90, 20};

	add_sector_node(&map->sector_head);

	create_wall_node(&map->sector_head->wall_head, vec1, vec2, 0xff0000);
	create_wall_node(&map->sector_head->wall_head, vec2, vec3, 0xffbb00);
	create_wall_node(&map->sector_head->wall_head, vec3, vec4, 0x00ff00);
	create_wall_node(&map->sector_head->wall_head, vec4, vec1, 0x0088ff);

	return (0);
}

int	init_game(t_game *game, t_sdlmain *sdlmain)
{
	if (init_gamesurfs_struct(&(game->surfs), sdlmain) == 1)
		return (1);
	init_data_struct(&(game->data));
	init_player_struct(&(game->player));
	return (0);
}
