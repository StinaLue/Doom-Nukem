/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:53:33 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/06 16:50:07 by sluetzen         ###   ########.fr       */
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
		SDL_Quit();
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
	if ((sdlmain->music = Mix_LoadMUS("assets/sounds/Story Music.mid")) == NULL)
		return (error_return("Mix_LoadMUS error: %{r}s\n", Mix_GetError()));
	Mix_PlayMusic(sdlmain->music, -1);
	return (EXIT_SUCCESS);
}

int		init_map(t_map *map)
{
	t_vecdb vec1 = {50, 20}; // start of "first" wall
	t_vecdb vec2 = {50, 30}; // end of "first" wall
	t_vecdb vec3 = {70, 100};
	t_vecdb vec4 = {90, 20};
	map->sector[0].num_walls = 4;
	if ((map->sector[0].walls = (t_wall *)malloc(sizeof(t_wall) * map->sector[0].num_walls)) == NULL)
		return (1);
	map->sector[0].walls[0].start_wall = vec1;
	map->sector[0].walls[0].end_wall = vec2;
	map->sector[0].walls[0].color = 0xFF0000;
	map->sector[0].walls[1].start_wall = vec2;
	map->sector[0].walls[1].end_wall = vec3;
	map->sector[0].walls[1].color = 0xFF8800;
	map->sector[0].walls[2].start_wall = vec3;
	map->sector[0].walls[2].end_wall = vec4;
	map->sector[0].walls[2].color = 0x00ff00;
	map->sector[0].walls[3].start_wall = vec4;
	map->sector[0].walls[3].end_wall = vec1;
	map->sector[0].walls[3].color = 0x0088ff;


	map->num_sectors = 0; //NOT USED FOR NOW
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
