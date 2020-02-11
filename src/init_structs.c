/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 22:33:43 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

int			init_gamesurfs_struct(t_gamesurfs *gamesurfs, t_sdlmain *sdlmain)
{
	if (create_game_surfaces(gamesurfs, sdlmain) != 0)
		return (1);
	if (load_game_textures(gamesurfs) != 0)
		return (1);
	assign_sdlcolor(&gamesurfs->fps_color, 255, 0, 0);
	if ((gamesurfs->fps_font = \
		TTF_OpenFont("assets/fonts/dooM.ttf", 14)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	if ((gamesurfs->fps = \
			TTF_RenderText_Solid(gamesurfs->fps_font, "fps = 00", \
			gamesurfs->fps_color)) == NULL)
		return (error_return("TTF_RenderText error = %{r)s\n", TTF_GetError()));
	gamesurfs->weapons_rect = create_sdlrect(0, 0, 232, 200);
	gamesurfs->hud_faces_rect = create_sdlrect(0, 0, \
			gamesurfs->hud_faces_surf->w / 3, gamesurfs->hud_faces_surf->h / 5);
	gamesurfs->hud_weapons_rect[0] = create_sdlrect(0, 0, 232, 200);
	gamesurfs->hud_weapons_rect[1] = create_sdlrect(100, 500, 116, 100);
	gamesurfs->dst_fps_rect = \
			create_sdlrect((gamesurfs->perspective_view->w / 2) - 12, 0, 0, 0);
	gamesurfs->anim_timer = 0;
	gamesurfs->hud_timer = 0;
	gamesurfs->current_frame = 0;
	gamesurfs->hud_weapons_color[0] = COLOR_NORMAL;
	gamesurfs->hud_weapons_color[1] = COLOR_NORMAL;
	return (0);
}

void		init_data_struct(t_data *data)
{
	data->hud_flags = 0;
}

void		init_player_struct(t_player *player, t_map *map)
{
	player->pos.x = map->player_spawn.x;
	player->pos.y = map->player_spawn.y;
	player->sector = get_sector_by_pos(map->sector_head, player->pos);
	player->angle = 0;
	player->posz = 0;
	player->height = 10;
	player->view_z = 0;
	player->inertia.x = 0;
	player->inertia.y = 0;
	player->true_fov = 1.5708;
	player->health = 100;
	player->is_moving = 0;
	player->anim = 0;
	player->current_weapon = 0;
	player->movespeed = WALK;
}

void	init_enemy(t_enemy *enemy, t_enemy_info *enemy_info, t_game *game, t_map *map)
{
	enemy->pos = create_vecdb(enemy_info->enemy_spawn.x, \
	enemy_info->enemy_spawn.y);
	enemy->sector = get_sector_by_pos(map->sector_head, enemy->pos);
	if (enemy->sector)
		enemy->posz = enemy->sector->floor_height;
	else
		enemy->posz = 0;
	enemy->texture = game->surfs.enemy_texture[enemy_info->which_enemy];
	enemy->angle = 0;
	get_enemysprite_rect(&enemy->clip_tex, \
					enemy_info->which_enemy, enemy->texture);
	enemy->state = 0;
	enemy->health = 100;
	enemy->anim_timer = 0;
	enemy->current_frame = 0;
	alGenSources(1, &enemy->sound_src);
	init_source(enemy->sound_src, 1, 5, 1);
}

int			init_enemies(t_game *game, t_map *map)
{
	int				current_enemy;
	t_enemy_info	*enemy_info;

	current_enemy = 0;
	if (map->num_enemies <= 0)
		return (0);
	if ((game->enemy = \
		(t_enemy *)malloc(sizeof(t_enemy) * map->num_enemies)) == NULL)
		return (1);
	while (current_enemy < map->num_enemies)
	{
		enemy_info = &map->enemy_info[current_enemy];
		init_enemy(&game->enemy[current_enemy], enemy_info, game, map);
		current_enemy++;
	}
	return (0);
}
