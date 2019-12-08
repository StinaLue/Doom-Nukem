/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:22:12 by afonck            #+#    #+#             */
/*   Updated: 2019/12/09 00:09:39 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_quit(SDL_Event *event, int *quit)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && \
		event->key.keysym.sym == SDLK_ESCAPE))
		*quit = 1;
}

void	check_editor(SDL_Event *event, int *editor_flag)
{
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
	{
		if (event->key.keysym.sym == SDLK_e)
			*editor_flag = 1;
	}
}

int		check_menu(SDL_Event *event)
{
		if (event->key.keysym.sym == SDLK_TAB)
			return (1);
		return (0);
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

void	handle_hud(char *hud_flags, SDL_Event *event)
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

int    handle_events(SDL_Event *event, t_data *data)
{
    check_quit(event, &data->quit);
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
	{
		if (check_menu(event) == 1)
			return (1);
	//check_editor(event, &data->editor_flag);
		handle_hud(&data->hud_flags, event);
	}
	return (0);
}
