/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/12 19:50:12 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int round_num(double num, int offset)
{
	double result = num / offset;
	return (num < 0 ? result - 0.5 : result + 0.5); 
}
void	init_editor(t_editor *editor)
{
	int i = 0;
	while (i < NBPOINTS)
	{
		editor->grid_values[i].x = 0;
		editor->grid_values[i].y = 0;
		i++;
	}
    editor->mouse_pos.x = 0;
    editor->mouse_pos.y = 0;
	editor->walls[0].start_wall.x = 0;
	editor->walls[0].start_wall.y = 0;
	editor->walls[0].end_wall.x = 0;
	editor->walls[0].end_wall.y = 0;
};

void	draw_lines(t_editor editor, SDL_Surface *editor_surf)
{
	editor->mouse_pos.x = editor->mouse_pos.x * editor->offset;
	editor->mouse_pos.y = editor->mouse_pos.y * editor->offset;
	if (editor->clicked != 0 && editor->num_walls <= MAX_WALLS)
		draw_line(editor->mouse_pos, vecdb_to_vec(editor->walls[editor->num_walls].start_wall), editor_surf, 0x00ABFF);
	int i = 0;
	while (i < editor.num_walls && editor.num_walls <= MAX_WALLS)
	{
		draw_line(vecdb_to_vec(editor.walls[i].end_wall), vecdb_to_vec(editor.walls[i].start_wall), editor_surf, 0x00ABFF);
		i++;
	}
}

void	draw_editor(SDL_Surface *editor_surf, t_editor *editor)
{
	int y = 0;
	int x;
	int i = 0;
	while (y < NBPOINTSROW * editor->offset)
	{
		y += editor->offset;
		x = 0;
		while (x < NBPOINTSROW * editor->offset)
		{
			x += editor->offset;
			fill_pix(editor_surf, x, y, 0xFFFFFF);
			editor->grid_values[i].x = x / editor->offset;
			editor->grid_values[i].y = y / editor->offset;
			i++;
		}
	}
    printf ("i = %d\n", i);
    if (editor->mouse_pos.y == 0)
        editor->mouse_pos.y = 1;
    if (editor->mouse_pos.x == 0)
        editor->mouse_pos.x = 1;
    editor->mouse_pos.y = y / editor->offset - editor->mouse_pos.y + 1;
	if (editor->mouse_pos.y == 0)
        editor->mouse_pos.y = 1;
}

void editor(SDL_Window **win, SDL_Surface **win_surf, int *editor_flag)
{
	SDL_Surface *editor_surf = NULL;
	SDL_Surface *instruct_surf = NULL;
	SDL_Event event;
	t_editor editor;
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
		ft_bzero(editor_surf->pixels, editor_surf->h * editor_surf->pitch);
		ft_bzero(instruct_surf->pixels, instruct_surf->h * instruct_surf->pitch);
		draw_editor(editor_surf, &editor);
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_TAB)
					*editor_flag = 0;
				//if (event.key.keysym.sym == SDLK_UP && offset < 100 / SIZE)
				//	offset++;
				//else if (event.key.keysym.sym == SDLK_DOWN && offset > 20 / SIZE)
				//	offset--;
			}
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT && editor.mouse_pos.x * OFFSET < editor_surf->w)
                {
                    if (editor.clicked == 1)
                    {
                        editor.walls[editor.num_walls].end_wall.x = editor.mouse_pos.x * OFFSET;
                        editor.walls[editor.num_walls].end_wall.y = editor.mouse_pos.y * OFFSET;
						editor.walls[editor.num_walls + 1].start_wall.x = editor.walls[editor.num_walls].end_wall.x;
						editor.walls[editor.num_walls + 1].start_wall.y = editor.walls[editor.num_walls].end_wall.y;
						editor.num_walls++;
                    }
                    else
                    {
						if (editor.num_walls == 0)
						{
                        	editor.walls[editor.num_walls].start_wall.x = editor.mouse_pos.x * OFFSET;
                        	editor.walls[editor.num_walls].start_wall.y = editor.mouse_pos.y * OFFSET;
							editor.clicked = 1;
						}
                    }
                }
            }
		}
	}
	return (CONTINUE_EDITOR);
}

int editor_loop(t_editor *editor, t_sdlmain *sdlmain)
{
	SDL_WarpMouseInWindow(sdlmain->win, WIN_W / 2, WIN_H / 2);
	//SDL_Rect editor_rect = {0, WIN_H, 0, WIN_W / 1.5};
	int state;

	state = 0;

    if (editor->editor_surf->w < editor->editor_surf->h)
        editor->offset = editor->editor_surf->w / NBPOINTSROW;
    else        
        editor->offset = editor->editor_surf->h / NBPOINTSROW;
	while (editor->activate == 1)
	{
		//while (SDL_PollEvent(&sdlmain->event) != 0)
		//	if ((state = editor_events(editor, sdlmain)) != 0)
		//		return (state);
        SDL_GetMouseState(&editor->mouse_pos.x, &editor->mouse_pos.y);
        editor->mouse_pos.x = round_num(editor->mouse_pos.x, editor->offset);
        editor->mouse_pos.y = round_num(editor->mouse_pos.y, editor->offset);
		ft_bzero(editor->editor_surf->pixels, editor->editor_surf->h * editor->editor_surf->pitch);
		ft_bzero(editor->instruct_surf->pixels, editor->instruct_surf->h * editor->instruct_surf->pitch);
		draw_editor(editor->editor_surf, editor);
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if ((state = editor_events(editor, sdlmain)) != CONTINUE_EDITOR)
				return (state);
		draw_lines(editor, editor->editor_surf);
		//draw_lines(editor.mouse_pos.x, editor.mouse_pos.y, &editor);
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