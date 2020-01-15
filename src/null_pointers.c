/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 20:36:08 by afonck            #+#    #+#             */
/*   Updated: 2020/01/15 11:26:36 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void null_game_pointers(t_game *game)
{
    game->surfs.fixed_mmap = NULL;
    game->surfs.rot_mmap = NULL;
    game->surfs.perspective_view = NULL;
    game->surfs.weapons = NULL;
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
    editor->options_surf = NULL;
    editor->instruct_surf = NULL;
    editor->options_surf = NULL;
    editor->current_sector = NULL;
    editor->current_wall = NULL;
    while (i < 5)
    {
        editor->instruct_menu.instructions[i] = NULL;
        i++;
    }
    i = 0;
    while (i < 4)
    {
        editor->options_menu.options[i] = NULL;
        i++;
    }
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
}
