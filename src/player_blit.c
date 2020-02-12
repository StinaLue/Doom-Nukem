/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_blit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 02:37:29 by afonck            #+#    #+#             */
/*   Updated: 2020/02/12 10:50:10 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void			init_katana(t_gamesurfs *surfs, int anim)
{
	surfs->weapons_rect.x = surfs->current_frame \
					* surfs->weapons_rect.w;
	if (anim == 0)
		surfs->weapons_rect.y = 0;
	else if (anim == 1 && surfs->current_frame > 2)
		surfs->weapons_rect.y = surfs->weapons_rect.h;
}

int				blit_katana(t_gamesurfs *gamesurfs, \
								SDL_Surface *dest, int *anim)
{
	init_katana(gamesurfs, *anim);
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
