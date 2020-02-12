/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:22:12 by afonck            #+#    #+#             */
/*   Updated: 2020/02/12 11:22:29 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

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

void	toggle_fly(SDL_Event *event, t_player *player)
{
	if (event->key.keysym.sym == SDLK_l)
		player->fly = !player->fly;
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
		toggle_fly(&doom->sdlmain.event, &doom->game.player);
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
