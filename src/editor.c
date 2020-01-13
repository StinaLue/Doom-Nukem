/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/13 01:50:19 by afonck           ###   ########.fr       */
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
    //editor->mouse_pos.x = 0;
    //editor->mouse_pos.y = 0;
	/* editor->walls[0].start_wall.x = 0;
	editor->walls[0].start_wall.y = 0;
	editor->walls[0].end_wall.x = 0;
	editor->walls[0].end_wall.y = 0;
	editor->sector.num_walls = 0;
	editor->num_sectors = 0;*/
	editor->start_sector_reached = 1;
	editor->color_change = 0;
	/* editor->sign_pos = 0;
	editor->point = 0;
	editor->A.x = 0;
	editor->A.y = 0;
	editor->B.x = 0;
	editor->B.y = 0;
	editor->C.x = 0;
	editor->C.y = 0; */	
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

void	draw_lines(t_editor *editor, SDL_Surface *editor_surf, t_sdlmain *sdlmain)
{
	int i = 0;

	sdlmain->mouse_pos.x = sdlmain->mouse_pos.x * editor->offset;
	sdlmain->mouse_pos.y = sdlmain->mouse_pos.y * editor->offset;
	if (editor->clicked != 0/* && editor->sector.num_walls <= MAX_WALLS && editor->walls[0].start_wall.x != 0*//* && editor->edit_map.sector_head->wall_head->start_wall.x != -1*/)
	{
		//draw_line(sdlmain->mouse_pos, vecdb_to_vec(editor->walls[editor->sector.num_walls].start_wall), editor_surf, 0x00ABFF);
		t_sector_node *tmpsect = get_last_sector_node(editor->edit_map.sector_head);
		t_wall_node		*tmpwall = get_last_wall_node(tmpsect->wall_head);
		draw_line(sdlmain->mouse_pos, vecdb_to_vec(tmpwall->end_wall), editor_surf, 0x00ABFF);
		/* 
		int j = 0;
		while (j < 4)
		{
			fill_area(editor_surf, editor->walls[0].start_wall.x, editor->walls[0].start_wall.y, j);
			fill_area(editor_surf, editor->walls[0].start_wall.x, editor->walls[0].start_wall.y, -j);
			j++;
		}*/
	}
	//while (i < editor->sector.num_walls && editor->sector.num_walls <= MAX_WALLS)
	t_sector_node *tmp_sect = editor->edit_map.sector_head;
	while (tmp_sect != NULL)
	{
		t_wall_node *tmp_wall = tmp_sect->wall_head;
		while (tmp_wall != NULL)
		{
			if (i % 2 == 0)
				draw_line(vecdb_to_vec(tmp_wall->end_wall), vecdb_to_vec(tmp_wall->start_wall), editor_surf, 0x00ABFF);
				//draw_line(vecdb_to_vec(editor->walls[i].end_wall), vecdb_to_vec(editor->walls[i].start_wall), editor_surf, 0x00ABFF);
			else
				draw_line(vecdb_to_vec(tmp_wall->end_wall), vecdb_to_vec(tmp_wall->start_wall), editor_surf, 0xABABFF);
				//draw_line(vecdb_to_vec(editor->walls[i].end_wall), vecdb_to_vec(editor->walls[i].start_wall), editor_surf, 0xABABFF);
			i++;
			/*
			int j = 0;
			while (j < 4)
			{
				//fill_area(editor_surf, editor->walls[i].start_wall.x, editor->walls[i].start_wall.y, j);
				//fill_area(editor_surf, editor->walls[i].start_wall.x, editor->walls[i].start_wall.y, -j);
				j++;
			}*/
			tmp_wall = tmp_wall->next;
		}
		tmp_sect = tmp_sect->next;
	}
}

void	check_finished_sect(t_editor *editor)//save_sectors(t_editor *editor)
{
	if ((editor->start_sector.x == editor->wall_tmp.end_wall.x) && (editor->start_sector.y == editor->wall_tmp.end_wall.y))
	{
		editor->clicked = 0;
		editor->start_sector_reached = 1;
		editor->num_sectors++;
		//editor->point = 0;
	}
}

