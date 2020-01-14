/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:53:33 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/14 23:45:04 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

int		init_wall_textures(SDL_Surface **wall_textures, SDL_Surface *winsurf)
{
	if ((wall_textures[0] = load_opti_bmp("assets/wall_textures/chippedbrick.bmp", winsurf, 0)) == NULL)
		return (error_return("load chippedbrick bmp error = %{r}s\n", SDL_GetError()));
	if ((wall_textures[1] = load_opti_bmp("assets/wall_textures/grittybrick.bmp", winsurf, 0)) == NULL)
		return (error_return("load grittybrick bmp error = %{r}s\n", SDL_GetError()));
	if ((wall_textures[2] = load_opti_bmp("assets/wall_textures/mudbrick.bmp", winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", SDL_GetError()));
	return (0);
}

int		init_doom(t_doom *doom)
{
	if (init_map(&doom->map) == 1 || init_sdl_and_ttf() == 1 || init_sdlmain(&doom->sdlmain) == 1 \
			|| init_game(&doom->game, &doom->sdlmain) || init_menu(&doom->menu, &doom->sdlmain) == 1 \
			|| init_editor(&doom->editor, &doom->sdlmain) == 1)
		return (1);
	if (init_wall_textures(doom->wall_textures, doom->sdlmain.win_surf) == 1)
		return (1);
	return (0);
}

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
	if ((sdlmain->font = TTF_OpenFont("assets/fonts/dukes-3d.ttf", 28)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((sdlmain->music = Mix_LoadMUS("assets/sounds/beet.wav")) == NULL)
		return (error_return("Mix_LoadMUS error: %{r}s\n", Mix_GetError()));
	Mix_PlayMusic(sdlmain->music, -1);
	sdlmain->mouse_pos.x = 0;
	sdlmain->mouse_pos.y = 0;
	return (EXIT_SUCCESS);
}

int		init_map(t_map *map)
{
	t_vecdb vec1 = {20, 60}; 
	t_vecdb vec2 = {40, 80};
	t_vecdb vec3 = {100, 100};
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
	itt_sector_wall_heads(map->sector_head, &set_wall_length);

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
