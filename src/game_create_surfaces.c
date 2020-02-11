/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_create_surfaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:34:52 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 17:06:44 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	load_game_textures(t_gamesurfs *gamesurfs)
{
	if ((gamesurfs->weapons = load_opti_bmp("assets/weapons/weapons.bmp", \
			gamesurfs->perspective_view, 0xFFFFFF)) == NULL)
		return (error_return("load weapon bmp surf error\n", NULL));
	if ((gamesurfs->hud_faces_surf = load_opti_bmp("assets/hud/hud_faces.bmp", \
			gamesurfs->perspective_view, 0x00FFFF)) == NULL)
		return (error_return("load hud faces bmp surf error\n", NULL));
	if ((gamesurfs->enemy_texture[0] = \
			load_opti_bmp("assets/enemy_sprites/UndeadWarrior.bmp", \
			gamesurfs->perspective_view, 0x00FFFF)) == NULL)
		return (error_return("load UndeadWarrior surf error\n", NULL));
	if ((gamesurfs->enemy_texture[1] = \
			load_opti_bmp("assets/enemy_sprites/Ogre.bmp", \
			gamesurfs->perspective_view, 0x00FFFF)) == NULL)
		return (error_return("load Ogre surf error\n", NULL));
	return (0);
}

int	create_game_surfaces(t_gamesurfs *gamesurfs, t_sdlmain *sdlmain)
{
	if ((gamesurfs->rot_mmap = \
			SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", \
					SDL_GetError()));
		if ((gamesurfs->fixed_mmap = \
			SDL_CreateRGBSurface(0, 102, 102, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", \
					SDL_GetError()));
		if ((gamesurfs->perspective_view = \
			SDL_CreateRGBSurface(0, sdlmain->win_surf->w / 2, \
					sdlmain->win_surf->h / 2, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	return (0);
}
