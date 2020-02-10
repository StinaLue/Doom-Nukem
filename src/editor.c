/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/10 17:36:57 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int		round_num(double num, int offset)
{
	double result;

	result = num / (double)offset;
	return (num < 0 ? result - 0.5 : result + 0.5);
}

void	init_colors(t_editor *editor)
{
	int i;

	i = 0;
	editor->color_change = 0;
	i = 0;
	while (i < NBTEXTURES)
	{
		editor->opt_menu.bord_color_text[i] = COLOR_CHOOSE;
		i++;
	}
	i = 0;
	editor->opt_menu.bord_color_text[0] = COLOR_PRESSED;
	editor->opt_menu.bord_hover_color_opt[0] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[1] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[2] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[3] = COLOR_PRESSED;
	editor->opt_menu.bord_hover_color_opt[4] = COLOR_CHOOSE;
	if (editor->opt_menu.activ_height[0] != 1)
		editor->opt_menu.bord_color_height[0] = COLOR_CHOOSE;
	if (editor->opt_menu.activ_height[1] != 1)
		editor->opt_menu.bord_color_height[1] = COLOR_CHOOSE;
	editor->opt_menu.bord_color_weapon[0] = COLOR_CHOOSE;
	editor->opt_menu.bord_color_weapon[1] = COLOR_CHOOSE;
}

int		init_editor2(t_editor *editor, t_sdlmain *sdlmain)
{
	int i;

	i = 0;
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
	reset_vecdb(&editor->wall_tmp.start);
	reset_vecdb(&editor->wall_tmp.end);
	editor->wall_tmp.wall_type = 0;
	editor->start_sector_reached = 1;
	editor->show_convex_alert = 0;
	editor->show_loading_alert = 0;
	editor->loading_success = 0;
	init_colors(editor);
	return (0);
}

int		init_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	reset_vec(&editor->edit_map.player_spawn);
	editor->edit_map.which_music = 0;
	editor->edit_map.sector_head = NULL;
	editor->edit_map.num_enemies = 0;
	editor->opt_menu.height_ceiling = 40;
	editor->opt_menu.height_floor = 2;
	editor->opt_menu.activ_tex = 0;
	editor->opt_menu.typing_filename = 0;
	ft_bzero(editor->opt_menu.file_name, 16);
	ft_strncpy(editor->opt_menu.file_name, ".doom_", 6);
	editor->current_sector = NULL;
	editor->current_wall = NULL;
	editor->selected_sector = NULL;
	if (init_editor2(editor, sdlmain) != 0)
		return (1);
	return (0);
}

int		reset_init_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	int i;

	i = 0;
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
	return (0);
}

void	fill_area(SDL_Surface *surf, t_wall_node *wall, t_editor *editor)
{
	t_vec	tmp_wall;
	int		j;
	int		color;
	int		i;

	color = (editor->start_sector.x == wall->start.x \
			&& editor->start_sector.y == wall->start.y) ? 0X00FF00 : 0XB11226;
	j = 0;
	tmp_wall.x = wall->start.x / SIZEMAP * editor->offset;
	tmp_wall.y = wall->start.y / SIZEMAP * editor->offset;
	while (j < 4)
	{
		i = 0;
		while (i < 2)
		{
			fill_pix(surf, tmp_wall.x + j, tmp_wall.y, color);
			fill_pix(surf, tmp_wall.x, tmp_wall.y + j, color);
			fill_pix(surf, tmp_wall.x + j, tmp_wall.y - j, color);
			fill_pix(surf, tmp_wall.x + j, tmp_wall.y + j, color);
			j = -j;
			i++;
		}
		j++;
	}
}

void	draw_lines(t_editor *editor, SDL_Surface *editor_surf, \
					t_vec mouse)
{
	t_sector_node	*tmp_sect;
	t_wall_node		*tmp_wall;

	if (editor->edit_map.sector_head == NULL)
		return ;
	tmp_sect = editor->edit_map.sector_head;
	if (editor->start_sector_reached == 0)
		draw_line(multvec(mouse, editor->offset), \
		multvec(vecdb_to_vec(divvecdb(editor->wall_tmp.end, SIZEMAP)), \
			editor->offset), editor_surf, editor->wall_tmp.type_color);
	fill_area(editor_surf, &editor->wall_tmp, editor);
	while (tmp_sect != NULL)
	{
		tmp_wall = tmp_sect->wall_head;
		while (tmp_wall != NULL)
		{
			fill_area(editor_surf, tmp_wall, editor);
			draw_line(multvec(vecdb_to_vec(divvecdb(tmp_wall->end, SIZEMAP)), \
			editor->offset), multvec(vecdb_to_vec(divvecdb(tmp_wall->start, \
				SIZEMAP)), editor->offset), editor_surf, tmp_wall->type_color);
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

void	prepare_editor(t_sdlmain *sdlmain, t_editor *editor, int offset_border)
{
	assign_sdlrect(&editor->mouse_rect, create_vec(sdlmain->mouse_pos.x \
					- 15, sdlmain->mouse_pos.y - 15), create_vec(15, 15));
	sdlmain->mouse_pos.x = round_num(sdlmain->mouse_pos.x, editor->offset);
	sdlmain->mouse_pos.y = round_num(sdlmain->mouse_pos.y - offset_border \
									+ editor->offset, editor->offset);
	ft_bzero(editor->editor_surf->pixels, \
				editor->editor_surf->h * editor->editor_surf->pitch);
	ft_bzero(editor->opt_surf->pixels, \
				editor->opt_surf->h * editor->opt_surf->pitch);
	ft_bzero(editor->instr_surf->pixels, \
				editor->instr_surf->h * editor->instr_surf->pitch);
	draw_editor(editor->editor_surf, editor, sdlmain);
	draw_border(editor->editor_surf, 0xB12211);
	draw_border(editor->opt_surf, 0xB12211);
	draw_border(editor->instr_surf, 0xB12211);
	draw_lines(editor, editor->editor_surf, sdlmain->mouse_pos);
}

int		editor_loop(t_doom *doom)
{
	t_editor	*editor;
	t_sdlmain	*sdlmain;
	int			offset_border;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	if (editor->editor_surf->w < editor->editor_surf->h)
		editor->offset = editor->editor_surf->w / NBPOINTSROW;
	else
		editor->offset = editor->editor_surf->h / NBPOINTSROW;
	offset_border = editor->editor_surf->h \
			- NBPOINTSROW * editor->offset;
	if (!is_buffer_playing(sdlmain->sound.source[0], sdlmain->sound.buffer[9]))
		play_editor_music(sdlmain, doom);
	while (doom->state == EDITOR_STATE)
	{
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if (editor_events(doom, sdlmain) != 0)
				break ;
		SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
		prepare_editor(sdlmain, editor, offset_border);
		if (blit_editor(editor, sdlmain) != 0)
			return (1);
	}
	return (0);
}
