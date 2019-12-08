/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/08 18:54:57 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int round_num(double num)
{
	double result = num / OFFSET;
	return (num < 0 ? result - 0.5 : result + 0.5); 
}
void	init_editor(t_editor *editor)
{
	int i = 0;
	while (i <= NBPOINTS)
	{
		editor->grid_values[i].x = 0;
		editor->grid_values[i].y = 0;
		i++;
	}
    editor->mouse_pos.x = 0;
    editor->mouse_pos.y = 0;
	editor->walls.start_wall.x = 0;
	editor->walls.start_wall.y = 0;
	editor->walls.end_wall.x = 0;
	editor->walls.end_wall.y = 0;
};

void	draw_lines(int x, int y, t_editor *editor)
{
    //editor->walls.start_wall.x = x;
    //editor->walls.start_wall.y = y;
	printf("x: %d, y: %d, ed.x: %d, ed.y : %d\n", x, y, editor->grid_values[0].x, editor->grid_values[0].y);
}

void	draw_editor(SDL_Surface *editor_surf, t_editor *editor)
{
	int y = 0;
	int x;
	int i = 0;
	while (y < editor_surf->h - OFFSET)
	{
		y += OFFSET;
		x = 0;
		while (x < editor_surf->w - OFFSET)
		{
			x += OFFSET;
			fill_pix(editor_surf, x, y, 0xFFFFFF);
			editor->grid_values[i].x = x / OFFSET;
			editor->grid_values[i].y = y / OFFSET;
			i++;
		}
	}
    if (editor->mouse_pos.y == 0)
        editor->mouse_pos.y = 1;
    if (editor->mouse_pos.x == 0)
        editor->mouse_pos.x = 1;
    editor->mouse_pos.y = y / OFFSET - editor->mouse_pos.y + 1;
	if (editor->mouse_pos.y == 0)
        editor->mouse_pos.y = 1;
}

void editor(SDL_Window **win, SDL_Surface **win_surf, int *editor_flag, const Uint8 *keyboard_state)
{
	SDL_Surface *editor_surf = NULL;
	SDL_Surface *instruct_surf = NULL;
	SDL_Event event;
	t_editor editor;
	(void)keyboard_state;
	init_editor(&editor);
	SDL_WarpMouseInWindow(*win, WIN_W / 2, WIN_H / 2);
	//SDL_Rect editor_rect = {0, WIN_H, 0, WIN_W / 1.5};
	SDL_Rect editor_rect = {0, 0, WIN_W / 1.5, WIN_H};
	SDL_Rect instruct_rect = {WIN_W / 1.5, 0, WIN_W - (WIN_W / 1.5), WIN_H};
	if ((editor_surf = SDL_CreateRGBSurface(0, WIN_W / 1.5, WIN_H, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((instruct_surf = SDL_CreateRGBSurface(0, WIN_W - (WIN_W / 1.5), WIN_H, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	while (*editor_flag == 1)
	{
        SDL_GetMouseState(&editor.mouse_pos.x, &editor.mouse_pos.y);
        editor.mouse_pos.x = round_num(editor.mouse_pos.x);
        editor.mouse_pos.y = round_num(editor.mouse_pos.y);
		//ft_bzero(editor_surf->pixels, editor_surf->h * editor_surf->pitch);
		ft_bzero(instruct_surf->pixels, instruct_surf->h * instruct_surf->pitch);
		draw_editor(editor_surf, &editor);
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
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (editor.clicked == 1)
                    {
                        editor.walls.end_wall.x = editor.mouse_pos.x * OFFSET;
                        editor.walls.end_wall.y = editor.mouse_pos.y * OFFSET;
                        editor.clicked = 0;
                    }
                    else
                    {
                        editor.walls.start_wall.x = editor.mouse_pos.x * OFFSET;
                        editor.walls.start_wall.y = editor.mouse_pos.y * OFFSET;
                        editor.clicked = 1;
                    }
                }
            }
			editor.mouse_pos.x = editor.mouse_pos.x * OFFSET;
			editor.mouse_pos.y = editor.mouse_pos.y * OFFSET;
			//if (editor.walls.end_wall.x != 0)
			//	draw_line(vecdb_to_vec(editor.walls.end_wall), editor.mouse_pos, editor_surf, 0x00ABFF);
			if (editor.walls.end_wall.x != 0 && editor.walls.start_wall.x != 0)
				draw_line(vecdb_to_vec(editor.walls.end_wall), vecdb_to_vec(editor.walls.start_wall), editor_surf, 0x00ABFF);
           /*  if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    editor.clicked = 0;
                    editor.walls.start_wall.x = editor.mouse_pos.x;
                    editor.walls.start_wall.y = editor.mouse_pos.y;
                    printf("x %f, y %f\n", editor.walls.start_wall.x, editor.walls.start_wall.y);
                    printf("this event works\n");
                }
            } */
		}
		//draw_lines(editor.mouse_pos.x, editor.mouse_pos.y, &editor);
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