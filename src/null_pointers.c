/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 20:36:08 by afonck            #+#    #+#             */
/*   Updated: 2020/02/10 15:14:18 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	null_game_pointers(t_game *game)
{
	game->surfs.fixed_mmap = NULL;
	game->surfs.rot_mmap = NULL;
	game->surfs.perspective_view = NULL;
	game->surfs.weapons = NULL;
	game->surfs.hud_faces_surf = NULL;
	game->surfs.enemy_texture[0] = NULL;
	game->surfs.enemy_texture[1] = NULL;
	game->surfs.game_over = NULL;
	game->surfs.victory = NULL;
	game->enemy = NULL;
	game->player.sector = NULL;
	game->weapon_anim[0] = NULL;
	game->weapon_anim[1] = NULL;
}

void	null_instr_pointers(t_editor *editor)
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

void	null_sdlmain_pointers(t_sdlmain *sdlmain)
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

void	null_map_pointers(t_map *map)
{
	map->sector_head = NULL;
	map->enemy_info = NULL;
	map->num_enemies = 0;
	map->num_sectors = 0;
	ft_bzero(map->name, 16);
	map->player_spawn.x = 0;
	map->player_spawn.y = 0;
}
