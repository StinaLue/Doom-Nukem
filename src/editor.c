/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/10 17:43:53 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int round_num(double num)
{
	double result = num / OFFSET;
	return (num < 0 ? result - 0.5 : result + 0.5); 
}
int	init_editor(t_editor *editor)
{
	editor->activate = 0;
	if ((editor->editor_surf = SDL_CreateRGBSurface(0, WIN_W / 1.5, WIN_H, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", SDL_GetError()));
	if ((editor->instruct_surf = SDL_CreateRGBSurface(0, WIN_W - (WIN_W / 1.5), WIN_H, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", SDL_GetError()));
	assign_sdlrect(&editor->editor_rect, create_vec(0, 0), create_vec(WIN_W / 1.5, WIN_H));
	assign_sdlrect(&editor->instruct_rect, create_vec(WIN_W / 1.5, 0), create_vec(WIN_W - (WIN_W / 1.5), WIN_H));
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
	return (0);
};

void	draw_lines(t_editor *editor, SDL_Surface *editor_surf)
{
	editor->mouse_pos.x = editor->mouse_pos.x * OFFSET;
	editor->mouse_pos.y = editor->mouse_pos.y * OFFSET;
	if (editor->clicked != 0 && editor->num_walls <= MAX_WALLS)
		draw_line(editor->mouse_pos, vecdb_to_vec(editor->walls[editor->num_walls].start_wall), editor_surf, 0x00ABFF);
	int i = 0;
	while (i < editor->num_walls && editor->num_walls <= MAX_WALLS)
	{
		draw_line(vecdb_to_vec(editor->walls[i].end_wall), vecdb_to_vec(editor->walls[i].start_wall), editor_surf, 0x00ABFF);
		i++;
	}
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

int		editor_events(t_editor *editor, t_sdlmain *sdlmain)
{
	if (sdlmain->event.type == SDL_KEYDOWN)
	{
		if (sdlmain->event.key.keysym.sym == SDLK_TAB)
			return (MENU_EDITOR);
			//editor->activate = 0;
		//if (event.key.keysym.sym == SDLK_UP && offset < 100 / SIZE)
		//	offset++;
		//else if (event.key.keysym.sym == SDLK_DOWN && offset > 20 / SIZE)
		//	offset--;
	}
    if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
    {
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			if (editor->clicked == 1)
			{
				editor->walls[editor->num_walls].end_wall.x = editor->mouse_pos.x * OFFSET;
				editor->walls[editor->num_walls].end_wall.y = editor->mouse_pos.y * OFFSET;
				editor->walls[editor->num_walls + 1].start_wall.x = editor->walls[editor->num_walls].end_wall.x;
				editor->walls[editor->num_walls + 1].start_wall.y = editor->walls[editor->num_walls].end_wall.y;
				editor->num_walls++;
			}
			else
			{
				if (editor->num_walls == 0)
				{
					editor->walls[editor->num_walls].start_wall.x = editor->mouse_pos.x * OFFSET;
					editor->walls[editor->num_walls].start_wall.y = editor->mouse_pos.y * OFFSET;
					editor->clicked = 1;
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
	while (editor->activate == 1)
	{
		//while (SDL_PollEvent(&sdlmain->event) != 0)
		//	if ((state = editor_events(editor, sdlmain)) != 0)
		//		return (state);
        SDL_GetMouseState(&editor->mouse_pos.x, &editor->mouse_pos.y);
        editor->mouse_pos.x = round_num(editor->mouse_pos.x);
        editor->mouse_pos.y = round_num(editor->mouse_pos.y);
		ft_bzero(editor->editor_surf->pixels, editor->editor_surf->h * editor->editor_surf->pitch);
		ft_bzero(editor->instruct_surf->pixels, editor->instruct_surf->h * editor->instruct_surf->pitch);
		draw_editor(editor->editor_surf, editor);
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if ((state = editor_events(editor, sdlmain)) != CONTINUE_EDITOR)
				return (state);
		draw_lines(editor, editor->editor_surf);
		//draw_lines(editor.mouse_pos.x, editor.mouse_pos.y, &editor);
		if ((SDL_BlitScaled(editor->editor_surf, NULL, sdlmain->win_surf, &editor->editor_rect)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));

		if ((SDL_BlitScaled(editor->instruct_surf, NULL, sdlmain->win_surf, &editor->instruct_rect)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));

		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
			return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError()));
	}
	//editor->activate = 0;
	return (QUIT_EDITOR);
}