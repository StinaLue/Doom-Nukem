/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/10 14:06:11 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	quit_sdl_and_ttf()
{
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

int		free_sdlmain(t_sdlmain *sdlmain)
{
	SDL_DestroyWindow(sdlmain->win);
	sdlmain->win = NULL;
	sdlmain->win_surf = NULL;
    TTF_CloseFont( sdlmain->font );
	sdlmain->font = NULL;
	Mix_FreeMusic(sdlmain->music);
	sdlmain->music = NULL;
	return (EXIT_FAILURE);
}

int		free_game(t_game *game)
{
	SDL_FreeSurface(game->surfs.fixed_mmap);
	game->surfs.fixed_mmap = NULL;
	SDL_FreeSurface(game->surfs.rot_mmap);
	game->surfs.rot_mmap = NULL;
	SDL_FreeSurface(game->surfs.perspective_view);
	game->surfs.perspective_view = NULL;
	SDL_FreeSurface(game->surfs.weapons);
	game->surfs.weapons = NULL;
	return (EXIT_FAILURE);
}

/*
--------------- FREE EDITOR MENU ? ---------------
*/

int		free_menu(t_menu *menu)
{
    SDL_FreeSurface( menu->background );
	menu->background = NULL;
    SDL_FreeSurface( menu->menu_title );
	menu->menu_title = NULL;
    SDL_FreeSurface( menu->options[0] );
	menu->options[0] = NULL;
    SDL_FreeSurface( menu->options[1] );
    menu->options[1] = NULL;
    SDL_FreeSurface( menu->options[2] );
    menu->options[2] = NULL;
    SDL_FreeSurface( menu->options[3] );
    menu->options[3] = NULL;
    
	return (EXIT_FAILURE);
}

int		free_editor(t_editor *editor)
{
	SDL_FreeSurface(editor->editor_surf);
	editor->editor_surf = NULL;
	SDL_FreeSurface(editor->instruct_surf);
	editor->instruct_surf = NULL;
	return (EXIT_FAILURE);
}
