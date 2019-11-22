/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:22:12 by afonck            #+#    #+#             */
/*   Updated: 2019/11/22 16:38:03 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_quit(SDL_Event *event, int *quit)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && \
		event->key.keysym.sym == SDLK_ESCAPE))
		*quit = 1;
}

void	handle_hud(char *hud_flags, SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
	{
        if (event->key.keysym.sym == SDLK_1)
        {
		    if ((*hud_flags & ROT_MAP_SHOW) == 0)
			    *hud_flags |= ROT_MAP_SHOW;
		    else
			    *hud_flags &= ~(ROT_MAP_SHOW);
        }
        else if (event->key.keysym.sym == SDLK_2)
        {
            if ((*hud_flags & FIX_MAP_SHOW) == 0)
	    		*hud_flags |= FIX_MAP_SHOW;
		    else
    			*hud_flags &= ~(FIX_MAP_SHOW);
        }
	}	
}

void    handle_events(SDL_Event *event, t_data *data)
{
    check_quit(event, &data->quit);
    handle_hud(&data->hud_flags, event);
}
