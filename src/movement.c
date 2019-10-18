/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:52:08 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/18 12:57:56 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	walk_straight(t_data *data, t_player *player,
					double speed, const Uint8 *keyboard_state)
{
	if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W])
	{
		if (keyboard_state[SDL_SCANCODE_LSHIFT])
			speed += 0.03;
		if ((*data->map_ptr)[(int)(player->y
			+ player->y_dir * speed)][(int)player->x] == 0)
			player->y += player->y_dir * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x
			+ player->x_dir * speed)] == 0)
			player->x += player->x_dir * speed;
	}
	if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S])
	{
		if (keyboard_state[SDL_SCANCODE_LSHIFT])
			speed = 0.08;
		if ((*data->map_ptr)[(int)(player->y
			- player->y_dir * speed)][(int)player->x] == 0)
			player->y -= player->y_dir * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x
			- player->x_dir * speed)] == 0)
			player->x -= player->x_dir * speed;
	}
}

void	walk_sidewards(t_data *data, t_player *player,
						double speed, const Uint8 *keyboard_state)
{
	if (keyboard_state[SDL_SCANCODE_D])
	{
		if ((*data->map_ptr)[(int)(player->y
			+ player->fov_y * speed)][(int)player->x] == 0)
			player->y += player->fov_y * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x
			+ player->fov_x * speed)] == 0)
			player->x += player->fov_x * speed;
	}
	if (keyboard_state[SDL_SCANCODE_A])
	{
		if ((*data->map_ptr)[(int)(player->y
			- player->fov_y * speed)][(int)player->x] == 0)
			player->y -= player->fov_y * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x
			- player->fov_x * speed)] == 0)
			player->x -= player->fov_x * speed;
	}
}

void	crouch_and_view(t_player *player, const Uint8 *keyboard_state, int y)
{
	if (keyboard_state[SDL_SCANCODE_LCTRL])
	{
		if (player->crouch < 20)
			player->crouch = player->crouch + 4;
	}
	if (!keyboard_state[SDL_SCANCODE_LCTRL] && player->crouch > 0)
		player->crouch = player->crouch - 4;
	if (y > 0 && player->up_and_down > MAX_LOOK_DOWN)
		player->up_and_down -= 20;
	if (y < 0 && player->up_and_down < MAX_LOOK_UP)
		player->up_and_down += 20;
}

void	rotate(t_player *player, const Uint8 *keyboard_state, int x, int fps)
{
	double save_x_dir;
	double save_fov_x;
	double rotspeed;

	save_x_dir = player->x_dir;
	save_fov_x = player->fov_x;
	rotspeed = ((keyboard_state[SDL_SCANCODE_LEFT] ||
				keyboard_state[SDL_SCANCODE_Q] || x < 0) ? 5 / (-fps + 0.00001)
				: 5 / (fps + 0.00001));
	if ((keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_Q]
		|| x < 0) || (keyboard_state[SDL_SCANCODE_RIGHT]
		|| keyboard_state[SDL_SCANCODE_E] || x > 0))
	{
		player->x_dir = player->x_dir * cos(rotspeed)
						- player->y_dir * sin(rotspeed);
		player->y_dir = save_x_dir * sin(rotspeed)
						+ player->y_dir * cos(rotspeed);
		player->fov_x = player->fov_x * cos(rotspeed)
						- player->fov_y * sin(rotspeed);
		player->fov_y = save_fov_x * sin(rotspeed)
						+ player->fov_y * cos(rotspeed);
	}
}

void	movement(t_player *player, t_data *data, const Uint8 *keyboard_state)
{
	int		x;
	int		y;
	double	speed;

	x = 0;
	y = 0;
	speed = (player->crouch > 0 ? 5 / (data->fps + 0.00001) : 6 / \
		(data->fps + 0.00001));
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetRelativeMouseState(&x, &y);
	walk_straight(data, player, speed, keyboard_state);
	walk_sidewards(data, player, speed, keyboard_state);
	crouch_and_view(player, keyboard_state, y);
	rotate(player, keyboard_state, x, data->fps);
}
