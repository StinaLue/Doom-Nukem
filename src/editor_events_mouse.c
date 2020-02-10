/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:00:02 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/10 14:30:31 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void	mouse_collide_textures(t_options_menu *menu, t_vec mouse_pos, \
											Uint8 button)
{
	int i;

	i = 0;
	while (i < NBTEXTURES)
	{
		if (is_mouse_collide(mouse_pos, menu->text_rect[i]) \
							&& button == SDL_BUTTON_LEFT)
		{
			if (menu->activ_tex != i)
				menu->bord_color_text[menu->activ_tex] = COLOR_CHOOSE;
			menu->bord_color_text[i] = COLOR_PRESSED;
			menu->activ_tex = i;
		}
		else
		{
			if (is_mouse_collide(mouse_pos, menu->text_rect[i]) \
								&& i != menu->activ_tex)
				menu->bord_color_text[i] = COLOR_HOVER;
			else if (!is_mouse_collide(mouse_pos, menu->text_rect[i]) \
								&& i != menu->activ_tex)
				menu->bord_color_text[i] = COLOR_CHOOSE;
		}
		i++;
	}
}

void	update_weapon_choice(t_sdlmain *sdlmain, \
			t_options_menu *menu, int weapon, t_vec mouse)
{
	if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
	{
		if (is_mouse_collide(mouse, menu->scaled_weapon_rect[0]))
		{
			if (weapon == 1 || weapon == 3)
				menu->bord_color_weapon[0] = COLOR_CHOOSE;
			else if (weapon == 0 || weapon == 2)
				menu->bord_color_weapon[0] = COLOR_PRESSED;
			menu->activ_weapon += (weapon == 0 || weapon == 2) ? 1 : -1;
		}
		else if (is_mouse_collide(mouse, menu->scaled_weapon_rect[1]))
		{
			if (weapon == 2 || weapon == 3)
				menu->bord_color_weapon[1] = COLOR_CHOOSE;
			else if (weapon == 0 || weapon == 1)
				menu->bord_color_weapon[1] = COLOR_PRESSED;
			menu->activ_weapon += (weapon == 0 || weapon == 1) ? 2 : -2;
		}
	}
	else if ((weapon == 0 || weapon == 2) \
			&& is_mouse_collide(mouse, menu->scaled_weapon_rect[0]))
		menu->bord_color_weapon[0] = COLOR_HOVER;
	else if ((weapon == 0 || weapon == 1) \
			&& is_mouse_collide(mouse, menu->scaled_weapon_rect[1]))
		menu->bord_color_weapon[1] = COLOR_HOVER;
}

void	mouse_collide_load(t_sdlmain *sdlmain, \
			t_options_menu *menu, t_editor *editor)
{
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[2]) \
			&& sdlmain->event.button.button == SDL_BUTTON_LEFT \
			&& editor->start_sector_reached == 1)
	{
		if (editor->selected_sector != NULL)
			remove_highlight_sector(editor->selected_sector);
		editor->selected_sector = NULL;
		free_map(&editor->edit_map);
		if (read_map(menu->file_name, &editor->edit_map) != 0)
		{
			ft_dprintf(STDERR_FILENO, "error in read map\n");
			free_map(&editor->edit_map);
		}
		else
		{
			ft_printf("%{g}s was properly loaded 😉\n", editor->edit_map.name);
			editor->opt_menu.activ_music = editor->edit_map.which_music;
			editor->opt_menu.activ_weapon = editor->edit_map.weapon_choice;
		}
	}
}

void	mouse_collide_music(t_sdlmain *sdlmain, t_options_menu *menu)
{
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[3]))
	{
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			menu->bord_hover_color_opt[3] = COLOR_PRESSED;
			menu->bord_hover_color_opt[4] = COLOR_CHOOSE;
			menu->activ_music = 0;
		}
		else if (menu->activ_music != 0)
			menu->bord_hover_color_opt[3] = COLOR_HOVER;
	}
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[4]))
	{
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			menu->bord_hover_color_opt[4] = COLOR_PRESSED;
			menu->bord_hover_color_opt[3] = COLOR_CHOOSE;
			menu->activ_music = 1;
		}
		else if (menu->activ_music != 1)
			menu->bord_hover_color_opt[4] = COLOR_HOVER;
	}
}

