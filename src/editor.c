/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/09 18:13:19 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int is_convex(t_vec a, t_vec b, t_vec c, t_editor *editor)
{
	if (editor->point <= 3)
		return (1);
	int i;
	
	i = 0;
	int safe_sign = editor->sign_pos;
	double cross_product;
	cross_product = cross_product_len(a, b, c);
	if (cross_product < 0)
		safe_sign = 0;
	else if (cross_product > 0)
		safe_sign = 1;
	if (safe_sign != editor->sign_pos)
	{
		ft_printf("NOT CONVEX\n");
		editor->sector.num_walls--;
		editor->point--; // maybe not the best way to do this
		return (0);
	}
	ft_printf("CONVEX\n");
	return (1);
}

int round_num(double num, int offset)
{
	double result;

	result = num / offset;
	return (num < 0 ? result - 0.5 : result + 0.5);
}

int create_surfaces_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	if ((editor->editor_surf = SDL_CreateRGBSurface(0, sdlmain->win_surf->w / 1.79, sdlmain->win_surf->h, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", SDL_GetError()));
	if ((editor->options_surf = SDL_CreateRGBSurface(0, sdlmain->win_surf->w - (sdlmain->win_surf->w / 1.79), sdlmain->win_surf->h / 2, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", SDL_GetError())); // remove bug color from game shining through editor on right side
	if ((editor->instruct_surf = SDL_CreateRGBSurface(0, sdlmain->win_surf->w - (sdlmain->win_surf->w / 1.79), sdlmain->win_surf->h - (sdlmain->win_surf->h / 2), 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %s\n", SDL_GetError()));
	assign_sdlrect(&editor->editor_rect, create_vec(0, 0), create_vec(sdlmain->win_surf->w / 1.79, sdlmain->win_surf->h));
	assign_sdlrect(&editor->options_rect, create_vec(sdlmain->win_surf->w / 1.79, 0), create_vec(sdlmain->win_surf->w - (sdlmain->win_surf->w / 1.79), sdlmain->win_surf->h / 2));
	assign_sdlrect(&editor->instruct_rect, create_vec(sdlmain->win_surf->w / 1.79, sdlmain->win_surf->h / 2), create_vec(sdlmain->win_surf->w - (sdlmain->win_surf->w / 1.79), sdlmain->win_surf->h - (sdlmain->win_surf->h / 2)));
	return(0);
}

int	init_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	int i = 0;

	if (create_surfaces_editor(editor, sdlmain) != 0)
		return (1);
	if (init_editor_menu(editor) != 0)
		return (1);
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
	editor->sector.num_walls = 0;
	editor->num_sectors = 0;
	editor->start_sector_reached = 1;
	editor->color_change = 0;
	editor->sign_pos = 0;
	editor->point = 0;
	editor->A.x = 0;
	editor->A.y = 0;
	editor->B.x = 0;
	editor->B.y = 0;
	editor->C.x = 0;
	editor->C.y = 0;
	return (0);
}

void	fill_area(SDL_Surface *surf, int x, int y, int j)
{
	int color;

	color = 0XB11226;
	fill_pix(surf, x + j, y, color);
	fill_pix(surf, x, y + j, color);
	fill_pix(surf, x + j, y - j, color);
	fill_pix(surf, x + j, y + j, color);
}

void	draw_lines(t_editor *editor, SDL_Surface *editor_surf)
{
	int i = 0;

	editor->mouse_pos.x = editor->mouse_pos.x * editor->offset;
	editor->mouse_pos.y = editor->mouse_pos.y * editor->offset;
	if (editor->clicked != 0 && editor->sector.num_walls <= MAX_WALLS && editor->walls[0].start_wall.x != 0)
	{
		draw_line(editor->mouse_pos, vecdb_to_vec(editor->walls[editor->sector.num_walls].start_wall), editor_surf, 0x00ABFF);
		int j = 0;
		while (j < 4)
		{
			fill_area(editor_surf, editor->walls[0].start_wall.x, editor->walls[0].start_wall.y, j);
			fill_area(editor_surf, editor->walls[0].start_wall.x, editor->walls[0].start_wall.y, -j);
			j++;
		}
	}
	while (i < editor->sector.num_walls && editor->sector.num_walls <= MAX_WALLS)
	{
		if (i % 2 == 0)
			draw_line(vecdb_to_vec(editor->walls[i].end_wall), vecdb_to_vec(editor->walls[i].start_wall), editor_surf, 0x00ABFF);
		else
			draw_line(vecdb_to_vec(editor->walls[i].end_wall), vecdb_to_vec(editor->walls[i].start_wall), editor_surf, 0xABABFF);
		i++;
		int j = 0;
		while (j < 4)
		{
			fill_area(editor_surf, editor->walls[i].start_wall.x, editor->walls[i].start_wall.y, j);
			fill_area(editor_surf, editor->walls[i].start_wall.x, editor->walls[i].start_wall.y, -j);
			j++;
		}
	}
}

void	save_sectors(t_editor *editor)
{
	if ((editor->start_sector.x == editor->walls[editor->sector.num_walls].end_wall.x) && (editor->start_sector.y == editor->walls[editor->sector.num_walls].end_wall.y))
	{
		editor->clicked = 0;
		editor->start_sector_reached = 1;
		editor->num_sectors++;
		editor->point = 0;
	}
}

void	draw_editor(SDL_Surface *editor_surf, t_editor *editor)
{
	int y;
	int x;
	int i;

	y = 0;
	i = 0;
	while (y < NBPOINTSROW * editor->offset)
	{
		y += editor->offset;
		x = 0;
		while (x < NBPOINTSROW * editor->offset)
		{
			x += editor->offset;
			fill_pix(editor_surf, x, y, 0x606060);
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

int	editor_events(t_doom *doom)
{
	t_editor *editor;
	t_sdlmain *sdlmain;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	check_quit(&doom->sdlmain.event, &doom->state);
	if (sdlmain->event.type == SDL_KEYDOWN)
	{
		if (sdlmain->event.key.repeat == 0)
			check_menu(&doom->sdlmain.event, &doom->state, &doom->menu.previous_state, EDITOR_STATE);
        if (sdlmain->event.key.keysym.sym == SDLK_u && editor->sector.num_walls > 0)
			editor->sector.num_walls--;
	}
	if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT && editor->mouse_pos.x < editor->editor_surf->h - editor->offset)
		{
			/* if (editor->point > 3)
			{
				is_convex(editor->A, editor->B, editor->C, editor);
			} */
			if (editor->clicked == 1/*  && is_convex(editor->A, editor->B, editor->C, editor) */)
			{
				if (editor->C.x == 0 && editor->point == 1)
				{
					editor->B.x = editor->mouse_pos.x;
					editor->B.y = editor->mouse_pos.y;
				}
				else
				{
					if (editor->C.x != 0)
					{
						editor->A.x = editor->B.x;
						editor->A.y = editor->B.y;
						editor->B.x = editor->C.x;
						editor->B.y = editor->C.y;
					}
				}
				if (editor->point != 1)
				{
					editor->C.x = editor->mouse_pos.x;
					editor->C.y = editor->mouse_pos.y;
					if (editor->point == 3)
					{
						ft_printf("HOLA\n");
						double cross_product = cross_product_len(editor->A, editor->B, editor->C);
						ft_printf("croos %f\n", cross_product);
						if (cross_product < 0)
							editor->sign_pos = 0;
						else if (cross_product > 0)
							editor->sign_pos = 1;
					}
				}
				editor->point++;
				editor->walls[editor->sector.num_walls].end_wall.x = editor->mouse_pos.x;
				editor->walls[editor->sector.num_walls].end_wall.y = editor->mouse_pos.y;
				editor->walls[editor->sector.num_walls + 1].start_wall.x = editor->walls[editor->sector.num_walls].end_wall.x;
				editor->walls[editor->sector.num_walls + 1].start_wall.y = editor->walls[editor->sector.num_walls].end_wall.y;
				save_sectors(editor);
				editor->sector.num_walls++;
			}
			else
			{
				if (editor->start_sector_reached == 1)
				{
					editor->walls[editor->sector.num_walls].start_wall.x = editor->mouse_pos.x;
					editor->walls[editor->sector.num_walls].start_wall.y = editor->mouse_pos.y;
					editor->start_sector.x = editor->mouse_pos.x;
					editor->start_sector.y = editor->mouse_pos.y;
					editor->clicked = 1;
					editor->start_sector_reached = 0;
					editor->A.x = editor->mouse_pos.x;
					editor->A.y = editor->mouse_pos.y;
					editor->point++;
				}
			}
			ft_printf("Ax = %d, Ay = %d, Bx = %d, By = %d, Cx = %d, Cy = %d\n", editor->A.x, editor->A.y, editor->B.x, editor->B.y, editor->C.x, editor->C.y);
			ft_printf("point %d\n", editor->point);
			ft_printf("sign: %d\n", editor->sign_pos);
		}
	}
	if (doom->state != EDITOR_STATE)
		return (1);
	return (0);
}

int	blit_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	if ((SDL_BlitSurface(editor->editor_menu.title, NULL, editor->options_surf, &editor->editor_menu.title_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_BlitSurface(editor->editor_menu.title_inst, NULL, editor->instruct_surf, &editor->editor_menu.title_inst_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_BlitScaled(editor->editor_surf, NULL, sdlmain->win_surf, &editor->editor_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if ((SDL_BlitScaled(editor->options_surf, NULL, sdlmain->win_surf, &editor->options_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if ((SDL_BlitScaled(editor->instruct_surf, NULL, sdlmain->win_surf, &editor->instruct_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError()));
	return (0);
}

int editor_loop(t_doom *doom)
{
	t_editor *editor;
	t_sdlmain *sdlmain;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	SDL_WarpMouseInWindow(sdlmain->win, doom->sdlmain.win_surf->w / 2, doom->sdlmain.win_surf->h / 2);
    if (editor->editor_surf->w < editor->editor_surf->h)
        editor->offset = editor->editor_surf->w / NBPOINTSROW;
    else        
        editor->offset = editor->editor_surf->h / NBPOINTSROW;
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
		ft_bzero(editor->options_surf->pixels, editor->options_surf->h * editor->options_surf->pitch);
		ft_bzero(editor->instruct_surf->pixels, editor->instruct_surf->h * editor->instruct_surf->pitch);
		draw_editor(editor->editor_surf, editor);
		draw_border(editor->editor_surf, 0xB12211);
		draw_border(editor->options_surf, 0xB12211);
		draw_border(editor->instruct_surf, 0xB12211);
		draw_lines(editor, editor->editor_surf);
		if (blit_editor(editor, sdlmain) != 0)
			return (1);
	}
	return (0);
}
