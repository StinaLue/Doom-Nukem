/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/12/05 16:44:44 by phaydont         ###   ########.fr       */
=======
/*   Updated: 2019/12/05 11:43:57 by afonck           ###   ########.fr       */
>>>>>>> 547d4ba7b5c89d26c9bbe9728f073b7b34da8ff6
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
	data->menu_flag = 0;
	//data->editor_flag = 0;
	data->hud_flags = 0;
}

void	init_player_struct(t_player *player)
{
	player->pos.x = 70;
	player->pos.y = 70;
	player->angle = 0;
	player->view_z = 0;
	player->inertia.x = 0;
	player->inertia.y = 0;
}
