/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/06 16:37:05 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	init_editor(t_editor *editor)
{
	int i = 0;
	while (i <= NBPOINTS)
	{
		editor->grid_values[i].x = 0;
		editor->grid_values[i].y = 0;
		i++;
	}
};

void	draw_lines(int x, int y, t_editor *editor)
{
	printf("x: %d, y: %d, ed.x: %d, ed.y : %d\n", x, y, editor->grid_values[2890].x, editor->grid_values[2890].y);
}

void	draw_editor(SDL_Surface *editor_surf, double offset, t_editor *editor)
{
	int y = 0;
	int x;
	int i = 0;
	while (y < editor_surf->h - offset)
	{
		y += offset;
		x = 0;
		while (x < editor_surf->w - offset)
		{
			x += offset;
			fill_pix(editor_surf, x, y, 0xFFFFFF);
			editor->grid_values[i].x = x / offset;
			editor->grid_values[i].y = y / offset;
			//printf("current value y %d\n", editor->grid_values[i].y);
			i++;
		}
	}
}

void editor(SDL_Window **win, SDL_Surface **win_surf, int *editor_flag, const Uint8 *keyboard_state)
{
	SDL_Surface *editor_surf = NULL;
	SDL_Surface *instruct_surf = NULL;
	SDL_Event event;
	t_editor editor;
	(void)keyboard_state;
	init_editor(&editor);
	double offset = OFFSET;
	int x = 0;
	int y = 0;
	SDL_WarpMouseInWindow(*win, WIN_W / 2, WIN_H / 2);
	//SDL_ShowCursor(SDL_ENABLE);
	//SDL_Rect editor_rect = {0, WIN_H, 0, WIN_W / 1.5};
	SDL_Rect editor_rect = {0, 0, WIN_W / 1.5, WIN_H};
	SDL_Rect instruct_rect = {WIN_W / 1.5, 0, WIN_W - (WIN_W / 1.5), WIN_H};
	if ((editor_surf = SDL_CreateRGBSurface(0, WIN_W / 1.5, WIN_H, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((instruct_surf = SDL_CreateRGBSurface(0, WIN_W - (WIN_W / 1.5), WIN_H, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	while (*editor_flag == 1)
	{
		//SDL_SetRelativeMouseMode(SDL_TRUE);
    	SDL_GetRelativeMouseState(&x, &y);
		ft_bzero(editor_surf->pixels, editor_surf->h * editor_surf->pitch);
		ft_bzero(instruct_surf->pixels, instruct_surf->h * instruct_surf->pitch);
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_e)
					*editor_flag = 0;
				//if (event.key.keysym.sym == SDLK_UP && offset < 100 / SIZE)
				//	offset++;
				//else if (event.key.keysym.sym == SDLK_DOWN && offset > 20 / SIZE)
				//	offset--;
			}
		}
		draw_editor(editor_surf, offset, &editor);
		//draw_lines(x, y, &editor);
		if ((SDL_BlitScaled(editor_surf, NULL, *win_surf, &editor_rect)) < 0)
			ft_dprintf(STDERR_FILENO, "BlitScale error = %s\n", SDL_GetError());

		if ((SDL_BlitScaled(instruct_surf, NULL, *win_surf, &instruct_rect)) < 0)
			ft_dprintf(STDERR_FILENO, "BlitScale error = %s\n", SDL_GetError());

		if ((SDL_UpdateWindowSurface(*win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n",
								SDL_GetError());
			return ;
		}
	}
}