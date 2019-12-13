/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/12 18:16:02 by afonck           ###   ########.fr       */
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

int		free_game(t_game *game)
{
	SDL_FreeSurface(game->surfs.fixed_mmap);
	game->surfs.fixed_mmap = NULL;
	SDL_FreeSurface(game->surfs.rot_mmap);
	game->surfs.rot_mmap = NULL;
	SDL_FreeSurface(game->surfs.perspective_view);
	game->surfs.perspective_view = NULL;
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

int		free_editor(t_editor *editor)
{
	SDL_FreeSurface(editor->editor_surf);
	editor->editor_surf = NULL;
	SDL_FreeSurface(editor->instruct_surf);
	editor->instruct_surf = NULL;
	return (EXIT_FAILURE);
}
