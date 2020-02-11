/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wall_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:15:31 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 19:15:44 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_wall_textures2(SDL_Surface **text, SDL_Surface *winsurf)
{
	if ((text[4] = load_opti_bmp("assets/wall_textures/granitewall.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", \
									SDL_GetError()));
		if ((text[5] = load_opti_bmp("assets/wall_textures/orangecell.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", \
									SDL_GetError()));
		if ((text[6] = load_opti_bmp("assets/wall_textures/rustwall.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", \
									SDL_GetError()));
		if ((text[7] = load_opti_bmp("assets/wall_textures/sandybrick.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", \
									SDL_GetError()));
		if ((text[8] = load_opti_bmp("assets/wall_textures/slimewall.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", \
									SDL_GetError()));
		return (0);
}

int		init_wall_textures(SDL_Surface **text, SDL_Surface *winsurf)
{
	if ((text[0] = load_opti_bmp("assets/wall_textures/chippedbrick.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load chippedbrick bmp error = %{r}s\n", \
		SDL_GetError()));
		if ((text[1] = load_opti_bmp("assets/wall_textures/grittybrick.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load grittybrick bmp error = %{r}s\n", \
							SDL_GetError()));
		if ((text[2] = load_opti_bmp("assets/wall_textures/mudbrick.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", \
							SDL_GetError()));
		if ((text[3] = load_opti_bmp("assets/wall_textures/bloodwall.bmp", \
							winsurf, 0)) == NULL)
		return (error_return("load mudbrick bmp error = %{r}s\n", \
							SDL_GetError()));
		if (init_wall_textures2(text, winsurf) != 0)
		return (1);
	return (0);
}
