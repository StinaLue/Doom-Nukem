/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/13 15:33:28 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int	init_gamesurfs_struct(t_gamesurfs *gamesurfs, t_sdlmain *sdlmain)
{
	gamesurfs->fixed_mmap = NULL;
	gamesurfs->rot_mmap = NULL;
	gamesurfs->perspective_view = NULL;
	if ((gamesurfs->rot_mmap = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0)) == NULL) //--> should be a square that can handle the size of a sector
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->fixed_mmap = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0)) == NULL) //--> should be a square that can handle the size of the whole map
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->perspective_view = SDL_CreateRGBSurface(0, sdlmain->win_surf->w / 4, sdlmain->win_surf->h / 4, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	return (0);
}

void	init_data_struct(t_data *data)
{
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
	player->fov.x = 100;
	player->fov.y = 100;
}
