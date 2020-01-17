/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/17 17:06:34 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

/*
int is_convex(t_vec a, t_vec b, t_vec c, t_editor *editor)
{
	//if (editor->point <= 3)
	//	return (1);
	int i;

	i = 0;
	//int safe_sign = editor->sign_pos;
	double cross_product;
	cross_product = cross_product_len(a, b, c);
	//if (cross_product < 0)
	//	safe_sign = 0;
	//else if (cross_product > 0)
	//	safe_sign = 1;
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
*/

int	round_num(double num, int offset)
{
	double result;

	result = num / offset;
	return (num < 0 ? result - 0.5 : result + 0.5);
}

void	init_colors(t_editor *editor)
{
	int i;

	i = 0;
	editor->color_change = 0;
	editor->opt_menu.activ_text = 0;
	editor->opt_menu.activ_h = 1;
	i = 0;
	while (i < NBTEXTURES)
	{
		editor->opt_menu.bord_color_text[i] = COLOR_NORMAL;
		i++;
	}
	i = 0;
	while (i < NBHEIGHTS)
	{
		editor->opt_menu.bord_color_h[i] = COLOR_NORMAL;
		i++;
	}
	editor->opt_menu.bord_color_text[0] = COLOR_PRESSED;
	editor->opt_menu.bord_color_h[1] = COLOR_PRESSED;
	editor->opt_menu.bord_color_h[4] = COLOR_PRESSED;
}

int	init_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	int i;

	i = 0;
	editor->edit_map.sector_head = NULL;
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
	editor->wall_tmp.start.x = -1;
	editor->wall_tmp.start.y = -1;
	editor->wall_tmp.end.x = -1;
	editor->wall_tmp.end.y = -1;
	editor->start_sector_reached = 1;
	init_colors(editor);
	return (0);
}

void	fill_area2(SDL_Surface *surf, int x, int y, int j)
{
	int color;

	color = 0XB11226;
	fill_pix(surf, x + j, y, color);
	fill_pix(surf, x, y + j, color);
	fill_pix(surf, x + j, y - j, color);
	fill_pix(surf, x + j, y + j, color);
}

void	fill_area(SDL_Surface *surf, t_wall_node *wall, t_editor *editor)
{
	int j;
	int wall_x;
	int wall_y;

	j = 0;
	wall_x = wall->end.x * editor->offset;
	wall_y = wall->end.y * editor->offset;
	while (j < 4)
	{
		fill_area2(surf, wall_x, wall_y, j);
		fill_area2(surf, wall_x, wall_y, -j);
		j++;
	}
}

void	draw_lines(t_editor *editor, SDL_Surface *editor_surf, t_sdlmain *sdlmain)
{
	int				i;
	t_sector_node	*tmp_sect;
	t_wall_node		*tmp_wall;

	i = 0;
	if (editor->edit_map.sector_head == NULL)
		return ;
	tmp_sect = editor->edit_map.sector_head;
	if (editor->start_sector_reached == 0)
	{
		draw_line(mult_vec(sdlmain->mouse_pos, editor->offset),
			mult_vec(vecdb_to_vec(editor->wall_tmp.end), editor->offset), editor_surf, 0x00ABFF);
		fill_area(editor_surf, &editor->wall_tmp, editor);
	}
	while (tmp_sect != NULL)
	{
		tmp_wall = tmp_sect->wall_head;
		while (tmp_wall != NULL)
		{
			fill_area(editor_surf, tmp_wall, editor);
			if (i % 2 == 0)
				draw_line(mult_vec(vecdb_to_vec(tmp_wall->end), editor->offset), mult_vec(vecdb_to_vec(tmp_wall->start), editor->offset), editor_surf, 0x00ABFF);
			else
				draw_line(mult_vec(vecdb_to_vec(tmp_wall->end), editor->offset), mult_vec(vecdb_to_vec(tmp_wall->start), editor->offset), editor_surf, 0xABABFF);
			i++;
			tmp_wall = tmp_wall->next;
		}
		tmp_sect = tmp_sect->next;
	}
}

void	draw_editor(SDL_Surface *editor_surf,
					t_editor *editor, t_sdlmain *sdlmain)
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
	sdlmain->mouse_pos.y = sdlmain->mouse_pos.y == 0 ? 1 : sdlmain->mouse_pos.y;
	sdlmain->mouse_pos.x = sdlmain->mouse_pos.x == 0 ? 1 : sdlmain->mouse_pos.x;
	sdlmain->mouse_pos.y = y / editor->offset - sdlmain->mouse_pos.y + 1;
	sdlmain->mouse_pos.y = sdlmain->mouse_pos.y == 0 ? 1 : sdlmain->mouse_pos.y;
}

int	is_pos_wall(t_wall_node *wall)
{
	if (wall->start.x > 0 && wall->start.y > 0)
	{
		if (wall->end.x > 0 && wall->end.y > 0)
			return (1);
	}
	return (0);
}

void	chosen_texture(t_editor *editor, t_vec mouse)
{
	(void)editor;
	//create rectangle
	assign_sdlrect(&editor->mouse_rect, create_vec(mouse.x - 15, mouse.y - 15), create_vec(15, 15));
}

int	editor_loop(t_doom *doom)
{
	t_editor	*editor;
	t_sdlmain	*sdlmain;
	int			offset_border;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	//SDL_WarpMouseInWindow(sdlmain->win, sdlmain->win_surf->w / 2, sdlmain->win_surf->h / 2);
	if (editor->editor_surf->w < editor->editor_surf->h)
		editor->offset = editor->editor_surf->w / NBPOINTSROW;
	else
		editor->offset = editor->editor_surf->h / NBPOINTSROW;
	while (doom->state == EDITOR_STATE)
	{
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if (editor_events(doom) != 0)
				break ;
		SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
		// add little square here? if in each surface
		chosen_texture(editor, sdlmain->mouse_pos);
		if (NBPOINTSROW * editor->offset < editor->editor_surf->h)
			offset_border = editor->editor_surf->h \
						- NBPOINTSROW * editor->offset;
		sdlmain->mouse_pos.x = round_num(sdlmain->mouse_pos.x, editor->offset);
		sdlmain->mouse_pos.y = round_num(sdlmain->mouse_pos.y - offset_border \
											+ editor->offset, editor->offset);
		ft_bzero(editor->editor_surf->pixels, \
					editor->editor_surf->h * editor->editor_surf->pitch);
		ft_bzero(editor->options_surf->pixels, \
					editor->options_surf->h * editor->options_surf->pitch);
		ft_bzero(editor->instr_surf->pixels, \
					editor->instr_surf->h * editor->instr_surf->pitch);
		draw_editor(editor->editor_surf, editor, sdlmain);
		draw_border(editor->editor_surf, 0xB12211);
		draw_border(editor->options_surf, 0xB12211);
		draw_border(editor->instr_surf, 0xB12211);
		draw_lines(editor, editor->editor_surf, sdlmain);
		if (blit_editor(editor, sdlmain) != 0)
			return (1);
	}
	return (0);
}
