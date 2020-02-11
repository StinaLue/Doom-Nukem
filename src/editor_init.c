/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:40:43 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 11:54:23 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

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
	editor->opt_menu.bord_hover_color_opt[0] = COLOR_NORMAL;
	editor->opt_menu.bord_hover_color_opt[1] = COLOR_NORMAL;
	editor->opt_menu.bord_hover_color_opt[2] = COLOR_NORMAL;
	editor->opt_menu.bord_hover_color_opt[3] = COLOR_PRESSED;
	editor->opt_menu.bord_hover_color_opt[4] = COLOR_NORMAL;
	if (editor->opt_menu.activ_height[0] != 1)
		editor->opt_menu.bord_color_height[0] = COLOR_NORMAL;
	if (editor->opt_menu.activ_height[1] != 1)
		editor->opt_menu.bord_color_height[1] = COLOR_NORMAL;
	editor->opt_menu.bord_color_weapon[0] = COLOR_NORMAL;
	editor->opt_menu.bord_color_weapon[1] = COLOR_NORMAL;
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
