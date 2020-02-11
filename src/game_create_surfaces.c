/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_create_surfaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:34:52 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 18:33:30 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "libbmp.h"

void		get_enemysprite_rect(SDL_Rect *rect, int which_enemy, \
									SDL_Surface *sprite_sheet)
{
	rect->x = 0;
	rect->y = 0;
	rect->w = sprite_sheet->w / 8;
	if (which_enemy == 0)
		rect->h = sprite_sheet->h / 9;
	else if (which_enemy == 1)
		rect->h = sprite_sheet->h / 11;
}

SDL_Surface	*load_opti_bmp(char *file, SDL_Surface *dst_surf, Uint32 colorkey)
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
			ft_dprintf(STDERR_FILENO, "SetColorKey err = %{r}s\n", \
						SDL_GetError());
			SDL_FreeSurface(opti_surf);
			return (NULL);
		}
	}
	return (opti_surf);
}

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
	if ((gamesurfs->game_over = load_opti_bmp("assets/game_over.bmp", \
						gamesurfs->perspective_view, 0)) == NULL)
		return (error_return("load game over surf error\n", NULL));
	if ((gamesurfs->victory = load_opti_bmp("assets/victory.bmp", \
						gamesurfs->perspective_view, 0)) == NULL)
		return (error_return("load victory surf error\n", NULL));
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
