/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/15 13:54:14 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	quit_sdl_and_ttf(void)
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
	TTF_CloseFont(sdlmain->font);
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

int		free_menu(t_menu *menu)
{
	int i;

	i = 0;
	SDL_FreeSurface(menu->background);
	menu->background = NULL;
	SDL_FreeSurface(menu->menu_title);
	menu->menu_title = NULL;
	while (i < 4)
	{
		SDL_FreeSurface(menu->options[i]);
		menu->options[i] = NULL;
		i++;
	}
	return (EXIT_FAILURE);
}

int		free_fonts(t_editor *editor)
{
	TTF_CloseFont(editor->options_menu.font);
	editor->options_menu.font = NULL;
	TTF_CloseFont(editor->options_menu.font_title);
	editor->options_menu.font_title = NULL;
	TTF_CloseFont(editor->instruct_menu.font);
	editor->instruct_menu.font = NULL;
	TTF_CloseFont(editor->instruct_menu.font_title);
	editor->instruct_menu.font_title = NULL;
	return (EXIT_FAILURE);
}

int		free_fonts_surf(t_editor *editor)
{
	int i;

	i = 0;
	SDL_FreeSurface(editor->instruct_menu.title);
	editor->instruct_menu.title = NULL;
	SDL_FreeSurface(editor->options_menu.title);
	editor->options_menu.title = NULL;
	while (i < 5)
	{
		SDL_FreeSurface(editor->options_menu.options[i]);
		editor->options_menu.options[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		SDL_FreeSurface(editor->instruct_menu.instructions[i]);
		editor->instruct_menu.instructions[i] = NULL;
		i++;
	}
	return (EXIT_FAILURE);
}

int		free_editor(t_editor *editor)
{
	SDL_FreeSurface(editor->editor_surf);
	editor->editor_surf = NULL;
	SDL_FreeSurface(editor->instruct_surf);
	editor->instruct_surf = NULL;
	SDL_FreeSurface(editor->options_surf);
	editor->options_surf = NULL;
	free_fonts_surf(editor);
	free_fonts(editor);
	return (EXIT_FAILURE);
}
