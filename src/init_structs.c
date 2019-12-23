/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/17 15:30:30 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

int	init_gamesurfs_struct(t_gamesurfs *gamesurfs, t_sdlmain *sdlmain)
{
	gamesurfs->fixed_mmap = NULL;
	gamesurfs->rot_mmap = NULL;
	gamesurfs->perspective_view = NULL;
	gamesurfs->weapons = NULL;
	if ((gamesurfs->rot_mmap = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0)) == NULL) //--> should be a square that can handle the size of a sector
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->fixed_mmap = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0)) == NULL) //--> should be a square that can handle the size of the whole map
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->perspective_view = SDL_CreateRGBSurface(0, sdlmain->win_surf->w / 4, sdlmain->win_surf->h / 4, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->weapons = load_bmp("assets/shadow.bmp")) == NULL)
		return (error_return("load weapon bmp surf error\n", NULL));
	gamesurfs->katana[0] = create_sdlrect(9, 110, 229, 137);
	gamesurfs->katana[1] = create_sdlrect(236, 110, 147, 137);
	gamesurfs->katana[2] = create_sdlrect(391, 45, 232, 202);
	gamesurfs->katana[3] = create_sdlrect(628, 77, 152, 172);
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
	player->true_fov = 1.5708; //hardcoded 90deg
}
