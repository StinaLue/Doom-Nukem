/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/15 14:27:52 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

#include <pthread.h>

void	init_sdl_struct(t_sdl *sdl)
{
	sdl->win = NULL;
	sdl->ren = NULL;
	sdl->tex = NULL;
}

void	init_ttf_struct(t_ttf *ttf)
{
	ttf->font = NULL;
	ttf->surf_message = NULL;
	ttf->message = NULL;
	ttf->fps = NULL;
}

void    init_data_struct(t_data *data, char *title)
{
        data->quit = 0;
        //ft_memset(data->pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
        data->img_ptr = NULL;
        fill_map(data->map_ptr, title, &(data->map_width), &(data->map_height));
        verify_bordermap(data->map_ptr, title, data->map_width, data->map_height);
}

void    init_player_struct(t_player *player, int map[MAX_MAP][MAX_MAP], int map_width, int map_height)
{
        find_player_pos(player, map, map_width, map_height);
        player->x_dir = 1;
        player->y_dir = 0;
        player->cam_vector_x = 0;
        player->cam_vector_y = 0.66;
        player->up_and_down = 0;
        player->crouch          = 0;
}

void	init_raycast_struct(t_raycast *raycast, double x, double y)
{
	raycast->pos_x = x;
	raycast->pos_y = y;
}
