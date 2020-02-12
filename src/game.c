/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:46:18 by afonck            #+#    #+#             */
/*   Updated: 2020/02/12 01:13:14 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

int				blit_uzi(t_gamesurfs *gamesurfs, SDL_Surface *dest, int *anim)
{
	gamesurfs->weapons_rect.x = \
			gamesurfs->current_frame * gamesurfs->weapons_rect.w;
	gamesurfs->weapons_rect.y = gamesurfs->weapons_rect.h * 2;
	if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->weapons_rect, \
							dest, NULL) != 0)
		return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
	if (*anim == 1)
	{
		if (gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0)
			gamesurfs->anim_timer = SDL_GetTicks();
		if ((SDL_GetTicks() - gamesurfs->anim_timer) >= 150)
		{
			gamesurfs->current_frame++;
			gamesurfs->anim_timer = SDL_GetTicks();
		}
		if (gamesurfs->current_frame >= 3)
		{
			gamesurfs->current_frame = 0;
			gamesurfs->weapons_rect.x = 0;
			*anim = 0;
		}
	}
	else
		gamesurfs->anim_timer = 0;
	return (0);
}

int				blit_katana(t_gamesurfs *gamesurfs, \
								SDL_Surface *dest, int *anim)
{
	gamesurfs->weapons_rect.x = gamesurfs->current_frame \
					* gamesurfs->weapons_rect.w;
	if (*anim == 0)
		gamesurfs->weapons_rect.y = 0;
	else if (*anim == 1 && gamesurfs->current_frame > 2)
		gamesurfs->weapons_rect.y = gamesurfs->weapons_rect.h;
	if (SDL_BlitScaled(gamesurfs->weapons, \
				&gamesurfs->weapons_rect, dest, NULL) != 0)
		return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
	if (*anim == 1)
	{
		if (gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0)
			gamesurfs->anim_timer = SDL_GetTicks();
		if ((SDL_GetTicks() - gamesurfs->anim_timer) >= 150)
		{
			gamesurfs->current_frame++;
			gamesurfs->anim_timer = SDL_GetTicks();
		}
		if (gamesurfs->current_frame >= 4)
		{
			gamesurfs->current_frame = 0;
			gamesurfs->weapons_rect.x = 0;
			*anim = 0;
		}
	}
	else
		gamesurfs->anim_timer = 0;
	return (0);
}

void			draw_crosshair(SDL_Surface *dest)
{
	t_vec top_cross;
	t_vec bottom_cross;
	t_vec left_cross;
	t_vec right_cross;

	top_cross.x = dest->w / 2;
	top_cross.y = (dest->h / 2) + 10;
	bottom_cross.x = dest->w / 2;
	bottom_cross.y = (dest->h / 2) - 10;
	left_cross.x = (dest->w / 2) - 10;
	left_cross.y = dest->h / 2;
	right_cross.x = (dest->w / 2) + 10;
	right_cross.y = dest->h / 2;
	draw_line(top_cross, bottom_cross, dest, 0xff0000);
	draw_line(left_cross, right_cross, dest, 0xff0000);
}

int				blit_weapon(t_game *game, SDL_Surface *dest, \
		int weapon, int available_weapons)
{
	int return_val;

	if (available_weapons == 0)
		return (0);
	return_val = (*game->weapon_anim[weapon])(&game->surfs, dest, \
					&game->player.anim);
	draw_crosshair(dest);
	return (return_val);
}

void			soft_reset_player(t_player *player, t_map *map)
{
	player->health = 100;
	player->pos = vec_to_vecdb(map->player_spawn);
	player->sector = get_sector_by_pos(map->sector_head, \
										player->pos);
	if (player->pos.x == -1 && player->pos.y == -1 && map->sector_head)
	{
		player->sector = map->sector_head;
		player->pos = map->sector_head->sector_center;
	}
}

int				player_hurt_anim(int health, SDL_Rect *surf_rect)
{
	int y_anim;

	y_anim = 0;
	if (health > 80)
		y_anim = 0;
	else if (health > 60)
		y_anim = surf_rect->h * 1;
	else if (health > 40)
		y_anim = surf_rect->h * 2;
	else if (health > 20)
		y_anim = surf_rect->h * 3;
	else
		y_anim = surf_rect->h * 4;
	return (y_anim);
}

void			set_listener_ori(double angle, t_vecdb player_pos)
{
	ALfloat	orix;
	ALfloat oriy;
	t_vecdb test;
	ALfloat listener_ori[6];

	orix = sin(angle) * -5 + player_pos.x;
	oriy = cos(angle) * 5 + player_pos.y;
	test.x = orix;
	test.y = oriy;
	listener_ori[0] = orix;
	listener_ori[1] = oriy;
	listener_ori[2] = cross_product(test, player_pos);
	listener_ori[3] = 0;
	listener_ori[4] = 1;
	listener_ori[5] = 0;
	alListenerfv(AL_ORIENTATION, listener_ori);
	//printf("vec direc x %f y %f\n", orix, oriy);
}

void			stop_enem_soundsources(t_enemy *enemies, int nb_enemies)
{
	int i;

	i = 0;
	while (i < nb_enemies)
	{
		alSourceStop(enemies[i].sound_src);
		i++;
	}
}

void	check_hit_uzi(int num_enemies, int *is_enemy_hit, t_vecdb dir_player, t_enemy *enemy)
{
	int i;

	i = 0;
	while (i < num_enemies && *is_enemy_hit == 0)
	{
		if (get_point_distance(dir_player, enemy[i].pos) < 22)
		{
			enemy[i].health -= 1;
			*is_enemy_hit = 1;
		}
		i++;
	}
}

void			raycast_uzi(t_player *player, \
								t_enemy *enemy, int num_enemies)
{
	int		is_enemy_hit;
	t_vecdb	dir_player;
	int		nb_steps;
	t_vecdb	step;

	nb_steps = 0;
	is_enemy_hit = 0;
	dir_player.x = -sin(player->angle) * 2 + player->pos.x;
	dir_player.y = cos(player->angle) * 2 + player->pos.y;
	step = vecdb_diff(dir_player, player->pos);
	while (nb_steps < 100 && is_enemy_hit == 0)
	{
		check_hit_uzi(num_enemies, &is_enemy_hit, dir_player, enemy);
		dir_player = vecdb_add(dir_player, step);
		nb_steps++;
	}
}

void	katana_hit(t_player *player, t_enemy *enemy, int num_enemies)
{
	int i;

	i = 0;
	while (i < num_enemies)
	{
		if (get_point_distance(player->pos, enemy[i].pos) < 22)
			enemy[i].health -= 1;
		i++;
	}
}

int				player_attack(t_enemy *enemy, \
					t_player *player, t_map *map, t_gamesurfs *surfs)
{
	if (player->current_weapon == 0 && player->anim == 1 && surfs->current_frame == 3)
	{
		katana_hit(player, enemy, map->num_enemies);
	}
	else if (player->current_weapon == 1 \
			&& player->anim == 1 && surfs->current_frame == 2)
	{
		raycast_uzi(player, enemy, map->num_enemies);
	}
	return (0);
}

int				game_loop(t_doom *doom)
{
	t_game		*game;
	t_sdlmain	*sdlmain;
	Uint32		startclock;
	int			itt;
	t_view		view;

	game = &(doom->game);
	sdlmain = &(doom->sdlmain);
	itt = 0;
	startclock = 0;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_WarpMouseInWindow(sdlmain->win, sdlmain->win_surf->w / 2, \
							sdlmain->win_surf->h / 2);
	startclock = SDL_GetTicks();
	if (!is_buffer_playing(sdlmain->sound.source[0], sdlmain->sound.buffer[0]))
		play_game_music(game, sdlmain, doom);
	while (doom->state == GAME_STATE)
	{
		ft_bzero(game->surfs.perspective_view->pixels, \
					game->surfs.perspective_view->h * \
						game->surfs.perspective_view->pitch);
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
			if (handle_events(doom) != 0)
				break ;
		play_sound(game, sdlmain, &doom->map);
		if (game->player.health <= 0)
			game_over_loop(doom);
		else if (game->player.sector->is_goal == 1)
			win_loop(doom);
		handle_keys(doom, SDL_GetKeyboardState(NULL));
		//printf("z:%f\nzinertia:%f\n", game->player.posz, game->player.zinertia);
		alListener3f(AL_POSITION, game->player.pos.x, game->player.pos.y, 0);
		//printf("vec player x %f y %f\n", game->player.pos.x, game->player.pos.y);
		set_listener_ori(game->player.angle, game->player.pos);
		if (game->data.hud_flags & TEXFLAG)
			game->surfs.perspective_view->userdata = "untextured";
		else
			game->surfs.perspective_view->userdata = "textured";
		view = init_view(&game->player, game->surfs.perspective_view);
		draw_view_recursive(game, doom->wall_textures, \
							view, game->player.sector);
		if (blit_enemies(game, game->surfs.perspective_view, &doom->map) != 0)
			return (error_return("Blit enemies error\n", NULL));
		if (blit_weapon(game, game->surfs.perspective_view, \
					game->player.current_weapon, doom->map.weapon_choice) != 0)
			return (error_return("Blit weapon error\n", NULL));
		player_attack(game->enemy, &game->player, &doom->map, &game->surfs);
		enemy_action(game->enemy, &game->player, doom->map.num_enemies);
		if (game_blit_hud(&doom->map, game, itt, startclock != 0))
			return (1);
		if ((SDL_BlitScaled(game->surfs.perspective_view, \
							NULL, sdlmain->win_surf, NULL)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", \
					SDL_GetError()));
		if ((draw_map(sdlmain, game, &doom->map, \
						&game->data.hud_flags)) == 1)
			return (error_return("error during map drawing\n", NULL));
		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
			return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", \
						SDL_GetError()));
			itt++;
	}
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_WarpMouseInWindow(sdlmain->win, sdlmain->win_surf->w / 2, \
				sdlmain->win_surf->h / 2);
	return (0);
}
