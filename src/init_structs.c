/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:37 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/21 17:57:57 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

SDL_Surface *load_opti_bmp(char *file, SDL_Surface *dst_surf, Uint32 colorkey)
{
	SDL_Surface *opti_surf;
	SDL_Surface *surf;

	opti_surf = NULL;
	surf = NULL;
	if ((surf = load_bmp(file)) == NULL)
		return (NULL);
	if ((opti_surf = SDL_ConvertSurface(surf, dst_surf->format, 0)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "ConvertSurf err = %{r}s\n", SDL_GetError());
		SDL_FreeSurface(surf);
		return (NULL);
	}
	SDL_FreeSurface(surf);
	if (colorkey != 0)
	{
		if ((SDL_SetColorKey(opti_surf, SDL_TRUE, colorkey)) != 0)
		{
			ft_dprintf(STDERR_FILENO, "SetColorKey err = %{r}s\n", SDL_GetError());
			SDL_FreeSurface(opti_surf);
			return (NULL);
		}
	}
	return (opti_surf);
}

int	init_gamesurfs_struct(t_gamesurfs *gamesurfs, t_sdlmain *sdlmain)
{
	gamesurfs->fixed_mmap = NULL;
	gamesurfs->rot_mmap = NULL;
	gamesurfs->perspective_view = NULL;
	gamesurfs->weapons = NULL;
	if ((gamesurfs->rot_mmap = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0)) == NULL) //--> should be a square that can handle the size of a sector
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->fixed_mmap = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0)) == NULL) //--> should be a square that can handle the size of the whole map
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((gamesurfs->perspective_view = SDL_CreateRGBSurface(0, sdlmain->win_surf->w / 4, sdlmain->win_surf->h / 4, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	//if ((gamesurfs->weapons = load_bmp("assets/shadow.bmp")) == NULL)
	if ((gamesurfs->weapons = load_opti_bmp("assets/shadow.bmp", gamesurfs->perspective_view/*sdlmain->win_surf*/, 0x0080FF)) == NULL)
		return (error_return("load weapon bmp surf error\n", NULL));
	if ((gamesurfs->hud_faces_surf = load_opti_bmp("assets/hud/hud_faces.bmp", gamesurfs->perspective_view, 0x00FFFF)) == NULL)
		return (error_return("load hud faces bmp surf error\n", NULL));
	gamesurfs->katana[0] = create_sdlrect(9, 78, 226, 169);
	gamesurfs->katana[1] = create_sdlrect(236, 76, 148, 169);
	gamesurfs->katana[2] = create_sdlrect(391, 47, 239, 200);
	gamesurfs->katana[3] = create_sdlrect(631, 25, 186, 223);
	gamesurfs->hud_faces_rect = create_sdlrect(0, 0, gamesurfs->hud_faces_surf->w / 3, gamesurfs->hud_faces_surf->h / 5);
	gamesurfs->anim_timer = 0;
	gamesurfs->hud_timer = 0;
	gamesurfs->current_frame = 0;
	return (0);
}

void	init_data_struct(t_data *data)
{
	data->hud_flags = 0;
}

void	init_player_struct(t_player *player)
{
	player->sector = NULL;
	player->pos.x = 49;
	player->pos.y = 35;
	player->angle = 0;
	player->view_z = 0;
	player->inertia.x = 0;
	player->inertia.y = 0;
	player->fov.x = 100;
	player->fov.y = 100;
	player->true_fov = 1.5708; //hardcoded 90deg
	player->health = 100;
}
