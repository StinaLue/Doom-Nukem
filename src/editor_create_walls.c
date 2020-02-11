/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_walls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:34:19 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 20:28:30 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	base_color_rect_options(t_options_menu *menu)
{
	if (menu->activ_height[0] != 1)
		menu->bord_color_height[0] = COLOR_NORMAL;
	if (menu->activ_height[1] != 1)
		menu->bord_color_height[1] = COLOR_NORMAL;
	menu->bord_hover_color_opt[0] = COLOR_NORMAL;
	menu->bord_hover_color_opt[1] = COLOR_NORMAL;
	menu->bord_hover_color_opt[2] = COLOR_NORMAL;
	if (menu->activ_music != 0)
		menu->bord_hover_color_opt[3] = COLOR_NORMAL;
	if (menu->activ_music != 1)
		menu->bord_hover_color_opt[4] = COLOR_NORMAL;
	if (menu->activ_weapon == 0 || menu->activ_weapon == 2)
		menu->bord_color_weapon[0] = COLOR_NORMAL;
	if (menu->activ_weapon == 0 || menu->activ_weapon == 1)
		menu->bord_color_weapon[1] = COLOR_NORMAL;
}

void	check_finished_sect(t_editor *editor, t_sector_node *sector)
{
	if ((editor->start_sector.x == editor->wall_tmp.end.x) \
		&& (editor->start_sector.y == editor->wall_tmp.end.y))
	{
		if (check_convex_sector(sector) != 1 || editor->num_points < 3)
		{
			delete_sector_by_address(&editor->edit_map.sector_head, sector);
			sector = NULL;
			editor->show_convex_alert = 1;
			editor->num_points = 0;
		}
		else
		{
			editor->show_convex_alert = 0;
			set_sector_position(sector);
			if (check_clockwise_sector(sector) == 0)
				flip_walls(sector);
			sector->floor_height = editor->opt_menu.height_floor;
			sector->ceiling_height = editor->opt_menu.height_ceiling;
			editor->edit_map.num_sectors++;
			editor->num_points = 0;
		}
		reset_vecdb(&editor->wall_tmp.start);
		editor->start_sector_reached = 1;
	}
}

int		start_wall_exists(t_wall_node *wall)
{
	if (wall->start.x > 0 && wall->start.y > 0)
		return (1);
	return (0);
}

void	create_walls_on_map(t_vec mouse, t_editor *editor, t_wall_node *wall)
{
	if (start_wall_exists(wall) && !(mouse.x == wall->end.x \
				&& mouse.y == wall->end.y))
	{
		wall->end = vec_to_vecdb(multvec(mouse, SIZEMAP));
		wall->tex_index = editor->opt_menu.activ_tex;
		copy_wall_node(&editor->current_sector->wall_head, wall);
		editor->current_sector->wall_num++;
		wall->start = wall->end;
		editor->num_points++;
		check_finished_sect(editor, editor->current_sector);
	}
	else
	{
		if (editor->start_sector_reached == 1)
		{
			add_sector_node(&editor->edit_map.sector_head);
			editor->start_sector = multvec(mouse, SIZEMAP);
			wall->start = vec_to_vecdb(multvec(mouse, SIZEMAP));
			wall->end = vec_to_vecdb(multvec(mouse, SIZEMAP));
			editor->start_sector_reached = 0;
			editor->num_points++;
		}
	}
	editor->current_sector = get_last_sector(editor->edit_map.sector_head);
}
