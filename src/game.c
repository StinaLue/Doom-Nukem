/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:46:18 by afonck            #+#    #+#             */
/*   Updated: 2020/02/12 10:47:16 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

void			set_listener_ori(double angle, t_vecdb player_pos)
{
	ALfloat	orix;
	ALfloat oriy;
	t_vecdb test;
	ALfloat listener_ori[6];

	orix = sin(angle) * -5 + player_pos.x;
	oriy = cos(angle) * 5 + player_pos.y;
	test.x = orix;
	test.y = oriy;
	listener_ori[0] = orix;
	listener_ori[1] = oriy;
	listener_ori[2] = cross_product(test, player_pos);
	listener_ori[3] = 0;
	listener_ori[4] = 1;
	listener_ori[5] = 0;
	alListener3f(AL_POSITION, player_pos.x, player_pos.y, 0);
	alListenerfv(AL_ORIENTATION, listener_ori);
}

void			setmouse_rel(t_sdlmain *sdlmain, int bool)
{
	if (bool == 1)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else if (bool == 0)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_WarpMouseInWindow(sdlmain->win, sdlmain->win_surf->w / 2, \
			sdlmain->win_surf->h / 2);
}

int				blit_game(t_game *game, t_sdlmain *sdlmain, \
				t_doom *doom, t_view *view)
{
	game->surfs.perspective_view->userdata = (game->data.hud_flags & TEXFLAG) ?\
		"untextured" : "textured";
	*view = init_view(&game->player, game->surfs.perspective_view);
	draw_view_recursive(game, doom->wall_textures, \
						*view, game->player.sector);
	if (blit_enemies(game, game->surfs.perspective_view, &doom->map) != 0)
		return (error_return("Blit enemies error\n", NULL));
	if (blit_weapon(game, game->surfs.perspective_view, \
				game->player.current_weapon, doom->map.weapon_choice) != 0)
		return (error_return("Blit weapon error\n", NULL));
	if (game_blit_hud(&doom->map, game, &game->data.itt, \
		&game->data.startclock) != 0)
		return (1);
	if ((SDL_BlitScaled(game->surfs.perspective_view, \
						NULL, sdlmain->win_surf, NULL)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", \
				SDL_GetError()));
		if ((draw_map(sdlmain, game, &doom->map, \
					&game->data.hud_flags)) == 1)
		return (error_return("error during map drawing\n", NULL));
	if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", \
					SDL_GetError()));
		game->data.itt++;
	return (0);
}

void			check_endgame(t_game *game, t_doom *doom)
{
	play_sound(game, &doom->sdlmain, &doom->map);
	if (game->player.health <= 0)
		game_over_loop(doom);
	else if (game->player.sector->is_goal == 1)
		win_loop(doom);
}

int				game_loop(t_doom *doom)
{
	t_game		*game;
	t_sdlmain	*sdlmain;
	t_view		view;

	game = &(doom->game);
	sdlmain = &(doom->sdlmain);
	game->data.itt = 0;
	setmouse_rel(sdlmain, 1);
	game->data.startclock = SDL_GetTicks();
	if (!is_buffer_playing(sdlmain->sound.source[0], sdlmain->sound.buffer[0]))
		play_game_music(game, sdlmain, doom);
	while (doom->state == GAME_STATE)
	{
		clean_surf(game->surfs.perspective_view);
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
			if (handle_events(doom) != 0)
				break ;
		check_endgame(game, doom);
		handle_keys(doom, SDL_GetKeyboardState(NULL));
		player_attack(game->enemy, &game->player, &doom->map, &game->surfs);
		enemy_action(game->enemy, &game->player, doom->map.num_enemies);
		blit_game(game, sdlmain, doom, &view);
	}
	setmouse_rel(sdlmain, 0);
	return (0);
}
