/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:08:39 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 22:13:50 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		calculate_screenx(t_vecdb *screenx_and_fov, t_vecdb enem_pos, \
			int widthsurf)
{
	screenx_and_fov->x = enem_pos.x / enem_pos.y;
	screenx_and_fov->x *= screenx_and_fov->y;
	screenx_and_fov->x *= widthsurf / 2;
	screenx_and_fov->x += widthsurf / 2;
}

void		calculate_dst_rect(SDL_Rect *rect, t_vecdb ytopbot, \
			t_enemy *enemy, t_vecdb screenxandfov)
{
	rect->h = ytopbot.y - ytopbot.x;
	rect->w = rect->h * enemy->clip_tex.w / enemy->clip_tex.h;
	rect->x = screenxandfov.x - rect->w * 0.35;
	rect->y = ytopbot.x;
}

SDL_Rect	find_dstrect_enemy(t_enemy *enemy, t_player *player, \
			SDL_Surface *dest)
{
	SDL_Rect	return_rect;
	t_vecdb		transformed_enem_pos;
	t_vecdb		screenx_and_fovratio;
	t_vecdb		topbot;
	t_vecdb		ytopbot;

	topbot.x = (player->posz + player->height) - (30 + enemy->posz);
	topbot.y = (player->posz + player->height) - enemy->posz;
	screenx_and_fovratio.y = player->view.b.y / player->view.b.x;
	transformed_enem_pos = vecdb_diff(enemy->pos, player->pos);
	transformed_enem_pos = rotate2d(transformed_enem_pos, -player->angle);
	calculate_screenx(&screenx_and_fovratio, transformed_enem_pos, dest->w);
	ytopbot.x = topbot.x / transformed_enem_pos.y;
	ytopbot.x *= screenx_and_fovratio.y;
	ytopbot.x *= dest->w / 2;
	ytopbot.x = (dest->h / 2) + ytopbot.x + player->view_z;
	ytopbot.y = topbot.y / transformed_enem_pos.y;
	ytopbot.y *= screenx_and_fovratio.y;
	ytopbot.y *= dest->w / 2;
	ytopbot.y = (dest->h / 2) + ytopbot.y + player->view_z;
	calculate_dst_rect(&return_rect, ytopbot, enemy, screenx_and_fovratio);
	return (return_rect);
}

int			blit_enemies(t_game *game, SDL_Surface *dest, t_map *map)
{
	int			i;
	SDL_Rect	destrect;

	i = 0;
	while (i < map->num_enemies)
	{
		game->enemy[i].clip_tex = find_srcrect_enemy(&game->enemy[i], \
		&map->enemy_info[i]);
		destrect = find_dstrect_enemy(&game->enemy[i], &game->player, dest);
		if ((SDL_BlitScaled(game->enemy[i].texture, \
				&game->enemy[i].clip_tex, dest, &destrect)) != 0)
			return (error_return("SDL_BlitScaled error: %{r}s\n", \
						SDL_GetError()));
			i++;
	}
	return (0);
}
