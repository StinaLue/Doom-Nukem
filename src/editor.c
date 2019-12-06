/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/06 13:07:10 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	draw_editor(SDL_Surface *editor_surf, double offset)
{
	int x = 0;
	int y;
	char point_values[NBPOINTS][2]; // saves all the coordinates (x, y) for the whole grid -> only works without zooming for now
	int i = 0;
	while (x < editor_surf->w - offset)
	{
		x += offset;
		y = 0;
		while (y < editor_surf->h - offset)
		{
			y += offset;
			fill_pix(editor_surf, x, y, 0xFFFFFF);
			if (offset == OFFSET)
			{
				point_values[i][0] = x / offset; // need to put this into struct to keep the values even when zooming
				point_values[i][1] = y / offset;
			}
			i++;
		}
	}
	//printf("x: %d\n", point_values[244][0]);
	//printf("y: %d\n", point_values[244][1]);
}

void editor(SDL_Window **win, SDL_Surface **win_surf, int *editor_flag)
{
	SDL_Surface *editor_surf = NULL;
	SDL_Surface *instruct_surf = NULL;
	SDL_Event event;
	double offset = OFFSET;
	//SDL_Rect editor_rect = {0, WIN_HEIGHT, 0, WIN_WIDTH / 1.5};
	SDL_Rect editor_rect = {0, 0, WIN_WIDTH / 1.5, WIN_HEIGHT};
	SDL_Rect instruct_rect = {WIN_WIDTH / 1.5, 0, WIN_WIDTH - (WIN_WIDTH / 1.5), WIN_HEIGHT};
	if ((editor_surf = SDL_CreateRGBSurface(0, WIN_WIDTH / 1.5, WIN_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((instruct_surf = SDL_CreateRGBSurface(0, WIN_WIDTH - (WIN_WIDTH / 1.5), WIN_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	while (*editor_flag == 1)
	{
		ft_bzero(editor_surf->pixels, editor_surf->h * editor_surf->pitch);
		ft_bzero(instruct_surf->pixels, instruct_surf->h * instruct_surf->pitch);
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_e)
					*editor_flag = 0;
				if (event.key.keysym.sym == SDLK_UP && offset < 100 / SIZE)
					offset++;
				else if (event.key.keysym.sym == SDLK_DOWN && offset > 20 / SIZE)
					offset--;
			}
		}
		draw_editor(editor_surf, offset);
		if ((SDL_BlitScaled(editor_surf, NULL, *win_surf, &editor_rect)) < 0)
			ft_dprintf(STDERR_FILENO, "BlitScale error = %s\n", SDL_GetError());

		if ((SDL_BlitScaled(instruct_surf, NULL, *win_surf, &instruct_rect)) < 0)
			ft_dprintf(STDERR_FILENO, "BlitScale error = %s\n", SDL_GetError());

		if ((SDL_UpdateWindowSurface(*win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n",
					   SDL_GetError());
			return;
		}
	}
	*editor_flag = 0;
}