void	mouse_collide_height(t_sdlmain *sdlmain, t_editor *editor, \
								t_options_menu *menu)
{
	int i;

	i = 0;
	while (i < 2)
	{
		if (is_mouse_collide(sdlmain->mouse_pos, \
				editor->opt_menu.height_rect[i]) \
				&& editor->opt_menu.activ_height[i] != 1)
			editor->opt_menu.bord_color_height[i] = COLOR_HOVER;
		i++;
	}
	if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[0]) \
			&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
	{
		menu->activ_height[0] = 1;
		menu->activ_height[1] = 0;
		menu->bord_color_height[0] = COLOR_PRESSED;
	}
	if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[1]) \
			&& sdlmain->event.button.button == SDL_BUTTON_LEFT)
	{
		menu->activ_height[1] = 1;
		menu->activ_height[0] = 0;
		menu->bord_color_height[1] = COLOR_PRESSED;
	}
}

void	mouse_collide_save(t_editor *editor)
{
	if (editor->selected_sector != NULL)
		remove_highlight_sector(editor->selected_sector);
	editor->selected_sector = NULL;
	if (editor->edit_map.sector_head == NULL)
	{
		ft_dprintf(STDERR_FILENO, "no sector in map to save\n");
		return ;
	}
	if (ft_strlen(editor->edit_map.name) <= 6)
	{
		ft_dprintf(STDERR_FILENO, "wrong map name to save\n");
		return ;
	}
	if (editor->edit_map.player_spawn.x == -1 \
		&& editor->edit_map.player_spawn.y == -1)
		editor->edit_map.player_spawn = \
		vecdb_to_vec(editor->edit_map.sector_head->sector_center);
	if (write_map(&editor->edit_map) != 0)
		ft_dprintf(STDERR_FILENO, "error in write map\n");
	else
		ft_printf("%{g}s was properly written 😉\n", \
				editor->edit_map.name);
}

void	mouse_collide_input(t_sdlmain *sdlmain, \
							t_options_menu *menu, Uint8 button)
{
	if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[0]) \
				&& button == SDL_BUTTON_LEFT)
	{
		menu->bord_hover_color_opt[0] = COLOR_PRESSED;
		menu->typing_filename = 1;
	}
}

void	mouse_in_options(t_editor *editor, t_sdlmain *sdlmain, \
							t_options_menu *menu, Uint8 button)
{
	int i;

	i = 0;
	if (is_mouse_collide(sdlmain->mouse_pos, editor->options_rect))
	{
		sdlmain->mouse_pos.x -= editor->editor_rect.w;
		mouse_collide_textures(&editor->opt_menu, sdlmain->mouse_pos, button);
		while (i < 3)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[i]))
				menu->bord_hover_color_opt[i] = COLOR_HOVER;
			i++;
		}
		mouse_collide_input(sdlmain, &editor->opt_menu, button);
		if (is_mouse_collide(sdlmain->mouse_pos, menu->hover_opt_rect[1]) \
			&& button == SDL_BUTTON_LEFT && editor->start_sector_reached == 1)
			mouse_collide_save(editor);
		mouse_collide_music(sdlmain, &editor->opt_menu);
		update_weapon_choice(sdlmain, menu, menu->activ_weapon, \
							sdlmain->mouse_pos);
		mouse_collide_load(sdlmain, menu, editor);
		mouse_collide_height(sdlmain, editor, &editor->opt_menu);
	}
}

