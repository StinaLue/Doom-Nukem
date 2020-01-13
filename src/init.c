/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:53:33 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/13 16:57:57 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int		init_sdl_and_ttf()
{
	int error;

	error = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
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
	//if (error == 1)
	//	quit_sdl_and_ttf();
	return (error);
}

int		init_sdlmain(t_sdlmain *sdlmain)
{
	if ((sdlmain->win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN)) \
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
	return (EXIT_SUCCESS);
}

int		init_map(t_map *map)
{
	t_vecdb vec1 = {20, 60}; 
	t_vecdb vec2 = {40, 80};
	t_vecdb vec3 = {90, 90};
	//t_vecdb vec4 = {80, 60};
	t_vecdb vec5 = {80, 40};
	t_vecdb vec6 = {60, 20};
	t_vecdb vec7 = {40, 20};
	t_vecdb vec8 = {20, 40};

	//map->sector_head = NULL;
	add_sector_node(&map->sector_head);
	create_wall_node(&map->sector_head->wall_head, vec1, vec2, 0xff0000);
	create_wall_node(&map->sector_head->wall_head, vec2, vec3, 0xffbb00);
	create_wall_node(&map->sector_head->wall_head, vec3, vec5, 0x00ff00);
	//create_wall_node(&map->sector_head->wall_head, vec4, vec5, 0x0088ff);
	create_wall_node(&map->sector_head->wall_head, vec5, vec6, 0xff0000);
	create_wall_node(&map->sector_head->wall_head, vec6, vec7, 0xffbb00);
	create_wall_node(&map->sector_head->wall_head, vec7, vec8, 0x00ff00);
	create_wall_node(&map->sector_head->wall_head, vec8, vec1, 0x0088ff);

	return (0);
}

int	init_game(t_game *game, t_sdlmain *sdlmain)
{
	if (init_gamesurfs_struct(&(doom->surfs)) == 1)
		return (1);
	init_data_struct(&(doom->data));
	init_player_struct(&(doom->player));
	return (0);
}