/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:46:18 by afonck            #+#    #+#             */
/*   Updated: 2020/02/05 21:22:24 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

int blit_uzi(t_gamesurfs *gamesurfs, SDL_Surface *dest, int *anim)//, t_sound *sound)
{
	gamesurfs->weapons_rect.x = gamesurfs->current_frame * gamesurfs->weapons_rect.w;
	gamesurfs->weapons_rect.y = gamesurfs->weapons_rect.h * 2;
	if (*anim == 1)
	{
		if (gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0)
		{
			gamesurfs->anim_timer = SDL_GetTicks();
			//alSourcef(sound->source[1], AL_PITCH, 1.3);
			//alSourcei(sound->source[1], AL_BUFFER, sound->buffer[1]);
			//alSourcePlay(sound->source[1]);
		}
		//if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->katana[gamesurfs->current_frame], dest, NULL) != 0)
		if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->weapons_rect, dest, NULL) != 0)
			return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
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
	{
		if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->weapons_rect, dest, NULL) != 0)
			return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
		gamesurfs->anim_timer = 0;
	}
	
	return (0);
}

int blit_katana(t_gamesurfs *gamesurfs, SDL_Surface *dest, int *anim)//, t_sound *sound)
{
	gamesurfs->weapons_rect.x = gamesurfs->current_frame * gamesurfs->weapons_rect.w;
	gamesurfs->weapons_rect.y = 0;
	if (*anim == 1)
	{
		if (gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0)
		{
			gamesurfs->anim_timer = SDL_GetTicks();
			//alSourcef(sound->source[1], AL_PITCH, 1.3);
			//alSourcei(sound->source[1], AL_BUFFER, sound->buffer[1]);
			//alSourcePlay(sound->source[1]);
		}
		//if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->katana[gamesurfs->current_frame], dest, NULL) != 0)
		if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->weapons_rect, dest, NULL) != 0)
			return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
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
	{
		if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->weapons_rect, dest, NULL) != 0)
			return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
		gamesurfs->anim_timer = 0;
	}
	
	return (0);
}

void	draw_crosshair(SDL_Surface *dest)
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

int	blit_weapon(t_game *game, SDL_Surface *dest, int weapon)//, t_sound *sound)
{
	int return_val;

	return_val = (*game->weapon_anim[weapon])(&game->surfs, dest, &game->player.anim);//, sound);
	draw_crosshair(dest);
	return (return_val);
}

int	player_hurt_anim(int health, SDL_Rect *surf_rect)
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

int	blit_hud_faces(t_game *game)
{
	t_gamesurfs *surfs;
	t_data		*data;
	SDL_Rect	dst;

	surfs = &game->surfs;
	data = &game->data;
	if ((data->hud_flags & HEALTH_STATUS))
	{
		surfs->hud_faces_rect.y = player_hurt_anim(game->player.health, &surfs->hud_faces_rect);
		dst.y = 0;
		dst.w = surfs->perspective_view->w / 8;
		dst.x = surfs->perspective_view->w - dst.w;
		dst.h = surfs->perspective_view->h / 6;
		if ((SDL_GetTicks() - surfs->hud_timer) >= 1000)
		{
			surfs->hud_timer = SDL_GetTicks();
			if (surfs->hud_faces_rect.x < surfs->hud_faces_rect.w * 2)
				surfs->hud_faces_rect.x += surfs->hud_faces_rect.w;
			else
				surfs->hud_faces_rect.x = 0;
		}
		if ((SDL_BlitScaled(surfs->hud_faces_surf, &surfs->hud_faces_rect, surfs->perspective_view, &dst)) != 0)
			return (1);
	}
	return (0);
}

int	blit_enemies(t_game *game, SDL_Surface *dest)
{
	if ((SDL_BlitScaled(game->enemy[0].texture, &game->enemy[0].clip_tex, dest, NULL)) != 0)
		return (error_return("SDL_BlitScaled error: %{r}s\n", SDL_GetError()));
	return (0);
}

int is_source_playing(ALuint source)
{
	ALenum state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return (state == AL_PLAYING);
}

int	play_sound(t_game *game, t_sdlmain *sdlmain)
{
	t_gamesurfs *gamesurfs;
	t_sound		*sound;
	t_player	*player;

	gamesurfs = &game->surfs;
	sound = &sdlmain->sound;
	player = &game->player;
	if (player->current_weapon == 0)
	{
		if (player->anim == 1 && gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0 && !is_source_playing(sound->source[1]))
		{
			alSourcef(sound->source[1], AL_PITCH, 1.6);
			alSourcei(sound->source[1], AL_BUFFER, sound->buffer[1]);
			alSourcePlay(sound->source[1]);
		}
		else if (player->anim == 0 && gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0 && is_source_playing(sound->source[1]))
			alSourceStop(sound->source[1]);
	}
	if (player->current_weapon == 1)
	{
		if (player->anim == 1 && gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0 && !is_source_playing(sound->source[1]))
		{
			alSourcef(sound->source[1], AL_PITCH, 1);
			alSourcei(sound->source[1], AL_BUFFER, sound->buffer[3]);
			alSourcePlay(sound->source[1]);
		}
		else if (player->anim == 0 && gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0 && is_source_playing(sound->source[1]))
			alSourceStop(sound->source[1]);
	}
	if (player->is_moving == 1 && !is_source_playing(sound->source[2]))
		alSourcePlay(sound->source[2]);
	else if (player->is_moving == 0)
		alSourcePause(sound->source[2]);
	return (0);
}

int game_loop(t_doom *doom)
{
	t_game		*game;
	t_sdlmain	*sdlmain;
	Uint32		startclock = 0;
	int			itt = 0;
	t_view		view;

	game = &(doom->game);
	sdlmain = &(doom->sdlmain);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_WarpMouseInWindow(sdlmain->win, sdlmain->win_surf->w / 2, sdlmain->win_surf->h / 2);
	startclock = SDL_GetTicks();
	while (doom->state == GAME_STATE)
	{
		ft_bzero(game->surfs.perspective_view->pixels, game->surfs.perspective_view->h * game->surfs.perspective_view->pitch);
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
			if (handle_events(doom) != 0)
				break ;
		play_sound(game, sdlmain);
		handle_keys(doom, SDL_GetKeyboardState(NULL));//, &sdlmain->sound);
		alListener3f(AL_POSITION, game->player.pos.x, game->player.pos.y, 0);
		alSource3f(sdlmain->sound.source[0], AL_POSITION, doom->map.sector_head->wall_head->start.x, doom->map.sector_head->wall_head->start.y, 0);
		alSource3f(sdlmain->sound.source[1], AL_POSITION, doom->map.sector_head->wall_head->end.x, doom->map.sector_head->wall_head->end.y, 0);
		if (game->data.hud_flags & COLORFLAG)
			game->surfs.perspective_view->userdata = "yescolor";
		else
			game->surfs.perspective_view->userdata = "nocolor";
		//draw_perspective_view(game->surfs.perspective_view, &game->player, doom->wall_textures);
		//if ((SDL_BlitScaled(game->surfs.weapons, &game->surfs.katana[(int)((float)SDL_GetTicks() / 400) % 4], game->surfs.perspective_view, NULL)) != 0)
		//	printf("%s\n", SDL_GetError());

		//print sector index
		/*int i = 0;
		t_sector_node *node = doom->map.sector_head;
		while (node != NULL)
		{
			if (game->player.sector == node)
				printf("sector: %d\n", i + 1);
			i++;
			node = node->next;
		}*/

		//draw_perspective_view(game->surfs.perspective_view, &game->player, doom->wall_textures);
		view.left = doom->game.player.fov;
		view.right = doom->game.player.fov;
		view.left.x *= -1;
		draw_view_recursive(game->surfs.perspective_view, doom->wall_textures, view, doom->game.player.sector, &doom->game.player);
		//if (blit_enemies(game, game->surfs.perspective_view) != 0)
		//	return (error_return("Blit enemies error\n", NULL));
		if (blit_weapon(game, game->surfs.perspective_view, game->player.current_weapon) != 0)//, &sdlmain->sound) != 0)
			return (error_return("Blit weapon error\n", NULL));

		if ((blit_hud_faces(game)) == 1)
			return (error_return("error during blit_hud_faces\n", NULL));
		if ((SDL_BlitScaled(game->surfs.perspective_view, NULL, sdlmain->win_surf, NULL)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
		if ((draw_map(sdlmain, game, &doom->map, &game->data.hud_flags)) == 1)
			return (error_return("error during map drawing\n", NULL));
		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
			return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError()));

		itt++;
		if (SDL_GetTicks() - startclock >= 1000)
		{
			printf("fps:%d\n", itt);
			itt = 0;
			startclock = SDL_GetTicks();
		}
	}
	SDL_SetRelativeMouseMode(SDL_FALSE);
	return (0);
}