void	check_finished_sect(t_editor *editor, t_sector_node *sector)
{
	if ((editor->start_sector.x == editor->wall_tmp.end.x) \
		&& (editor->start_sector.y == editor->wall_tmp.end.y))
	{
		if (check_convex_sector(sector) != 1)
		{
			delete_sector_by_address(&editor->edit_map.sector_head, sector);
			sector = NULL;
			editor->show_convex_alert = 1;
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

void	event_editor_surf(t_vec mouse, t_editor *editor, t_wall_node *wall)
{
	if (start_wall_exists(wall) && !(mouse.x == wall->end.x \
				&& mouse.y == wall->end.y))
	{
		wall->end = vec_to_vecdb(multvec(mouse, MAPMULTIPLIER));
		wall->tex_index = editor->opt_menu.activ_tex;
		copy_wall_node(&editor->current_sector->wall_head, wall);
		editor->current_sector->wall_num++;
		wall->start = wall->end;
		check_finished_sect(editor, editor->current_sector);
	}
	else
	{
		if (editor->start_sector_reached == 1)
		{
			add_sector_node(&editor->edit_map.sector_head);
			editor->start_sector = multvec(mouse, MAPMULTIPLIER);
			wall->start = vec_to_vecdb(multvec(mouse, MAPMULTIPLIER));
			wall->end = vec_to_vecdb(multvec(mouse, MAPMULTIPLIER));
			editor->start_sector_reached = 0;
		}
	}
	editor->current_sector = get_last_sector(editor->edit_map.sector_head);
}

void	highlight_sector(t_sector_node *selected_sector)
{
	t_wall_node *current_wall;

	if (selected_sector == NULL)
		return ;
	current_wall = selected_sector->wall_head;
	while (current_wall != NULL)
	{
		current_wall->color = current_wall->type_color;
		current_wall->type_color = 0xFFFFFF;
		current_wall = current_wall->next;
	}
}

void	remove_highlight_sector(t_sector_node *sector)
{
	t_wall_node *current_wall;

	if (sector == NULL)
		return ;
	current_wall = sector->wall_head;
	while (current_wall != NULL)
	{
		current_wall->type_color = current_wall->color;
		current_wall->color = 0xFFFFFF;
		current_wall = current_wall->next;
	}
}

void	mouse_click_right(t_editor *editor, t_sdlmain *sdlmain)
{
	t_sector_node	*tmp_sector;
	t_vec			tmp_mouse;

	tmp_mouse = sdlmain->mouse_pos;
	tmp_sector = editor->selected_sector;
	tmp_mouse = multvec(tmp_mouse, MAPMULTIPLIER);
	if (editor->start_sector_reached == 1)
		editor->selected_sector = \
		get_sector_by_pos(editor->edit_map.sector_head, \
							vec_to_vecdb(tmp_mouse));
	if (tmp_sector != NULL && tmp_sector != editor->selected_sector)
		remove_highlight_sector(tmp_sector);
	if (tmp_sector != editor->selected_sector)
		highlight_sector(editor->selected_sector);
	if (editor->selected_sector != NULL)
	{
		editor->opt_menu.height_floor = editor->selected_sector->floor_height;
		editor->opt_menu.height_ceiling = \
			editor->selected_sector->ceiling_height;
	}
	set_height(&editor->opt_menu, editor->opt_surf);
}

void	base_color_rect_options(t_options_menu *menu)
{
	if (menu->activ_height[0] != 1)
		menu->bord_color_height[0] = COLOR_CHOOSE;
	if (menu->activ_height[1] != 1)
		menu->bord_color_height[1] = COLOR_CHOOSE;
	menu->bord_hover_color_opt[0] = COLOR_CHOOSE;
	menu->bord_hover_color_opt[1] = COLOR_CHOOSE;
	menu->bord_hover_color_opt[2] = COLOR_CHOOSE;
	if (menu->activ_music != 0)
		menu->bord_hover_color_opt[3] = COLOR_CHOOSE;
	if (menu->activ_music != 1)
		menu->bord_hover_color_opt[4] = COLOR_CHOOSE;
	if (menu->activ_weapon == 0 || menu->activ_weapon == 2)
		menu->bord_color_weapon[0] = COLOR_CHOOSE;
	if (menu->activ_weapon == 0 || menu->activ_weapon == 1)
		menu->bord_color_weapon[1] = COLOR_CHOOSE;
}

void	event_mouse(t_editor *editor, t_sdlmain *sdlmain)
{
	Uint8 button;

	button = sdlmain->event.button.button;
	editor->loading_success = 0;
	if (button == SDL_BUTTON_LEFT \
		&& sdlmain->mouse_pos.x <= NBPOINTSROW \
		&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
		event_editor_surf(sdlmain->mouse_pos, editor, &editor->wall_tmp);
	if (button == SDL_BUTTON_RIGHT && sdlmain->mouse_pos.x <= NBPOINTSROW \
		&& sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_click_right(editor, sdlmain);
	}
	base_color_rect_options(&editor->opt_menu);
	SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
	mouse_in_options(editor, sdlmain, &editor->opt_menu, button);
}
