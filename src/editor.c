/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/13 15:46:52 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int round_num(double num, int offset)
{
	double result = num / offset;
	return (num < 0 ? result - 0.5 : result + 0.5); 
}
int	init_editor(t_editor *editor)
{
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
	editor->mouse_pos.x = editor->mouse_pos.x * editor->offset;
	editor->mouse_pos.y = editor->mouse_pos.y * editor->offset;
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
    if (editor->mouse_pos.y == 0)
        editor->mouse_pos.y = 1;
    if (editor->mouse_pos.x == 0)
        editor->mouse_pos.x = 1;
    editor->mouse_pos.y = y / editor->offset - editor->mouse_pos.y + 1;
	if (editor->mouse_pos.y == 0)
        editor->mouse_pos.y = 1;
}

int		editor_events(t_doom *doom)
{
	t_editor *editor;
	t_sdlmain *sdlmain;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	if (sdlmain->event.type == SDL_KEYDOWN)
	{
		if (sdlmain->event.key.keysym.sym == SDLK_TAB)
		{
			doom->menu.previous_state = EDITOR_STATE;
			doom->state = MENU_STATE;
		}
	}
    if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
    {
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT && editor->mouse_pos.x < editor->editor_surf->h - editor->offset)
		{
			if (editor->clicked == 1)
			{
				editor->walls[editor->num_walls].end_wall.x = editor->mouse_pos.x;
				editor->walls[editor->num_walls].end_wall.y = editor->mouse_pos.y;
				editor->walls[editor->num_walls + 1].start_wall.x = editor->walls[editor->num_walls].end_wall.x;
				editor->walls[editor->num_walls + 1].start_wall.y = editor->walls[editor->num_walls].end_wall.y;
				editor->num_walls++;
			}
			else
			{
				if (editor->num_walls == 0)
				{
					editor->walls[editor->num_walls].start_wall.x = editor->mouse_pos.x;
					editor->walls[editor->num_walls].start_wall.y = editor->mouse_pos.y;
					editor->clicked = 1;
				}
			}
		}
	}
	if (doom->state != EDITOR_STATE)
		return (1);
	return (0);
}

int editor_loop(t_doom *doom)
{
	t_editor *editor;
	t_sdlmain *sdlmain;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	SDL_WarpMouseInWindow(sdlmain->win, WIN_W / 2, WIN_H / 2);
    if (editor->editor_surf->w < editor->editor_surf->h)
        editor->offset = editor->editor_surf->w / NBPOINTSROW;
    else        
        editor->offset = editor->editor_surf->h / NBPOINTSROW;
	//SDL_Rect editor_rect = {0, WIN_H, 0, WIN_W / 1.5};
	while (doom->state == EDITOR_STATE)
	{
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if (editor_events(doom) != 0)
				break ;
        SDL_GetMouseState(&editor->mouse_pos.x, &editor->mouse_pos.y);

		int offset_border = 0;
		if (NBPOINTSROW * editor->offset < editor->editor_surf->h)
			offset_border = editor->editor_surf->h - NBPOINTSROW * editor->offset;
        editor->mouse_pos.x = round_num(editor->mouse_pos.x, editor->offset);
        editor->mouse_pos.y = round_num(editor->mouse_pos.y - offset_border + editor->offset, editor->offset);
		ft_bzero(editor->editor_surf->pixels, editor->editor_surf->h * editor->editor_surf->pitch);
		ft_bzero(editor->instruct_surf->pixels, editor->instruct_surf->h * editor->instruct_surf->pitch);
		draw_editor(editor->editor_surf, editor);
		draw_lines(editor, editor->editor_surf);
		//draw_lines(editor.mouse_pos.x, editor.mouse_pos.y, &editor);
		if ((SDL_BlitScaled(editor->editor_surf, NULL, sdlmain->win_surf, &editor->editor_rect)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));

		if ((SDL_BlitScaled(editor->instruct_surf, NULL, sdlmain->win_surf, &editor->instruct_rect)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));

		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
			return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError()));
	}
	return (0);
}
