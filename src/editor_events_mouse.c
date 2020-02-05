/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:00:02 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/05 19:57:15 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

void change_size(t_editor *editor, t_sdlmain *sdlmain)
{
	if (editor->selected_sector != NULL)
	{
		editor->opt_menu.height_floor = editor->selected_sector->floor_height;
		editor->opt_menu.height_ceiling = editor->selected_sector->ceiling_height;
		if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[1]) && sdlmain->event.wheel.y > 0 && editor->opt_menu.height_floor > 0)
		{
			editor->opt_menu.height_floor--; // makes floor lower
			editor->selected_sector->floor_height--;
		}
		else if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[1]) && sdlmain->event.wheel.y < 0 && editor->opt_menu.height_floor < 49 && editor->opt_menu.height_floor < editor->opt_menu.height_ceiling - 1)
		{
			editor->opt_menu.height_floor++;
			editor->selected_sector->floor_height++;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[0]) && sdlmain->event.wheel.y < 0 && editor->opt_menu.height_ceiling < 50)
		{
			editor->opt_menu.height_ceiling++;
			editor->selected_sector->ceiling_height++;
		}
		else if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[0]) && sdlmain->event.wheel.y > 0 && editor->opt_menu.height_ceiling > 1 && editor->opt_menu.height_floor < 49 && editor->opt_menu.height_ceiling > editor->opt_menu.height_floor + 1)
		{
			editor->opt_menu.height_ceiling--;
			editor->selected_sector->ceiling_height--;
		}
		//editor->opt_menu.height_floor = editor->selected_sector->floor_height;
		//editor->opt_menu.height_ceiling = editor->selected_sector->ceiling_height;
		set_height(editor);
	}
}

void	set_border_color(t_editor *editor, t_vec mouse_pos)
{
	int i;

	i = 0;
	while (i < NBTEXTURES)
	{
		if (is_mouse_collide(mouse_pos, editor->opt_menu.text_rect[i]))
		{
			if (editor->opt_menu.activ_tex != i)
				editor->opt_menu.bord_color_text[editor->opt_menu.activ_tex] = COLOR_NORMAL;
			editor->opt_menu.bord_color_text[i] = COLOR_PRESSED;
			editor->opt_menu.activ_tex = i;
		}
		i++;
	}
	i = 0;
	//editor->opt_menu.bord_color_opt = COLOR_PRESSED;
}

void mouse_in_options(t_editor *editor, t_sdlmain *sdlmain)
{
	int i;

	i = 0;
	if (is_mouse_collide(sdlmain->mouse_pos, editor->options_rect))
	{
		sdlmain->mouse_pos.x -= editor->editor_rect.w;
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			set_border_color(editor, sdlmain->mouse_pos);
			//special_case_height(editor);
		}
		while (i < NBTEXTURES)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.text_rect[i]) && i != editor->opt_menu.activ_tex)
				editor->opt_menu.bord_color_text[i] = COLOR_HOVER;
			else if (!is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.text_rect[i]) && i != editor->opt_menu.activ_tex)
				editor->opt_menu.bord_color_text[i] = COLOR_NORMAL;
			i++;
		}
		i = 0;
		while (i < 2)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.height_rect[i]))
				editor->opt_menu.bord_color_opt[i] = COLOR_PRESSED;
			i++;
		}
		i = 0;
		while (i < NBHOVEROPTIONS)
		{
			if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.hover_options_rect[i]))
				editor->opt_menu.bord_hover_color_opt[i] = COLOR_PRESSED;
			i++;
		}

		if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.hover_options_rect[0]) && sdlmain->event.button.button == SDL_BUTTON_LEFT/*  && i != editor->opt_menu.activ_tex */)
		{
			editor->opt_menu.typing_filename = 1;
			//editor->opt_menu.bord_color_opt[1] = COLOR_HOVER;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.hover_options_rect[1]) && sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			if (editor->selected_sector != NULL)
				remove_highlight_sector(editor->selected_sector);
			editor->selected_sector = NULL;
			printf("saved\n"); // SAVE MAP
			if (editor->edit_map.sector_head == NULL)
			{
				ft_printf("no sector in map to save\n");
				return ;
			}
			if (ft_strlen(editor->edit_map.name) <= 5)
			{
				ft_printf("wrong map name to save\n");
				return ;
			}
			//scanf("%s", editor->edit_map.name);
			//read(0, editor->edit_map.name, 15);
			if (editor->edit_map.player_spawn.x == -1 && editor->edit_map.player_spawn.y == -1)
				editor->edit_map.player_spawn = vecdb_to_vec(editor->edit_map.sector_head->sector_center);
			//set_sectors_clockwise(editor->edit_map.sector_head);
			if (write_map(&editor->edit_map) != 0)
				printf("error in write map\n");
			//editor->opt_menu.typing_filename = 1;
			//editor->opt_menu.bord_color_text[i] = COLOR_HOVER;
		}
		if (is_mouse_collide(sdlmain->mouse_pos, editor->opt_menu.hover_options_rect[2]) && sdlmain->event.button.button == SDL_BUTTON_LEFT)
		{
			if (editor->selected_sector != NULL)
				remove_highlight_sector(editor->selected_sector);
			editor->selected_sector = NULL;
			printf("loaded\n"); // LOAD MAP
			free_map(&editor->edit_map);
			if (read_map(editor->opt_menu.file_name, &editor->edit_map))
				printf("error in read map\n");
			//editor->opt_menu.typing_filename = 1;
			//editor->opt_menu.bord_color_text[i] = COLOR_HOVER;
		}
	}
}

