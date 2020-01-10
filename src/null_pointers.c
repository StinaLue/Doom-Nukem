/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 20:36:08 by afonck            #+#    #+#             */
/*   Updated: 2020/01/10 15:17:00 by afonck           ###   ########.fr       */
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
    menu->background = NULL;
    menu->menu_title = NULL;
    menu->options[0] = NULL;
    menu->options[1] = NULL;
    menu->options[2] = NULL;
    menu->options[3] = NULL;
}

void null_editor_pointers(t_editor *editor)
{
    editor->editor_surf = NULL;
    editor->instruct_surf = NULL;
}

void null_sdlmain_pointers(t_sdlmain *sdlmain)
{
    sdlmain->win = NULL;
    sdlmain->win_surf = NULL;
    sdlmain->font = NULL;
    sdlmain->music = NULL;
}

void null_map_pointers(t_map *map)
{
	map->sector_head = NULL;
}
