/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/10 20:00:00 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int	init_gamesurfs_struct(t_gamesurfs *gamesurfs)
{
	gamesurfs->fixed_mmap = NULL;
	gamesurfs->rot_mmap = NULL;
	gamesurfs->perspective_mmap = NULL;
	if ((gamesurfs->rot_mmap = SDL_CreateRGBSurface(0, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->fixed_mmap = SDL_CreateRGBSurface(0, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->perspective_mmap = SDL_CreateRGBSurface(0, THIRD_MAP_WIDTH, THIRD_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	return (0);
}

void	init_data_struct(t_data *data)
{
	data->activate = 0;
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