void	draw_editor(SDL_Surface *editor_surf, t_editor *editor, t_sdlmain *sdlmain)
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
    if (sdlmain->mouse_pos.y == 0)
        sdlmain->mouse_pos.y = 1;
    if (sdlmain->mouse_pos.x == 0)
        sdlmain->mouse_pos.x = 1;
    sdlmain->mouse_pos.y = y / editor->offset - sdlmain->mouse_pos.y + 1;
	if (sdlmain->mouse_pos.y == 0)
        sdlmain->mouse_pos.y = 1;
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
        if (sdlmain->event.key.keysym.sym == SDLK_u)
			undo_wall(editor->edit_map.sector_head);
			//editor->sector.num_walls--;
	}
    if (sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
    {
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT && sdlmain->mouse_pos.x < editor->editor_surf->h - editor->offset)
		{
			/* if (editor->point > 3)
			{
				is_convex(editor->A, editor->B, editor->C, editor);
			} */
			if (editor->clicked == 1 && sdlmain->mouse_pos.x != editor->wall_tmp.start_wall.x && sdlmain->mouse_pos.y != editor->wall_tmp.start_wall.y/*  && is_convex(editor->A, editor->B, editor->C, editor) */)
			{
				/* if (editor->C.x == 0 && editor->point == 1)
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
				editor->point++; */
				//editor->walls[editor->sector.num_walls].end_wall.x = sdlmain->mouse_pos.x;
				//editor->walls[editor->sector.num_walls].end_wall.y = sdlmain->mouse_pos.y;
				editor->wall_tmp.end_wall.x = sdlmain->mouse_pos.x; // can maybe be put into create_wall_node directly
				editor->wall_tmp.end_wall.y = sdlmain->mouse_pos.y;

				t_sector_node *tmp;
				tmp = get_last_sector_node(editor->edit_map.sector_head);
				//create_wall_node(&editor->edit_map.sector_head->wall_head, editor->wall_tmp.start_wall, editor->wall_tmp.end_wall, 0x00ABFF);
				create_wall_node(&tmp->wall_head, editor->wall_tmp.start_wall, editor->wall_tmp.end_wall, 0x00ABFF);
				editor->wall_tmp.start_wall.x = editor->wall_tmp.end_wall.x;
				editor->wall_tmp.start_wall.y = editor->wall_tmp.end_wall.y;
				check_finished_sect(editor);
				//save_sectors(editor);
				//editor->sector.num_walls++;
			}
			else
			{
				if (editor->start_sector_reached == 1)
				{
					add_sector_node(&editor->edit_map.sector_head);
					//editor->walls[editor->sector.num_walls].start_wall.x = sdlmain->mouse_pos.x;
					//editor->walls[editor->sector.num_walls].start_wall.y = sdlmain->mouse_pos.y;
					editor->start_sector.x = sdlmain->mouse_pos.x;
					editor->start_sector.y = sdlmain->mouse_pos.y;
					editor->wall_tmp.start_wall.x = sdlmain->mouse_pos.x;
					editor->wall_tmp.start_wall.y = sdlmain->mouse_pos.y;
					editor->clicked = 1;
					editor->start_sector_reached = 0;
					//editor->A.x = sdlmain->mouse_pos.x;
					//editor->A.y = sdlmain->mouse_pos.y;
					//editor->point++;
				}
			}
			//ft_printf("Ax = %d, Ay = %d, Bx = %d, By = %d, Cx = %d, Cy = %d\n", editor->A.x, editor->A.y, editor->B.x, editor->B.y, editor->C.x, editor->C.y);
			//ft_printf("point %d\n", editor->point);
			//ft_printf("sign: %d\n", editor->sign_pos);
		}
	}
	if (doom->state != EDITOR_STATE)
		return (1);
	print_map_contents(&editor->edit_map);
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
        SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);

		int offset_border = 0;
		if (NBPOINTSROW * editor->offset < editor->editor_surf->h)
			offset_border = editor->editor_surf->h - NBPOINTSROW * editor->offset;
        sdlmain->mouse_pos.x = round_num(sdlmain->mouse_pos.x, editor->offset);
        sdlmain->mouse_pos.y = round_num(sdlmain->mouse_pos.y - offset_border + editor->offset, editor->offset);
		ft_bzero(editor->editor_surf->pixels, editor->editor_surf->h * editor->editor_surf->pitch);
		ft_bzero(editor->options_surf->pixels, editor->options_surf->h * editor->options_surf->pitch);
		ft_bzero(editor->instruct_surf->pixels, editor->instruct_surf->h * editor->instruct_surf->pitch);
		draw_editor(editor->editor_surf, editor, sdlmain);
		draw_border(editor->editor_surf, 0xB12211);
		draw_border(editor->options_surf, 0xB12211);
		draw_border(editor->instruct_surf, 0xB12211);
		if (editor->edit_map.sector_head != NULL && editor->edit_map.sector_head->wall_head != NULL)
			draw_lines(editor, editor->editor_surf, sdlmain);
		if (blit_editor(editor, sdlmain) != 0)
			return (1);
	}
	return (0);
}
