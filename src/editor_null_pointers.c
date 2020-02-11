/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_null_pointers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:11:47 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 11:52:18 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	null_option_pointers(t_editor *editor)
{
	int i;

	i = 0;
	while (i < NBOPTIONS)
	{
		editor->opt_menu.options[i] = NULL;
		i++;
	}
	i = 0;
	while (i < NBHOVEROPTIONS)
	{
		editor->opt_menu.hover_options[i] = NULL;
		i++;
	}
	editor->opt_menu.title = NULL;
	editor->opt_menu.height_surf[0] = NULL;
	editor->opt_menu.height_surf[1] = NULL;
	editor->opt_menu.font = NULL;
	editor->opt_menu.font_title = NULL;
}

void	null_menu_pointers(t_menu *menu)
{
	int i;

	i = 0;
	menu->background = NULL;
	menu->menu_title = NULL;
	while (i < 4)
	{
		menu->options[i] = NULL;
		i++;
	}
}

void	null_editor_pointers(t_editor *editor)
{
	editor->editor_surf = NULL;
	editor->opt_surf = NULL;
	editor->instr_surf = NULL;
	editor->current_sector = NULL;
	editor->current_wall = NULL;
	editor->mouse_surf = NULL;
	editor->alert_convex_surf = NULL;
	editor->alert_loading_surf = NULL;
	editor->loading_success_surf = NULL;
	editor->wall_tmp.wall_type = 0;
	editor->wall_tmp.type_color = 0xFF0000;
	editor->wall_textures = NULL;
	editor->selected_sector = NULL;
	editor->enemy_textures = NULL;
	null_option_pointers(editor);
	null_instr_pointers(editor);
	null_map_pointers(&editor->edit_map);
}
