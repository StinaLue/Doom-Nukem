/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/30 11:51:31 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	quit_sdl_and_ttf(void)
{
	//Mix_CloseAudio();
	//Mix_Quit();
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
	//Mix_FreeMusic(sdlmain->music);
	//sdlmain->music = NULL;
	return (EXIT_FAILURE);
}

int		free_game(t_game *game, t_map *map)
{
	int nb_enemy;

	nb_enemy = map->num_enemies;
	SDL_FreeSurface(game->surfs.fixed_mmap);
	game->surfs.fixed_mmap = NULL;
	SDL_FreeSurface(game->surfs.rot_mmap);
	game->surfs.rot_mmap = NULL;
	SDL_FreeSurface(game->surfs.perspective_view);
	game->surfs.perspective_view = NULL;
	SDL_FreeSurface(game->surfs.weapons);
	game->surfs.weapons = NULL;
	SDL_FreeSurface(game->surfs.hud_faces_surf);
	game->surfs.hud_faces_surf = NULL;
	SDL_FreeSurface(game->surfs.enemy_texture[0]);
	game->surfs.enemy_texture[0] = NULL;
	SDL_FreeSurface(game->surfs.enemy_texture[1]);
	game->surfs.enemy_texture[1] = NULL;
	if (nb_enemy >= 0)
		ft_memdel((void **)&game->enemy);
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
	TTF_CloseFont(editor->opt_menu.font);
	editor->opt_menu.font = NULL;
	TTF_CloseFont(editor->opt_menu.font_title);
	editor->opt_menu.font_title = NULL;
	TTF_CloseFont(editor->instr_menu.font);
	editor->instr_menu.font = NULL;
	TTF_CloseFont(editor->instr_menu.font_title);
	editor->instr_menu.font_title = NULL;
	return (EXIT_FAILURE);
}

int		free_fonts_surf(t_editor *editor)
{
	int i;

	i = 0;
	SDL_FreeSurface(editor->instr_menu.title);
	editor->instr_menu.title = NULL;
	SDL_FreeSurface(editor->opt_menu.title);
	editor->opt_menu.title = NULL;
	while (i < NBOPTIONS)
	{
		SDL_FreeSurface(editor->opt_menu.options[i]);
		editor->opt_menu.options[i] = NULL;
		i++;
	}
	i = 0;
	while (i < NBINSTRUCTS)
	{
		SDL_FreeSurface(editor->instr_menu.instructs[i]);
		editor->instr_menu.instructs[i] = NULL;
		i++;
	}
	return (EXIT_FAILURE);
}

int		free_editor(t_editor *editor)
{
	SDL_FreeSurface(editor->editor_surf);
	editor->editor_surf = NULL;
	SDL_FreeSurface(editor->instr_surf);
	editor->instr_surf = NULL;
	SDL_FreeSurface(editor->opt_surf);
	editor->opt_surf = NULL;
	free_fonts_surf(editor);
	free_fonts(editor);
	return (EXIT_FAILURE);
}

int		free_wall_textures(SDL_Surface **wall_textures)
{
	int i;

	i = 0;
	while (i < NB_WALL_TEXTURES)
	{
		SDL_FreeSurface(wall_textures[i]);
		wall_textures[i] = NULL;
		i++;
	}
	return (EXIT_FAILURE);
}

int		free_map(t_map *map)
{
	int nb_enemy;

	nb_enemy = map->num_enemies;
	if (map->sector_head != NULL)
		free_sector_list(&map->sector_head);
	if (nb_enemy >= 1 && map->enemy_info != NULL)
		ft_memdel((void **)&map->enemy_info);
	map->num_enemies = 0;
	map->num_sectors = 0;
	return (EXIT_FAILURE);
}
