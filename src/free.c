/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:43:56 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 19:20:03 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	free_enemies(t_game *game, int num_enemies)
{
	int i;

	i = 0;
	if (num_enemies <= 0)
		return ;
	while (i < num_enemies)
	{
		alDeleteSources(1, &game->enemy[i].sound_src);
		i++;
	}
	ft_memdel((void **)&game->enemy);
}

int		free_game(t_game *game, t_map *map)
{
	int nb_enemy;

	nb_enemy = map->num_enemies;
	free_and_null_surf(game->surfs.fixed_mmap);
	free_and_null_surf(game->surfs.rot_mmap);
	free_and_null_surf(game->surfs.perspective_view);
	free_and_null_surf(game->surfs.weapons);
	free_and_null_surf(game->surfs.hud_faces_surf);
	free_and_null_surf(game->surfs.hud_weapons_surf[0]);
	free_and_null_surf(game->surfs.hud_weapons_surf[1]);
	free_and_null_surf(game->surfs.enemy_texture[0]);
	free_and_null_surf(game->surfs.enemy_texture[1]);
	free_and_null_surf(game->surfs.game_over);
	free_and_null_surf(game->surfs.victory);
	free_and_null_surf(game->surfs.fps);
	TTF_CloseFont(game->surfs.fps_font);
	game->surfs.fps_font = NULL;
	ft_memdel((void **)&game->surfs.fps_text);
	free_enemies(game, nb_enemy);
	return (EXIT_FAILURE);
}

int		free_menu(t_menu *menu)
{
	int i;

	i = 0;
	free_and_null_surf(menu->background);
	free_and_null_surf(menu->menu_title);
	while (i < 4)
	{
		free_and_null_surf(menu->options[i]);
		i++;
	}
	return (EXIT_FAILURE);
}

int		free_wall_textures(SDL_Surface **wall_textures)
{
	int i;

	i = 0;
	while (i < NB_WALL_TEXTURES)
	{
		free_and_null_surf(wall_textures[i]);
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
