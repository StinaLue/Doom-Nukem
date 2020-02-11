/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:28:19 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 21:28:45 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	enemy_follow_player(t_enemy *enemy, t_player *player)
{
	if (get_point_distance(enemy->pos, player->pos) > 20)
	{
		enemy->state = 1;
		if (player->pos.x > enemy->pos.x)
			enemy->pos.x += 0.2;
		if (player->pos.y > enemy->pos.y)
			enemy->pos.y += 0.2;
		if (player->pos.x < enemy->pos.x)
			enemy->pos.x -= 0.2;
		if (player->pos.y < enemy->pos.y)
			enemy->pos.y -= 0.2;
	}
}

void	enemy_attack_player(t_enemy *enemy, t_player *player)
{
	enemy->state = 2;
	if (enemy->current_frame == 2 && SDL_GetTicks() - enemy->anim_timer < 100)
		player->health -= 1;
}

void	enemy_action(t_enemy *enemy, t_player *player, int num_enemies)
{
	int i;

	i = 0;
	while (i < num_enemies)
	{
		if (enemy[i].state != 3)
		{
			if (enemy[i].sector == player->sector)
				enemy_follow_player(&enemy[i], player);
			if (get_point_distance(enemy[i].pos, player->pos) <= 25)
				enemy_attack_player(&enemy[i], player);
		}
		i++;
	}
}
