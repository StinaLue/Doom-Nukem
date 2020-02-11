/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:53:33 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 12:45:22 by sluetzen         ###   ########.fr       */
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
	if (init_sdl_and_ttf() == 1 \
		|| init_sdlmain(&doom->sdlmain) == 1 \
		|| init_game(&doom->game, &doom->sdlmain, &doom->map) == 1 \
		|| init_menu(&doom->menu, &doom->sdlmain) == 1 \
		|| init_wall_textures(doom->wall_textures, doom->sdlmain.win_surf) == 1)
		return (1);
	doom->editor.wall_textures = doom->wall_textures;
	doom->editor.enemy_textures = doom->game.surfs.enemy_texture;
	doom->editor.weapon_texture = doom->game.surfs.weapons;
	doom->editor.player_face_surf = doom->game.surfs.hud_faces_surf;
	//doom->editor.player_face_rec = doom->game.surfs.hud_weapons_rect;
	doom->editor.player_face_rec.x = doom->game.surfs.hud_faces_rect.x;
	doom->editor.player_face_rec.y = doom->game.surfs.hud_faces_rect.y;
	doom->editor.player_face_rec.h = doom->game.surfs.hud_faces_rect.h;
	doom->editor.player_face_rec.w = doom->game.surfs.hud_faces_rect.w;
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
	if ((load_wav("assets/sounds/win.wav", sound->buffer[8])) != 0)
		return (error_return("error loading %{r}s\n", "win.wav"));
	if ((load_wav("assets/sounds/chill_music.wav", sound->buffer[9])) != 0)
		return (error_return("error loading %{r}s\n", "chill_music.wav"));
	if ((load_wav("assets/sounds/doom_theme.wav", sound->buffer[10])) != 0)
		return (error_return("error loading %{r}s\n", "doom_theme.wav"));

	//alSourcei(sound->source[0], AL_BUFFER, sound->buffer[0]);
	alSourcei(sound->source[2], AL_BUFFER, sound->buffer[2]);
	return (0);
}

int		init_sdlmain(t_sdlmain *sdlmain)
{
	if ((init_sound(&sdlmain->sound)) != 0)
		return (error_return("error during openal sound init\n", NULL));
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

int	init_game(t_game *game, t_sdlmain *sdlmain, t_map *map)
{
	init_data_struct(&(game->data));
	if (init_gamesurfs_struct(&(game->surfs), sdlmain) == 1)
		return (1);
	init_player_struct(&(game->player), map);
	game->weapon_anim[0] = blit_katana;
	game->weapon_anim[1] = blit_uzi;
	return (0);
}
