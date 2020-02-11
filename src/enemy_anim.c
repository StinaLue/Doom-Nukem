/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:27:13 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 21:36:09 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		enemy_walking_anim(t_enemy *enemy)
{
	enemy->clip_tex.y = enemy->current_frame * enemy->clip_tex.h;
	if (enemy->current_frame == 0 && enemy->anim_timer == 0)
		enemy->anim_timer = SDL_GetTicks();
	if (enemy->current_frame == 0 && enemy->anim_timer == 0)
		enemy->anim_timer = SDL_GetTicks();
	if ((SDL_GetTicks() - enemy->anim_timer) >= 150)
	{
		enemy->current_frame++;
		enemy->anim_timer = SDL_GetTicks();
	}
	if (enemy->current_frame >= 4)
	{
		enemy->current_frame = 0;
		enemy->clip_tex.y = 0;
		enemy->state = 0;
	}
}

void		enemy_attack_anim(t_enemy *enemy)
{
	enemy->clip_tex.y = enemy->clip_tex.h * (enemy->current_frame + 4);
	if (enemy->current_frame == 0 && enemy->anim_timer == 0)
		enemy->anim_timer = SDL_GetTicks();
	if ((SDL_GetTicks() - enemy->anim_timer) >= 250)
	{
		enemy->current_frame++;
		enemy->anim_timer = SDL_GetTicks();
	}
	if (enemy->current_frame >= 3)
	{
		enemy->current_frame = 0;
		enemy->clip_tex.y = 0;
		enemy->state = 0;
	}
}

void		enemy_die_anim(t_enemy *enemy, t_enemy_info *enemy_info)
{
	if (enemy_info->which_enemy == 0)
		enemy->clip_tex.y = enemy->clip_tex.h * 8;
	else if (enemy_info->which_enemy == 1)
		enemy->clip_tex.y = enemy->clip_tex.h * 9;
	enemy->clip_tex.x = enemy->clip_tex.w * enemy->current_frame;
	if (enemy->current_frame == 0 && enemy->anim_timer == 0)
		enemy->anim_timer = SDL_GetTicks();
	if ((SDL_GetTicks() - enemy->anim_timer) >= 150)
	{
		enemy->current_frame++;
		enemy->anim_timer = SDL_GetTicks();
	}
	if (enemy->current_frame >= 7)
		enemy->state = 3;
}

void		enemy_dead_rect(t_enemy *enemy)
{
	enemy->clip_tex.y = enemy->clip_tex.h * 8;
	enemy->clip_tex.x = enemy->clip_tex.w * 6;
}

SDL_Rect	find_srcrect_enemy(t_enemy *enemy, t_enemy_info *enemy_info)
{
	if (enemy->state == 1 && enemy->health > 0)
		enemy_walking_anim(enemy);
	else if (enemy->state == 2 && enemy->health > 0)
		enemy_attack_anim(enemy);
	else if (enemy->state == 2 && enemy->health <= 0)
		enemy_die_anim(enemy, enemy_info);
	else if (enemy->state == 3)
		enemy_dead_rect(enemy);
	else
		enemy->anim_timer = 0;
	return (enemy->clip_tex);
}
