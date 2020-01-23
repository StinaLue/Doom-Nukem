/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 20:36:08 by afonck            #+#    #+#             */
/*   Updated: 2020/01/23 19:19:38 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void null_game_pointers(t_game *game)
{
    game->surfs.fixed_mmap = NULL;
    game->surfs.rot_mmap = NULL;
    game->surfs.perspective_view = NULL;
    game->surfs.weapons = NULL;
	game->surfs.hud_faces_surf = NULL;
	game->surfs.enemy_texture[0] = NULL;
	game->surfs.enemy_texture[1] = NULL;
	game->enemy = NULL;
}

void null_menu_pointers(t_menu *menu)
{
    int i;

    i = 0;
    menu->background = NULL;
    menu->menu_title = NULL;
    while (i < 4)
    {
        menu->options[i] = NULL;
        i++;
    }
}

void null_editor_pointers(t_editor *editor)
{
    int i;

    i = 0;
    editor->editor_surf = NULL;
    editor->opt_surf = NULL;
    editor->instr_surf = NULL;
    editor->current_sector = NULL;
    editor->current_wall = NULL;
    editor->mouse_surf = NULL;
    editor->wall_tmp.wall_type = 0;//1;
	editor->wall_tmp.type_color = 0xFF0000;
    while (i < NBINSTRUCTS)
    {
        editor->instr_menu.instructs[i] = NULL;
        i++;
    }
    i = 0;
    while (i < NBOPTIONS)
    {
        editor->opt_menu.options[i] = NULL;
        i++;
    }
    i = 0;
    null_map_pointers(&editor->edit_map);
}

void    null_sdlmain_pointers(t_sdlmain *sdlmain)
{
    sdlmain->win = NULL;
    sdlmain->win_surf = NULL;
    sdlmain->font = NULL;
    sdlmain->music = NULL;
}

void    null_map_pointers(t_map *map)
{
	map->sector_head = NULL;
	map->enemy_info = NULL;
}
