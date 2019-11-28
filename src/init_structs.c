/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/28 17:46:39 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	init_sdl_struct(t_sdl *sdl)
{
	sdl->win = NULL;
	sdl->win_surf = NULL;
	sdl->fixed_mmap = NULL;
	sdl->rot_mmap = NULL;
}

void	init_data_struct(t_data *data)
{
	data->quit = 0;
	data->hud_flags = 0;
}

void	init_player_struct(t_player *player)
{
	player->pos.x = 70;
	player->pos.y = 70;
	player->angle = 0.0;
	player->view_z = 0;
	player->inertia.x = 0;
	player->inertia.y = 0;
}
