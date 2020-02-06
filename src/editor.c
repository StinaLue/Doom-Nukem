/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 17:17:41 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

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
	i = 0;
	while (i < NBTEXTURES)
	{
		editor->opt_menu.bord_color_text[i] = COLOR_NORMAL;
		i++;
	}
	i = 0;
	editor->opt_menu.bord_color_text[0] = COLOR_PRESSED;
	editor->opt_menu.bord_hover_color_opt[0] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[1] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[2] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[3] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[4] = COLOR_CHOOSE;
	editor->opt_menu.bord_color_opt[0] = COLOR_CHOOSE;
	editor->opt_menu.bord_color_opt[1] = COLOR_CHOOSE;
	editor->opt_menu.bord_color_weapon[0] = COLOR_NORMAL;
	editor->opt_menu.bord_color_weapon[1] = COLOR_NORMAL;
}

int	init_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	int i;

	i = 0;

	editor->edit_map.player_spawn.x = -1;
	editor->edit_map.player_spawn.y = -1;

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
	editor->wall_tmp.wall_type = 0;
	editor->start_sector_reached = 1;
	editor->show_convex_alert = 0;
	editor->show_loading_alert = 0;
	editor->loading_success = 0;
	init_colors(editor);
	return (0);
}

int	reset_init_editor(t_editor *editor, t_sdlmain *sdlmain)
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
	tmp_wall.x = wall->start.x / MAPMULTIPLIER * editor->offset;
	tmp_wall.y = wall->start.y / MAPMULTIPLIER * editor->offset;
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

void	draw_lines(t_editor *editor, SDL_Surface *editor_surf, t_sdlmain *sdlmain)
{
	int				i;
	t_sector_node	*tmp_sect;
	t_wall_node		*tmp_wall;

	i = 0;
    t_vecdb tmptest;
    t_vecdb tempstart;
	if (editor->edit_map.sector_head == NULL)
		return ;
	tmp_sect = editor->edit_map.sector_head;
    tmptest = editor->wall_tmp.end;
        tmptest.x /= MAPMULTIPLIER;
        tmptest.y /= MAPMULTIPLIER;
	if (editor->start_sector_reached == 0)
		draw_line(multvec(sdlmain->mouse_pos, editor->offset),
			multvec(vecdb_to_vec(tmptest), editor->offset), editor_surf, editor->wall_tmp.type_color);
	fill_area(editor_surf, &editor->wall_tmp, editor);
	while (tmp_sect != NULL)
	{
		tmp_wall = tmp_sect->wall_head;
		while (tmp_wall != NULL)
		{
			fill_area(editor_surf, tmp_wall, editor);
				tmptest = tmp_wall->end;
				tempstart = tmp_wall->start;
				tmptest.x /= MAPMULTIPLIER;
				tmptest.y /= MAPMULTIPLIER;
				tempstart.x /= MAPMULTIPLIER;
				tempstart.y /= MAPMULTIPLIER;
			draw_line(multvec(vecdb_to_vec(tmptest), editor->offset),
				multvec(vecdb_to_vec(tempstart), editor->offset), editor_surf, tmp_wall->type_color);
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

int	editor_loop(t_doom *doom)
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
	while (doom->state == EDITOR_STATE)
	{
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if (editor_events(doom) != 0)
				break ;
		SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
		assign_sdlrect(&editor->mouse_rect, create_vec(sdlmain->mouse_pos.x \
						- 15, sdlmain->mouse_pos.y - 15), create_vec(15, 15));
		if (NBPOINTSROW * editor->offset < editor->editor_surf->h)
			offset_border = editor->editor_surf->h \
						- NBPOINTSROW * editor->offset;
		sdlmain->mouse_pos.x = round_num(sdlmain->mouse_pos.x, editor->offset);
		sdlmain->mouse_pos.y = round_num(sdlmain->mouse_pos.y, editor->offset);
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
		draw_lines(editor, editor->editor_surf, sdlmain);
		editor->player_face_surf = doom->game.surfs.hud_faces_surf;
		editor->player_face_rec.x = doom->game.surfs.hud_faces_rect.x;
		editor->player_face_rec.y = doom->game.surfs.hud_faces_rect.y;
		editor->player_face_rec.h = doom->game.surfs.hud_faces_rect.h;
		editor->player_face_rec.w = doom->game.surfs.hud_faces_rect.w;
		if (blit_editor(editor, sdlmain) != 0)
			return (1);
	}
	return (0);
}
