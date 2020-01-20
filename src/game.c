/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:46:18 by afonck            #+#    #+#             */
/*   Updated: 2020/01/21 00:40:51 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

int blit_katana(t_gamesurfs *gamesurfs, SDL_Surface *dest, int *anim)
{
	if (*anim == 1)
	{
		if (gamesurfs->current_frame == 0 && gamesurfs->anim_timer == 0)
			gamesurfs->anim_timer = SDL_GetTicks();
		if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->katana[gamesurfs->current_frame], dest, NULL) != 0)
			return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
		if ((SDL_GetTicks() - gamesurfs->anim_timer) >= 100)
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
		if (SDL_BlitScaled(gamesurfs->weapons, &gamesurfs->katana[2], dest, NULL) != 0)
			return (error_return("SDL_BlitScaled error: %s\n", SDL_GetError()));
		gamesurfs->anim_timer = 0;
	}
	
	return (0);
}

static int (*p[4])(t_gamesurfs *gamesurfs, SDL_Surface *dest, int *anim);

int	blit_weapon(t_gamesurfs *gamesurfs, SDL_Surface *dest, int weapon, int *anim)
{
	int return_val;

	return_val = (*p[weapon])(gamesurfs, dest, anim);
	return (return_val);
}

int game_loop(t_doom *doom)
{
	t_game *game;
	t_sdlmain *sdlmain;
	Uint32 startclock = 0;
	int itt = 0;

	game = &(doom->game);
	sdlmain = &(doom->sdlmain);

	SDL_WarpMouseInWindow(sdlmain->win, sdlmain->win_surf->w / 2, sdlmain->win_surf->h / 2);
	startclock = SDL_GetTicks();
	p[0] = blit_katana;
	while (doom->state == GAME_STATE)
	{
		ft_bzero(game->surfs.perspective_view->pixels, game->surfs.perspective_view->h * game->surfs.perspective_view->pitch);
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
			if (handle_events(doom) != 0)
				break ;
		handle_keys(game, SDL_GetKeyboardState(NULL));
		if (game->data.hud_flags & COLORFLAG)
			game->surfs.perspective_view->userdata = "yescolor";
		else
			game->surfs.perspective_view->userdata = "nocolor";
		draw_perspective_view(game->surfs.perspective_view, &game->player, doom->wall_textures);
		if (blit_weapon(&game->surfs, game->surfs.perspective_view, 0, &game->anim) != 0)
			return (error_return("Blit weapon error\n", NULL));
		//if ((SDL_BlitScaled(game->surfs.weapons, &game->surfs.katana[(int)((float)SDL_GetTicks() / 400) % 4], game->surfs.perspective_view, NULL)) != 0)
		//	printf("%s\n", SDL_GetError());
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
