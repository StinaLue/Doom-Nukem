/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:22:12 by afonck            #+#    #+#             */
/*   Updated: 2019/12/12 18:24:54 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_quit(SDL_Event *event, int *state)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && \
		event->key.keysym.sym == SDLK_ESCAPE))
		*state = QUIT_STATE;
}

void	check_menu(SDL_Event *event, int *state, int *previous_state)
{
		if (event->key.keysym.sym == SDLK_TAB)
		{
			*previous_state = GAME_STATE;
			*state = MENU_STATE;
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
		if (event->key.keysym.sym == SDLK_c)
		{
			if ((*hud_flags & COLORFLAG) == 0)
				*hud_flags |= COLORFLAG;
			else if ((*hud_flags & COLORFLAG))
				*hud_flags &= ~(COLORFLAG);
		}
}

int    handle_events(t_doom *doom)
{
    check_quit(&doom->sdlmain.event, &doom->state);
	if (doom->sdlmain.event.type == SDL_KEYDOWN && doom->sdlmain.event.key.repeat == 0)
	{
		check_menu(&doom->sdlmain.event, &doom->state, &doom->menu.previous_state);
		handle_hud(&doom->sdlmain.event, &doom->game.data.hud_flags);
	}
	if (doom->state != GAME_STATE)
		return (1);
	return (0);
}
