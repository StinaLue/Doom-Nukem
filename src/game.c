/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:46:18 by afonck            #+#    #+#             */
/*   Updated: 2020/01/17 16:59:05 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

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
		handle_keys(game, SDL_GetKeyboardState(NULL));
		if (game->data.hud_flags & COLORFLAG)
			game->surfs.perspective_view->userdata = "yescolor";
		else
			game->surfs.perspective_view->userdata = "nocolor";

		//print sector
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

		if ((SDL_BlitScaled(game->surfs.weapons, &game->surfs.katana[(int)((float)SDL_GetTicks() / 400) % 4], game->surfs.perspective_view, NULL)) != 0)
			printf("%s\n", SDL_GetError());
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
