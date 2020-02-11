/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:22:12 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 22:26:24 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	check_quit(SDL_Event *event, int *state)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && \
		event->key.keysym.sym == SDLK_ESCAPE))
		*state = QUIT_STATE;
}

void	check_menu(SDL_Event *event, int *state, \
					int *prev_state_ptr, int prev_state)
{
	if (event->key.keysym.sym == SDLK_TAB)
	{
		*prev_state_ptr = prev_state;
		*state = MENU_STATE;
	}
}

void	check_anim(t_game *game)
{
	if (game->surfs.current_frame == 0)
	{
		if (game->player.anim == 1)
			game->player.anim = 0;
		else
			game->player.anim = 1;
	}
}

void	activate_map_flags(char *hud_flags)
{
	if ((*hud_flags & ROT_MAP_SHOW) == 0 && (*hud_flags & FIX_MAP_SHOW) == 0)
		*hud_flags |= ROT_MAP_SHOW;
	else if ((*hud_flags & ROT_MAP_SHOW) && (*hud_flags & FIX_MAP_SHOW) == 0)
	{
		*hud_flags &= ~(ROT_MAP_SHOW);
		*hud_flags |= FIX_MAP_SHOW;
	}
	else if ((*hud_flags & FIX_MAP_SHOW) && (*hud_flags & ROT_MAP_SHOW) == 0)
		*hud_flags |= ROT_MAP_SHOW;
	else if ((*hud_flags & ROT_MAP_SHOW) && (*hud_flags & FIX_MAP_SHOW))
	{
		*hud_flags &= ~(ROT_MAP_SHOW);
		*hud_flags &= ~(FIX_MAP_SHOW);
	}
}

void	handle_hud(SDL_Event *event, char *hud_flags)
{
	if (event->key.keysym.sym == SDLK_m)
		activate_map_flags(hud_flags);
	if (event->key.keysym.sym == SDLK_x)
	{
		if ((*hud_flags & TEXFLAG) == 0)
			*hud_flags |= TEXFLAG;
		else if ((*hud_flags & TEXFLAG))
			*hud_flags &= ~(TEXFLAG);
	}
	if (event->key.keysym.sym == SDLK_p)
	{
		if ((*hud_flags & HEALTH_STATUS) == 0)
			*hud_flags |= HEALTH_STATUS;
		else if ((*hud_flags & HEALTH_STATUS))
			*hud_flags &= ~(HEALTH_STATUS);
	}
	if (event->key.keysym.sym == SDLK_t)
	{
		if ((*hud_flags & FPS_SHOW) == 0)
			*hud_flags |= FPS_SHOW;
		else if ((*hud_flags & FPS_SHOW))
			*hud_flags &= ~(FPS_SHOW);
	}
}

void	check_weapon(SDL_Event *event, t_game *game, int available_weapons)
{
	if (available_weapons == 0)
		return ;
	if (event->key.keysym.sym == SDLK_1 && game->player.current_weapon != 0 \
	&& game->player.anim == 0 && available_weapons == 3)
	{
		game->player.current_weapon = 0;
		game->surfs.anim_timer = 0;
		game->surfs.current_frame = 0;
		game->player.anim = 0;
	}
	else if (event->key.keysym.sym == SDLK_2 \
			&& game->player.current_weapon != 1 \
	&& game->player.anim == 0 && available_weapons == 3)
	{
		game->player.current_weapon = 1;
		game->surfs.anim_timer = 0;
		game->surfs.current_frame = 0;
		game->player.anim = 0;
	}
}

int		handle_events(t_doom *doom)
{
	check_quit(&doom->sdlmain.event, &doom->state);
	if (doom->sdlmain.event.type == SDL_KEYDOWN \
			&& doom->sdlmain.event.key.repeat == 0)
	{
		check_menu(&doom->sdlmain.event, &doom->state, \
						&doom->menu.previous_state, GAME_STATE);
		if (doom->sdlmain.event.key.keysym.sym == SDLK_f)
			check_anim(&doom->game);
		check_weapon(&doom->sdlmain.event, \
						&doom->game, doom->map.weapon_choice);
		handle_hud(&doom->sdlmain.event, &doom->game.data.hud_flags);
	}
	if (doom->sdlmain.event.type == SDL_MOUSEMOTION)
	{
		mouse_movement(doom->sdlmain.event.motion, doom);
	}
	if (doom->sdlmain.event.type == SDL_MOUSEBUTTONDOWN \
		&& doom->sdlmain.event.button.button == SDL_BUTTON_LEFT)
		check_anim(&doom->game);
	if (doom->state != GAME_STATE)
		return (1);
	return (0);
}
