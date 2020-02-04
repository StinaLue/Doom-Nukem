/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 20:36:08 by afonck            #+#    #+#             */
/*   Updated: 2020/02/04 22:21:17 by sluetzen         ###   ########.fr       */
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

void    null_option_pointers(t_editor *editor)
{
    int i;

    i = 0;
    while (i < NBOPTIONS)
    {
        editor->opt_menu.options[i] = NULL;
        i++;
    }
    editor->opt_menu.title = NULL;
    editor->opt_menu.ceiling_h_surf = NULL;
    editor->opt_menu.floor_h_surf = NULL;
}

void    null_instr_pointers(t_editor *editor)
{
    int i;

    i = 0;
    while (i < NBINSTRUCTS)
    {
        editor->instr_menu.instructs[i] = NULL;
        i++;
    }
	editor->instr_menu.font = NULL;
	editor->instr_menu.font_title = NULL;
	editor->instr_menu.title = NULL;
}

void    null_editor_pointers(t_editor *editor)
{
    editor->editor_surf = NULL;
    editor->opt_surf = NULL;
    editor->instr_surf = NULL;
    editor->current_sector = NULL;
    editor->current_wall = NULL;
    editor->mouse_surf = NULL;
    editor->alert_convex_surf = NULL;
    editor->alert_loading_surf = NULL;
    editor->loading_success_surf = NULL;
    editor->wall_tmp.wall_type = 0;//1;
	editor->wall_tmp.type_color = 0xFF0000;
    null_option_pointers(editor);
    null_instr_pointers(editor);
    null_map_pointers(&editor->edit_map);
}

void    null_sdlmain_pointers(t_sdlmain *sdlmain)
{
    sdlmain->win = NULL;
    sdlmain->win_surf = NULL;
    sdlmain->font = NULL;

	sdlmain->sound.device = NULL;
	sdlmain->sound.context = NULL;
}

void	null_walltextures_pointers(SDL_Surface **wall_textures)
{
	int i;

	i = 0;
	while (i < NB_WALL_TEXTURES)
	{
		wall_textures[i] = NULL;
		i++;
	}
}

void    null_map_pointers(t_map *map)
{
	map->sector_head = NULL;
	map->enemy_info = NULL;
}
