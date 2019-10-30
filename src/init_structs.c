/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/30 13:44:18 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

#include <pthread.h>

void	init_sdl_struct(t_sdl *sdl)
{
	sdl->win = NULL;
	sdl->surf = NULL;
}

void	init_ttf_struct(t_ttf *ttf)
{
	ttf->font = NULL;
	ttf->surf_message = NULL;
	ttf->fps = NULL;
}

void	init_data_struct(t_data *data, char *title)
{
	data->quit = 0;
	data->img_ptr = NULL;
	fill_map(data->map_ptr, title, &(data->map_height), &(data->map_width));
	verify_bordermap(data->map_ptr, title, data->map_height, data->map_width);
}

void	init_player_struct(t_player *player, int map[MAX_MAP][MAX_MAP],
							int map_width, int map_height)
{
	find_player_pos(player, map, map_width, map_height);
	player->x_dir = -1;
	player->y_dir = 0;
	player->fov_x = 0;
	player->fov_y = 0.9;
	player->up_and_down = 0;
	player->crouch = 0;
}

void	init_raycast_struct(t_raycast *raycast, double x, double y)
{
	raycast->pos_x = x;
	raycast->pos_y = y;
}
