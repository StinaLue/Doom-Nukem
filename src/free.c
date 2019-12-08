/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/07 20:29:24 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	quit_sdl_and_ttf()
{
	TTF_Quit();
	SDL_Quit();
	//TTF_Quit();
}

int		free_sdlmain(t_sdlmain *sdlmain)
{
	SDL_DestroyWindow(sdlmain->win);
	sdlmain->win = NULL;
	sdlmain->win_surf = NULL;
	return (EXIT_FAILURE);
}

int		free_doom(t_doom *doom)
{
	SDL_FreeSurface(doom->surfs.fixed_mmap);
	doom->surfs.fixed_mmap = NULL;
	SDL_FreeSurface(doom->surfs.rot_mmap);
	doom->surfs.rot_mmap = NULL;
	SDL_FreeSurface(doom->surfs.perspective_mmap);
	doom->surfs.perspective_mmap = NULL;
	return (EXIT_FAILURE);
}

int		free_menu(t_menu *menu)
{
    SDL_FreeSurface( menu->background );
	menu->background = NULL;
    SDL_FreeSurface( menu->menu_title );
	menu->menu_title = NULL;
    SDL_FreeSurface( menu->first_option );
	menu->first_option = NULL;
    SDL_FreeSurface( menu->second_option );
    menu->second_option = NULL;
    
    //Close the font that was used
    TTF_CloseFont( menu->font );
	menu->font = NULL;
	return (EXIT_FAILURE);
}
