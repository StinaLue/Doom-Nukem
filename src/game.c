/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:46:18 by afonck            #+#    #+#             */
/*   Updated: 2020/02/01 19:44:47 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

int blit_katana(t_gamesurfs *gamesurfs, SDL_Surface *dest, int *anim, t_sound *sound)
{
	if (*anim == 1)
	{
		if (gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0)
		{
			gamesurfs->anim_timer = SDL_GetTicks();
			alSourcef(sound->source[1], AL_PITCH, 1.3);
			alSourcei(sound->source[1], AL_BUFFER, sound->buffer[1]);
			alSourcePlay(sound->source[1]);
		}
		if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->katana[gamesurfs->current_frame], dest, NULL) != 0)
			return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
		if ((SDL_GetTicks() - gamesurfs->anim_timer) >= 150)
		{
			gamesurfs->current_frame++;
			gamesurfs->anim_timer = SDL_GetTicks();
		}
		if (gamesurfs->current_frame >= 4)
		{
			gamesurfs->current_frame = 0;
			*anim = 0;
		}
	}
	else
	{
		if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->katana[0], dest, NULL) != 0)
			return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
		gamesurfs->anim_timer = 0;
	}
	
	return (0);
}

int	blit_weapon(t_game *game, SDL_Surface *dest, int weapon, t_sound *sound)
{
	int return_val;

	return_val = (*game->weapon_anim[weapon])(&game->surfs, dest, &game->anim, sound);
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
		dst.x = surfs->perspective_view->w - surfs->hud_faces_rect.w;
		dst.y = 0;
		if ((SDL_GetTicks() - surfs->hud_timer) >= 1000)
		{
			surfs->hud_timer = SDL_GetTicks();
			if (surfs->hud_faces_rect.x < surfs->hud_faces_rect.w * 2)
				surfs->hud_faces_rect.x += surfs->hud_faces_rect.w;
			else
				surfs->hud_faces_rect.x = 0;
		}
		if ((SDL_BlitSurface(surfs->hud_faces_surf, &surfs->hud_faces_rect, surfs->perspective_view, &dst)) != 0)
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

int game_loop(t_doom *doom)
{
	t_game		*game;
	t_sdlmain	*sdlmain;
	Uint32		startclock = 0;
	int			itt = 0;
	t_view		view;

	game = &(doom->game);
	sdlmain = &(doom->sdlmain);

	SDL_WarpMouseInWindow(sdlmain->win, sdlmain->win_surf->w / 2, sdlmain->win_surf->h / 2);
	startclock = SDL_GetTicks();
	while (doom->state == GAME_STATE)
	{
		ft_bzero(game->surfs.perspective_view->pixels, game->surfs.perspective_view->h * game->surfs.perspective_view->pitch);
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
			if (handle_events(doom) != 0)
				break ;
		handle_keys(game, SDL_GetKeyboardState(NULL), &sdlmain->sound);
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
		if (blit_weapon(game, game->surfs.perspective_view, 0, &sdlmain->sound) != 0)
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
	return (0);
}