void	check_finished_sect(t_editor *editor)
{
	if ((editor->start_sector.x == editor->wall_tmp.end.x) \
		&& (editor->start_sector.y == editor->wall_tmp.end.y))
	{
		if (check_convex_sector(editor->current_sector) != 1)
		{
			delete_sector_by_address(&editor->edit_map.sector_head, editor->current_sector);
			editor->current_sector = NULL;
			editor->show_convex_alert = 1;
		}
		else
		{
			editor->show_convex_alert = 0;
			set_sector_position(editor->current_sector);
			if (check_clockwise_sector(editor->current_sector) == 0)
				flip_walls(editor->current_sector);
			editor->current_sector->floor_height = editor->opt_menu.height_floor;
			editor->current_sector->ceiling_height = editor->opt_menu.height_ceiling;
			editor->edit_map.num_sectors++;
		}
		editor->wall_tmp.start.x = -1;
		editor->wall_tmp.start.y = -1;
		editor->start_sector_reached = 1;
	}
}
int	start_wall_exists(t_wall_node *wall)
{
	if (wall->start.x > 0 && wall->start.y > 0)
		return (1);
	return (0);
}

void	event_editor_surf(t_vec mouse, t_editor *editor)
{
	if (start_wall_exists(&editor->wall_tmp) \
		&& !(mouse.x == editor->wall_tmp.end.x \
		&& mouse.y == editor->wall_tmp.end.y))
	{
		editor->wall_tmp.end.x = mouse.x * MAPMULTIPLIER;// * editor->offset;
		editor->wall_tmp.end.y = mouse.y * MAPMULTIPLIER;// * editor->offset;
		editor->wall_tmp.tex_index = editor->opt_menu.activ_tex;
		editor->current_sector = get_last_sector(editor->edit_map.sector_head);
		copy_wall_node(&editor->current_sector->wall_head, &editor->wall_tmp);
		editor->current_sector->wall_num++;
		editor->wall_tmp.start.x = editor->wall_tmp.end.x;
		editor->wall_tmp.start.y = editor->wall_tmp.end.y;
		check_finished_sect(editor);
	}
	else
	{
		if (editor->start_sector_reached == 1)
		{
			//if (editor->current_sector != NULL)
			//	set_sector_position(editor->current_sector);
			add_sector_node(&editor->edit_map.sector_head);
			//set_vec_values(&mouse, &editor->start_sector);
			editor->start_sector.x = mouse.x * MAPMULTIPLIER;// * editor->offset;
			editor->start_sector.y = mouse.y * MAPMULTIPLIER;// * editor->offset;
			editor->wall_tmp.start.x = mouse.x * MAPMULTIPLIER;// * editor->offset; // set_vec_values can be used if wall_tmp.start is int
			editor->wall_tmp.start.y = mouse.y * MAPMULTIPLIER;// * editor->offset;
			editor->wall_tmp.end.x = mouse.x * MAPMULTIPLIER;// * editor->offset;
			editor->wall_tmp.end.y = mouse.y * MAPMULTIPLIER;// * editor->offset;
			editor->start_sector_reached = 0;
		}
	}
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

void 	mouse_click_right(t_editor *editor, t_sdlmain *sdlmain)
{
	t_sector_node *tmp_sector = editor->selected_sector;
    t_vec tmp_mouse = sdlmain->mouse_pos;
    tmp_mouse.x = tmp_mouse.x * MAPMULTIPLIER/*  * editor->offset */;
    tmp_mouse.y = tmp_mouse.y * MAPMULTIPLIER/*  * editor->offset */; 
	//editor->selected_sector = get_sector_by_pos(editor->current_sector, vec_to_vecdb(tmp_mouse));
	if (editor->start_sector_reached == 1)
    	editor->selected_sector = get_sector_by_pos(editor->edit_map.sector_head, vec_to_vecdb(tmp_mouse));
	//highlight_sector(selected_sector);
	//printf("mouse x %d, mouse y %d\n", tmp_mouse.x, tmp_mouse.y);
	//editor->selected_sector = get_sector_by_pos(editor->edit_map.sector_head, vec_to_vecdb(multvec(sdlmain->mouse_pos, editor->offset)));
	
	if (tmp_sector != NULL && tmp_sector != editor->selected_sector)
		remove_highlight_sector(tmp_sector);
	if (tmp_sector != editor->selected_sector)
		highlight_sector(editor->selected_sector);
	//printf("%p\n", editor->selected_sector);
	// select "set_height"
	if (editor->selected_sector != NULL)
	{
		editor->opt_menu.height_floor = editor->selected_sector->floor_height;
		editor->opt_menu.height_ceiling = editor->selected_sector->ceiling_height;
	}
	set_height(editor);
	//check_convex_sector(editor->edit_map.sector_head);
}

void event_mouse(t_editor *editor, t_sdlmain *sdlmain)
{
	if (sdlmain->event.button.button == SDL_BUTTON_LEFT && sdlmain->mouse_pos.x <= NBPOINTSROW && sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
		event_editor_surf(sdlmain->mouse_pos, editor);
	if (sdlmain->event.button.button == SDL_BUTTON_RIGHT && sdlmain->mouse_pos.x <= NBPOINTSROW && sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
	{
		mouse_click_right(editor, sdlmain);
	}
	editor->opt_menu.bord_color_opt[0] = COLOR_CHOOSE;
	editor->opt_menu.bord_color_opt[1] = COLOR_CHOOSE;

	editor->opt_menu.bord_hover_color_opt[0] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[1] = COLOR_CHOOSE;
	editor->opt_menu.bord_hover_color_opt[2] = COLOR_CHOOSE;
	SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
	mouse_in_options(editor, sdlmain);
	if (sdlmain->event.type == SDL_MOUSEWHEEL)
		change_size(editor, sdlmain);
}