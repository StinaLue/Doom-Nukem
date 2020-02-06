/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 18:06:03 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

SDL_Surface *load_opti_bmp(char *file, SDL_Surface *dst_surf, Uint32 colorkey)
{
	SDL_Surface *opti_surf;
	SDL_Surface *surf;

	opti_surf = NULL;
	surf = NULL;
	if ((surf = load_bmp(file)) == NULL)
		return (NULL);
	if ((opti_surf = SDL_ConvertSurface(surf, dst_surf->format, 0)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "ConvertSurf err = %{r}s\n", SDL_GetError());
		SDL_FreeSurface(surf);
		return (NULL);
	}
	SDL_FreeSurface(surf);
	if (colorkey != 0)
	{
		if ((SDL_SetColorKey(opti_surf, SDL_TRUE, colorkey)) != 0)
		{
			ft_dprintf(STDERR_FILENO, "SetColorKey err = %{r}s\n", SDL_GetError());
			SDL_FreeSurface(opti_surf);
			return (NULL);
		}
	}
	return (opti_surf);
}

int	init_gamesurfs_struct(t_gamesurfs *gamesurfs, t_sdlmain *sdlmain)
{
	if ((gamesurfs->rot_mmap = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0)) == NULL) //--> should be a square that can handle the size of a sector
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->fixed_mmap = SDL_CreateRGBSurface(0, 51 * MAPMULTIPLIER, 51 * MAPMULTIPLIER, 32, 0, 0, 0, 0)) == NULL) //--> should be a square that can handle the size of the whole map
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->perspective_view = SDL_CreateRGBSurface(0, sdlmain->win_surf->w/2, sdlmain->win_surf->h/2, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	//if ((gamesurfs->weapons = load_bmp("assets/shadow.bmp")) == NULL)
	if ((gamesurfs->weapons = load_opti_bmp("assets/weapons/weapons.bmp", gamesurfs->perspective_view/*sdlmain->win_surf*/, 0xFFFFFF)) == NULL)
		return (error_return("load weapon bmp surf error\n", NULL));
	if ((gamesurfs->hud_faces_surf = load_opti_bmp("assets/hud/hud_faces.bmp", gamesurfs->perspective_view, 0x00FFFF)) == NULL)
		return (error_return("load hud faces bmp surf error\n", NULL));
	if ((gamesurfs->enemy_texture[0] = load_opti_bmp("assets/enemy_sprites/UndeadWarrior.bmp", gamesurfs->perspective_view, 0x00FFFF)) == NULL)
		return (error_return("load UndeadWarrior surf error\n", NULL));
	if ((gamesurfs->enemy_texture[1] = load_opti_bmp("assets/enemy_sprites/Ogre.bmp", gamesurfs->perspective_view, 0x00FFFF)) == NULL)
		return (error_return("load Ogre surf error\n", NULL));
	gamesurfs->weapons_rect = create_sdlrect(0, 0, 232, 200);
	gamesurfs->hud_faces_rect = create_sdlrect(0, 0, gamesurfs->hud_faces_surf->w / 3, gamesurfs->hud_faces_surf->h / 5);
	gamesurfs->anim_timer = 0;
	gamesurfs->hud_timer = 0;
	gamesurfs->current_frame = 0;
	return (0);
}

void	init_data_struct(t_data *data)
{
	data->hud_flags = 0;
}

void	init_player_struct(t_player *player, t_map *map)
{
	player->pos.x = map->player_spawn.x;//49;
	player->pos.y = map->player_spawn.y;//35;
	player->sector = get_sector_by_pos(map->sector_head, player->pos);
	player->angle = 0;
	player->view_z = 0;
	player->inertia.x = 0;
	player->inertia.y = 0;
	player->fov.x = 100;
	player->fov.y = 100;
	player->true_fov = 1.5708; //hardcoded 90deg
	player->health = 100;
	player->is_moving = 0;
	player->anim = 0;
	player->current_weapon = 0;
}

void	get_enemysprite_rect(SDL_Rect *rect, int which_enemy, SDL_Surface *sprite_sheet)
{
	rect->x = 0;
	rect->y = 0;
	rect->w = sprite_sheet->w / 8;
	if (which_enemy == 0)
		rect->h = sprite_sheet->h / 9;
	else if (which_enemy == 1)
		rect->h = sprite_sheet->h / 11;
}

int	init_enemy_struct(t_game *game, t_map *map)
{
	int				current_enemy;
	t_enemy_info	*enemy_info;

	current_enemy = 0;
	if (map->num_enemies <= 0)
		return (0);
	if ((game->enemy = (t_enemy *)malloc(sizeof(t_enemy) * map->num_enemies)) == NULL)
		return (1);
	while (current_enemy < map->num_enemies)
	{
		enemy_info = &map->enemy_info[current_enemy];
		game->enemy[current_enemy].pos = create_vecdb(enemy_info->enemy_spawn.x, enemy_info->enemy_spawn.y);
		game->enemy[current_enemy].texture = game->surfs.enemy_texture[enemy_info->which_enemy];
		game->enemy[current_enemy].angle = 0;
		get_enemysprite_rect(&game->enemy[current_enemy].clip_tex, enemy_info->which_enemy, game->enemy[current_enemy].texture);
		game->enemy[current_enemy].state = 0;
		game->enemy[current_enemy].health = 100;
		alGenSources(1, &game->enemy[current_enemy].sound_src);
		init_source(game->enemy[current_enemy].sound_src, 1, 5, 1);
		current_enemy++;
	}
	return (0);
}
