/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:53:33 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/07 15:46:36 by sluetzen         ###   ########.fr       */
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
	if ((wall_textures[3] = load_opti_bmp("assets/wall_textures/bloodwall.bmp", winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", SDL_GetError()));
	if ((wall_textures[4] = load_opti_bmp("assets/wall_textures/granitewall.bmp", winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", SDL_GetError()));
	if ((wall_textures[5] = load_opti_bmp("assets/wall_textures/orangecell.bmp", winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", SDL_GetError()));
	if ((wall_textures[6] = load_opti_bmp("assets/wall_textures/rustwall.bmp", winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", SDL_GetError()));
	if ((wall_textures[7] = load_opti_bmp("assets/wall_textures/sandybrick.bmp", winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", SDL_GetError()));
	if ((wall_textures[8] = load_opti_bmp("assets/wall_textures/slimewall.bmp", winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", SDL_GetError()));
	return (0);
}

int		init_doom(t_doom *doom)
{
	if (init_map(&doom->map) == 1 || init_sdl_and_ttf() == 1 \
		|| init_sdlmain(&doom->sdlmain) == 1 \
		|| init_game(&doom->game, &doom->sdlmain, &doom->map) == 1 \
		|| init_menu(&doom->menu, &doom->sdlmain) == 1 \
		|| init_wall_textures(doom->wall_textures, doom->sdlmain.win_surf) == 1)
		return (1);
	//degeulasse PLEASE REMOVE ASAP
	//doom->game.player.sector = doom->map.sector_head->next;


	doom->editor.wall_textures = doom->wall_textures;
	doom->editor.enemy_textures = doom->game.surfs.enemy_texture;
	doom->editor.weapon_texture = doom->game.surfs.weapons;
	get_enemysprite_rect(&doom->editor.enemy_rect[0], 0, doom->editor.enemy_textures[0]);
	get_enemysprite_rect(&doom->editor.enemy_rect[1], 1, doom->editor.enemy_textures[1]);
	doom->editor.opt_menu.weapon_rect[0] = create_sdlrect(0, 0, 232, 200);
	doom->editor.opt_menu.weapon_rect[1] = create_sdlrect(100, 500, 116, 100);
	if (init_editor(&doom->editor, &doom->sdlmain) == 1)
		return (1);
	return (0);
}

int		init_sdl_and_ttf(void)
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
	return (error);
}

int		init_sound(t_sound *sound)
{
	if ((sound->device = alcOpenDevice(NULL)) == NULL)
		return (1);
	if ((sound->context = alcCreateContext(sound->device, NULL)) == NULL)
		return (1);
	alcMakeContextCurrent(sound->context);
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alGenSources(NB_SOUND_SOURCES, sound->source);
	init_source(sound->source[0], 1, 0.3, 1); // background music
	init_source(sound->source[1], 1, 1, 0); // player weapon
	init_source(sound->source[2], 1.5, 1, 1); // player's feet
	alGetError();
	alGenBuffers(NB_SOUND_BUFFERS, sound->buffer);

	//MUSIC
	if ((load_wav("assets/sounds/beet.wav", sound->buffer[0])) != 0)
		return (error_return("error loading %{r}s\n", "beet.wav"));
	//if ((load_wav("assets/sounds/beet_mono.wav", sound->buffer[0])) != 0)
	//	return (error_return("error loading %{r}s\n", "beet.wav"));

	//player sounds
	if ((load_wav("assets/sounds/niceswordsound.wav", sound->buffer[1])) != 0)
		return (error_return("error loading %{r}s\n", "niceswordsound.wav"));
	if ((load_wav("assets/sounds/footsteps-1.wav", sound->buffer[2])) != 0)
		return (error_return("error loading %{r}s\n", "footsteps-1.wav"));
	if ((load_wav("assets/sounds/uzi.wav", sound->buffer[3])) != 0)
		return (error_return("error loading %{r}s\n", "uzi.wav"));
	
	//enemies sounds
	if ((load_wav("assets/sounds/zombie_mono.wav", sound->buffer[4])) != 0)
		return (error_return("error loading %{r}s\n", "zombie.wav"));
	if ((load_wav("assets/sounds/boss.wav", sound->buffer[5])) != 0)
		return (error_return("error loading %{r}s\n", "boss.wav"));
	if ((load_wav("assets/sounds/boss_hit.wav", sound->buffer[6])) != 0)
		return (error_return("error loading %{r}s\n", "boss_hit.wav"));

	//environment sounds
	if ((load_wav("assets/sounds/you_lose.wav", sound->buffer[7])) != 0)
		return (error_return("error loading %{r}s\n", "you_lose.wav"));

	alSourcei(sound->source[0], AL_BUFFER, sound->buffer[0]);
	alSourcei(sound->source[2], AL_BUFFER, sound->buffer[2]);
	alSourcePlay(sound->source[0]);
	return (0);
}

int		init_sdlmain(t_sdlmain *sdlmain)
{
	if ((sdlmain->win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, sdlmain->win_w, sdlmain->win_h, \
		SDL_WINDOW_SHOWN)) == NULL)
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
	if ((init_sound(&sdlmain->sound)) != 0)
		return (error_return("error during openal sound init\n", NULL));
	//if ((sdlmain->music = Mix_LoadMUS("assets/sounds/beet.wav")) == NULL)
	//	return (error_return("Mix_LoadMUS error: %{r}s\n", Mix_GetError()));
	//Mix_PlayMusic(sdlmain->music, -1);
	sdlmain->mouse_pos.x = 0;
	sdlmain->mouse_pos.y = 0;
	return (EXIT_SUCCESS);
}

t_view	init_view(t_player *player, SDL_Surface *surf)
{
	t_view	view;

	view.fov = player->view;
	view.top_limit = surf->h - 1;
	view.bot_limit = 0;
	return (view);
}

int		init_map(t_map *map)
{
	//if (read_map(".doom_1", map))
	//	return (1);
	(void)map;
	return (0);
}
/*
int		init_map(t_map *map) //<-- INIT MAP LEAKS
{
	t_sector_node	*current_sector;
	map->num_enemies = 1;
	map->player_spawn.x = 49;
	map->player_spawn.y = 35;

	if (map->num_enemies >= 1)
	{
		if (((map->enemy_info = (t_enemy_info *)malloc(sizeof(t_enemy_info) * map->num_enemies))) == NULL)
			return (1);
		map->enemy_info[0].enemy_spawn = create_vec(50, 34);
		map->enemy_info[0].which_enemy = 1;
	}
	map->num_sectors = 8;
	t_vecdb vec1 = {30, 30};
	t_vecdb vec2 = {70, 30};
	t_vecdb vec3 = {70, 10};
	t_vecdb vec4 = {30, 10};

	t_vecdb vec5 = {20, 33};
	t_vecdb vec6 = {20, 37};
	t_vecdb vec7 = {30, 40};
	t_vecdb vec8 = {70, 40};
	t_vecdb vec9 = {80, 37};
	t_vecdb vec10 = {80, 33};

	t_vecdb vec11 = {30, 60};
	t_vecdb vec12 = {40, 80}; //triangle gauche
	t_vecdb vec13 = {45, 70}; //rect haut gauche
	t_vecdb vec14 = {40, 50}; //rect bas gauche

	t_vecdb vec15 = {60, 50}; //rect bas droit

	t_vecdb vec16 = {60, 80}; //triangle droit
	t_vecdb vec17 = {55, 70}; //rect haut droit

	t_vecdb vec18 = {70, 60};

	t_vecdb vec19 = {50, 110}; //triangle top
	t_vecdb vec20 = {49, 150};
	t_vecdb vec21 = {100, 60};

	t_vecdb vec22 = {0, 60};

	current_sector = add_sector_node(&map->sector_head); //<---- THIS LEAKS
	create_wall_node(&current_sector->wall_head, vec1, vec2, 0);
	create_wall_node(&current_sector->wall_head, vec2, vec3, 1);
	create_wall_node(&current_sector->wall_head, vec3, vec4, 1);
	create_wall_node(&current_sector->wall_head, vec4, vec1, 1);

	current_sector = add_sector_node(&map->sector_head);
	create_wall_node(&current_sector->wall_head, vec2, vec1, 2);
	create_wall_node(&current_sector->wall_head, vec1, vec5, 2);
	create_wall_node(&current_sector->wall_head, vec5, vec6, 2);
	create_wall_node(&current_sector->wall_head, vec6, vec7, 2);
	create_wall_node(&current_sector->wall_head, vec7, vec8, 2);
	create_wall_node(&current_sector->wall_head, vec8, vec9, 2);
	create_wall_node(&current_sector->wall_head, vec9, vec10, 3);
	create_wall_node(&current_sector->wall_head, vec10, vec2, 3);

	current_sector = add_sector_node(&map->sector_head);
	create_wall_node(&current_sector->wall_head, vec7, vec11, 1);
	create_wall_node(&current_sector->wall_head, vec11, vec12, 3);
	create_wall_node(&current_sector->wall_head, vec12, vec13, 4);
	create_wall_node(&current_sector->wall_head, vec13, vec14, 5);
	create_wall_node(&current_sector->wall_head, vec14, vec7, 3);

	current_sector = add_sector_node(&map->sector_head);
	create_wall_node(&current_sector->wall_head, vec7, vec14, 4);
	create_wall_node(&current_sector->wall_head, vec14, vec15,4);
	create_wall_node(&current_sector->wall_head, vec15, vec8, 4);
	create_wall_node(&current_sector->wall_head, vec8, vec7, 5);

	current_sector = add_sector_node(&map->sector_head);
	create_wall_node(&current_sector->wall_head, vec12, vec16, 3);
	create_wall_node(&current_sector->wall_head, vec16, vec17, 3);
	create_wall_node(&current_sector->wall_head, vec17, vec13, 3);
	create_wall_node(&current_sector->wall_head, vec13, vec12, 3);

	current_sector = add_sector_node(&map->sector_head);
	create_wall_node(&current_sector->wall_head, vec8, vec15, 4);
	create_wall_node(&current_sector->wall_head, vec15, vec17, 4);
	create_wall_node(&current_sector->wall_head, vec17, vec16, 4);
	create_wall_node(&current_sector->wall_head, vec16, vec18, 4);
	create_wall_node(&current_sector->wall_head, vec18, vec8, 4);

	current_sector = add_sector_node(&map->sector_head);
	create_wall_node(&current_sector->wall_head, vec16, vec19, 6);
	create_wall_node(&current_sector->wall_head, vec19, vec20, 6);
	create_wall_node(&current_sector->wall_head, vec20, vec21, 6);
	create_wall_node(&current_sector->wall_head, vec21, vec18, 6);
	create_wall_node(&current_sector->wall_head, vec18, vec16, 6);

	current_sector = add_sector_node(&map->sector_head);
	create_wall_node(&current_sector->wall_head, vec11, vec22, 4);
	create_wall_node(&current_sector->wall_head, vec22, vec20, 4);
	create_wall_node(&current_sector->wall_head, vec20, vec19, 4);
	create_wall_node(&current_sector->wall_head, vec19, vec12, 4);
	create_wall_node(&current_sector->wall_head, vec12, vec11, 4);

	current_sector = map->sector_head;
	current_sector->wall_head->neighbor_sector = current_sector->next;

	current_sector = current_sector->next;
	current_sector->wall_head->neighbor_sector = map->sector_head;
	current_sector->wall_head->next->next->next->next->neighbor_sector = current_sector->next->next;

	current_sector = current_sector->next;
	current_sector->wall_head->next->neighbor_sector = current_sector->next->next->next->next->next;
	current_sector->wall_head->next->next->neighbor_sector = current_sector->next->next;
	current_sector->wall_head->next->next->next->next->neighbor_sector = current_sector->next;

	current_sector = current_sector->next;
	current_sector->wall_head->neighbor_sector = map->sector_head->next->next;
	current_sector->wall_head->next->next->neighbor_sector = current_sector->next->next;
	current_sector->wall_head->next->next->next->neighbor_sector = map->sector_head->next;

	current_sector = current_sector->next;
	current_sector->wall_head->next->neighbor_sector = current_sector->next;
	current_sector->wall_head->next->next->next->neighbor_sector = map->sector_head->next->next;

	current_sector = current_sector->next;
	current_sector->wall_head->neighbor_sector = map->sector_head->next->next->next;
	current_sector->wall_head->next->next->neighbor_sector = map->sector_head->next->next->next->next;
	current_sector->wall_head->next->next->next->neighbor_sector = current_sector->next;

	current_sector = current_sector->next;
	current_sector->wall_head->next->neighbor_sector = current_sector->next;
	current_sector->wall_head->next->next->next->next->neighbor_sector = map->sector_head->next->next->next->next->next;

	current_sector = current_sector->next;
	current_sector->wall_head->next->next->neighbor_sector = map->sector_head->next->next->next->next->next->next;
	current_sector->wall_head->next->next->next->next->neighbor_sector = map->sector_head->next->next;

	itt_sector_wall_heads(map->sector_head, &set_wall_length);
	itt_sectors_true(map->sector_head, &check_convex_sector);

	return (0);
}
*/
int	init_game(t_game *game, t_sdlmain *sdlmain, t_map *map)
{
	//game->data.num_enemies = map->num_enemies;
	//game->data.enemy_info = map->enemy_info;
	init_data_struct(&(game->data));
	if (init_gamesurfs_struct(&(game->surfs), sdlmain) == 1 \
							|| init_enemy_struct(game, map) == 1)
		return (1);
	//init_data_struct(&(game->data, map));
	init_player_struct(&(game->player), map);
	game->weapon_anim[0] = blit_katana;
	game->weapon_anim[1] = blit_uzi;
	return (0);
}
