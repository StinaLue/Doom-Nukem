/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_blit_hud.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:05:59 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 14:33:37 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int	update_fps(int *itt, t_gamesurfs *surfs, Uint32 *startclock)
{
	if ((surfs->fps_text = ft_itoa(*itt)) == NULL)
		return (error_return("itoa malloc error\n", NULL));
	if (reset_text(&surfs->fps_font, &surfs->fps, \
				&surfs->fps_color, surfs->fps_text) != 0)
		return (error_return("reset text error\n", NULL));
	ft_memdel((void **)&surfs->fps_text);
	*itt = 0;
	*startclock = SDL_GetTicks();
	return (0);
}

int	blit_fps(t_game *game, int *itt, Uint32 *startclock)
{
	if (game->data.hud_flags & FPS_SHOW)
	{
		if ((SDL_BlitSurface(game->surfs.fps, NULL, \
				game->surfs.perspective_view, &game->surfs.dst_fps_rect)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", \
									SDL_GetError()));
	}
	if (SDL_GetTicks() - *startclock >= 1000 && game->data.hud_flags & FPS_SHOW)
	{
		if (update_fps(itt, &game->surfs, startclock) != 0)
			return (1);
	}
	return (0);
}

int	blit_hud_faces(t_game *game, t_gamesurfs *surfs, SDL_Surface *win)
{
	t_data		*data;
	SDL_Rect	dst;

	data = &game->data;
	if ((data->hud_flags & HEALTH_STATUS))
	{
		surfs->hud_faces_rect.y = \
			player_hurt_anim(game->player.health, &surfs->hud_faces_rect);
		assign_sdlrect(&dst, create_vec(win->w - win->w / 20, 0), \
			create_vec(win->h / 12, win->w / 16));
		if ((SDL_GetTicks() - surfs->hud_timer) >= 1000)
		{
			surfs->hud_timer = SDL_GetTicks();
			if (surfs->hud_faces_rect.x < surfs->hud_faces_rect.w * 2)
				surfs->hud_faces_rect.x += surfs->hud_faces_rect.w;
			else
				surfs->hud_faces_rect.x = 0;
		}
		if ((SDL_BlitScaled(surfs->hud_faces_surf, \
				&surfs->hud_faces_rect, win, &dst)) != 0)
			return (1);
	}
	return (0);
}

int	blit_hud_weapons(t_game *game, t_map *map, t_gamesurfs *surfs)
{
	SDL_Rect	dst[2];
	t_vec		vec[2];
	int			i;

	i = 0;
	vec[0] = create_vec((surfs->perspective_view->w / 20) * 18.5, \
		(surfs->perspective_view->h / 20) * 17.5);
	vec[1] = create_vec((surfs->perspective_view->w / 20) * 17, \
		(surfs->perspective_view->h / 20) * 17.5);
	while (i < 2)
	{
		if (((map->weapon_choice == 1 || map->weapon_choice == 3) && i == 0) \
		|| ((map->weapon_choice == 2 || map->weapon_choice == 3) && i == 1))
		{
			assign_sdlrect(&dst[i], vec[i], create_vec(40, 40));
			if ((SDL_BlitScaled(game->surfs.weapons, \
				&surfs->hud_weapons_rect[i], \
				surfs->perspective_view, &dst[i])) != 0)
				return (1);
			draw_border_options(&dst[i], \
						surfs->hud_weapons_color[i], surfs->perspective_view);
		}
		i++;
	}
	return (0);
}

int	game_blit_hud(t_map *map, t_game *game, int itt, Uint32 startclock)
{
	if ((blit_hud_faces(game, &game->surfs, game->surfs.perspective_view)) == 1)
		return (error_return("error during blit_hud_faces\n", NULL));
	if ((blit_fps(game, &itt, &startclock)) == 1)
		return (error_return("error during blit_fps\n", NULL));
	if ((blit_hud_weapons(game, map, &game->surfs) == 1))
		return (error_return("error during blit_hud_weapons\n", NULL));
	return (0);
}
