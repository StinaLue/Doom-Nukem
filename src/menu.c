/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:27:36 by afonck            #+#    #+#             */
/*   Updated: 2020/02/07 19:27:50 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int	init_menu_surfs(t_menu *menu, t_sdlmain *sdlmain)
{
	if ((menu->menu_title = TTF_RenderText_Solid(sdlmain->font, "MENU", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError())); // create function ttf error
	if ((menu->options[0] = TTF_RenderText_Solid(sdlmain->font, "editor", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->options[1] = TTF_RenderText_Solid(sdlmain->font, "return to game", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->options[2] = TTF_RenderText_Solid(sdlmain->font, "resize window", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->options[3] = TTF_RenderText_Solid(sdlmain->font, "quit game", menu->text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->background = SDL_CreateRGBSurface(0, sdlmain->win_surf->w - (sdlmain->win_surf->w / 8), sdlmain->win_surf->h - (sdlmain->win_surf->h / 4), 32, 0, 0, 0, 0)) == NULL)
		return (error_return("SDL_CreateRGBSurface error = %s\n", SDL_GetError()));
	return (0);
}

int init_menu(t_menu *menu, t_sdlmain *sdlmain)
{
	menu->current_option = 0;
	menu->prev_option = 0;
	menu->previous_state = QUIT_STATE;
	menu->background = NULL;
	assign_sdlcolor(&menu->text_color, 255, 0, 0);
	assign_sdlrect(&menu->background_rect, create_vec((sdlmain->win_surf->w / 8) / 2, (sdlmain->win_surf->h / 4) / 2), create_vec(0, 0));//MENU_WIDTH, MENU_HEIGHT));
	if (init_menu_surfs(menu, sdlmain) != 0)	
		return (1);
	assign_sdlrect(&menu->menu_title_rect, create_vec((menu->background->w - menu->menu_title->w) / 2, (menu->background->h - menu->menu_title->h) / 8), create_vec(0, 0));
	assign_sdlrect(&menu->options_rects[1], create_vec((menu->background->w - menu->options[1]->w) / 2, (menu->background->h - menu->options[1]->h) / 2), create_vec(0, 0));
	assign_sdlrect(&menu->options_rects[0], create_vec((menu->background->w - menu->options[0]->w) / 2, menu->options_rects[1].y - menu->options[1]->h), create_vec(0, 0));
	assign_sdlrect(&menu->options_rects[2], create_vec((menu->background->w - menu->options[2]->w) / 2, menu->options_rects[1].y + menu->options[1]->h), create_vec(0, 0));
	assign_sdlrect(&menu->options_rects[3], create_vec((menu->background->w - menu->options[3]->w) / 2, menu->options_rects[2].y + menu->options[2]->h), create_vec(0, 0));
	draw_border(menu->background, 0xFFFFFF);

	return (0);
}

void	browse_options(t_sdlmain *sdlmain, t_menu *menu, \
						SDL_Rect *rects, int key_or_mouse)
{
	SDL_GetMouseState(&sdlmain->mouse_pos.x, \
						&sdlmain->mouse_pos.y);
	sdlmain->mouse_pos.x -= menu->background_rect.x;
	sdlmain->mouse_pos.y -= menu->background_rect.y;
	if (key_or_mouse == 1)
	{
		if (sdlmain->event.key.keysym.sym == SDLK_DOWN \
					&& menu->current_option < 4)
			menu->current_option += 1;
		else if (sdlmain->event.key.keysym.sym == SDLK_UP \
					&& menu->current_option > 1)
			menu->current_option -= 1;
	}
	else if (key_or_mouse == 2)
	{
		if (is_mouse_collide(sdlmain->mouse_pos, rects[0]))
			menu->current_option = FIRST_OPTION_SELECT;
		else if (is_mouse_collide(sdlmain->mouse_pos, rects[1]))
			menu->current_option = SECOND_OPTION_SELECT;
		else if (is_mouse_collide(sdlmain->mouse_pos, rects[2]))
			menu->current_option = THIRD_OPTION_SELECT;
		else if (is_mouse_collide(sdlmain->mouse_pos, rects[3]))
			menu->current_option = FOURTH_OPTION_SELECT;
	}
}

void	change_win_dimensions(int *width, int *height)
{
	if (*width == HD_W && *height == HD_H)
	{
		*width = FHD_W;
		*height = FHD_H;
	}
	else if (*width == FHD_W && *height == FHD_H)
	{
		*width = QHD_W;
		*height = QHD_H;
	}
	else if (*width == QHD_W && *height == QHD_H)
	{
		*width = HD_W;
		*height = HD_H;
	}
}

void	launch_option(t_doom *doom)
{
	t_menu		*menu;
	t_sdlmain	*sdlmain;

	menu = &(doom->menu);
	sdlmain = &(doom->sdlmain);
	if (menu->current_option == FIRST_OPTION_SELECT)
		doom->state = EDITOR_STATE;
	else if (menu->current_option == SECOND_OPTION_SELECT)
		doom->state = GAME_STATE;
	else if (menu->current_option == THIRD_OPTION_SELECT)
		change_win_dimensions(&sdlmain->win_w, &sdlmain->win_h);
	else if (menu->current_option == FOURTH_OPTION_SELECT)
		doom->state = QUIT_STATE;
}

int		menu_events(t_doom *doom)
{
	t_menu		*menu;
	t_sdlmain	*sdlmain;

	menu = &(doom->menu);
	sdlmain = &(doom->sdlmain);
	check_quit(&doom->sdlmain.event, &doom->state);
	if (sdlmain->event.type == SDL_KEYDOWN && sdlmain->event.key.repeat == 0)
	{
		if (sdlmain->event.key.keysym.sym == SDLK_TAB)
			doom->state = menu->previous_state;
		browse_options(sdlmain, menu, menu->options_rects, 1);
		if (sdlmain->event.key.keysym.sym == SDLK_RETURN)
			launch_option(doom);
	}
	else if (sdlmain->event.type == SDL_MOUSEMOTION \
	|| sdlmain->event.type == SDL_MOUSEBUTTONDOWN)
	{
		browse_options(sdlmain, menu, menu->options_rects, 2);
		if (sdlmain->event.button.button == SDL_BUTTON_LEFT)
			launch_option(doom);
	}
	if (doom->state != MENU_STATE)
		return (1);
	return (0);
}

int	reset_menu_text(t_menu *menu, t_sdlmain *sdlmain, \
						SDL_Rect *rect, SDL_Surface **surf)
{
	SDL_Surface	*backgr;
	SDL_Color	color;

	backgr = menu->background;
	color = menu->text_color;
	if (menu->prev_option == menu->current_option)
		return (0);
	if (reset_text(&sdlmain->font, &surf[0], &color, "editor") == -1)
		return (1);
	if (reset_text(&sdlmain->font, &surf[1], &color, "return to game") == -1)
		return (1);
	if (reset_text(&sdlmain->font, &surf[2], &color, "resize window") == -1)
		return (1);
	if (reset_text(&sdlmain->font, &surf[3], &color, "quit game") == -1)
		return (1);
	assign_sdlrect(&rect[0], create_vec((backgr->w - surf[0]->w) / 2, \
					rect[1].y - surf[1]->h), create_vec(0, 0));
	assign_sdlrect(&rect[1], create_vec((backgr->w - surf[1]->w) / 2, \
					(backgr->h - surf[1]->h) / 2), create_vec(0, 0));
	assign_sdlrect(&rect[2], create_vec((backgr->w - surf[2]->w) / 2, \
					rect[1].y + surf[1]->h), create_vec(0, 0));
	assign_sdlrect(&rect[3], create_vec((backgr->w - surf[3]->w) / 2, \
					rect[2].y + surf[2]->h), create_vec(0, 0));
	return (0);
}

int	highlight_select(t_menu *menu, t_sdlmain *sdlmain)
{
	SDL_Rect	*rect;
	SDL_Surface	**surf;
	SDL_Surface	*backgr;
	SDL_Color	color;

	rect = menu->options_rects;
	surf = menu->options;
	backgr = menu->background;
	color = menu->text_color;
	if (menu->prev_option == menu->current_option)
		return (0);
	if (menu->current_option == FIRST_OPTION_SELECT)
	{
		if (highlight_text(&sdlmain->font, &surf[0], &color, "/ editor \\") == -1)
			return (1);
		assign_sdlrect(&rect[0], create_vec((backgr->w - surf[0]->w) / 2, rect[1].y - surf[1]->h), create_vec(0, 0));
	}
	else if (menu->current_option == SECOND_OPTION_SELECT)
	{
		if (highlight_text(&sdlmain->font, &surf[1], &color, "/ return to game \\") == -1)
			return (1);
		assign_sdlrect(&rect[1], create_vec((backgr->w - surf[1]->w) / 2, (backgr->h - surf[1]->h) / 2), create_vec(0, 0));
	}
	else if (menu->current_option == THIRD_OPTION_SELECT)
	{
		if (highlight_text(&sdlmain->font, &surf[2], &color, "/ resize window \\") == -1)
			return (1);
		assign_sdlrect(&rect[2], create_vec((backgr->w - surf[2]->w) / 2, rect[1].y + surf[1]->h), create_vec(0, 0));
	}
	else if (menu->current_option == FOURTH_OPTION_SELECT)
	{
		if (highlight_text(&sdlmain->font, &surf[3], &color, "/ quit game \\") == -1)
			return (1);
		assign_sdlrect(&rect[3], create_vec((backgr->w - surf[3]->w) / 2, rect[2].y + surf[2]->h), create_vec(0, 0));
	}
	return (0);
}

int	reset_doom(t_doom *doom)
{
	free_game(&doom->game, &doom->map);
	free_menu(&doom->menu);
	free_editor(&doom->editor);
	free_sdlmain(&doom->sdlmain);
	quit_sdl_and_ttf();
	if (init_sdl_and_ttf() == 1 \
		|| init_sdlmain(&doom->sdlmain) == 1 \
		|| init_gamesurfs_struct(&doom->game.surfs, &doom->sdlmain) == 1 \
		|| init_enemy_struct(&doom->game, &doom->map) == 1 \
		|| init_menu(&doom->menu, &doom->sdlmain) == 1 \
		|| reset_init_editor(&doom->editor, &doom->sdlmain) == 1)
		return (1);

	doom->editor.player_face_surf = doom->game.surfs.hud_faces_surf;
	doom->editor.player_face_rec.x = doom->game.surfs.hud_faces_rect.x;
	doom->editor.player_face_rec.y = doom->game.surfs.hud_faces_rect.y;
	doom->editor.player_face_rec.h = doom->game.surfs.hud_faces_rect.h;
	doom->editor.player_face_rec.w = doom->game.surfs.hud_faces_rect.w;
	doom->editor.weapon_texture = doom->game.surfs.weapons;
	doom->state = GAME_STATE;
	return (0);
}

int	blit_menu_surfs(t_menu *menu, t_sdlmain *sdlmain)
{
	SDL_Surface	*backgr;
	SDL_Rect	*rect;

	backgr = menu->background;
	rect = menu->options_rects;
	if ((SDL_BlitSurface(menu->menu_title, NULL, \
						backgr, &menu->menu_title_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if (reset_menu_text(menu, sdlmain, menu->options_rects, menu->options) \
						== 1 || highlight_select(menu, sdlmain) == 1)
		return (error_return("Error in highlight selection function\n", NULL));
	if ((SDL_BlitSurface(menu->options[0], NULL, backgr, &rect[0])) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_BlitSurface(menu->options[1], NULL, backgr, &rect[1])) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_BlitSurface(menu->options[2], NULL, backgr, &rect[2])) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_BlitSurface(menu->options[3], NULL, backgr, &rect[3])) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_BlitSurface(backgr, NULL, sdlmain->win_surf, \
						&menu->background_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", \
				SDL_GetError()));
		return (0);
}

int	menu_loop(t_doom *doom)
{
	t_menu		*menu;
	t_sdlmain	*sdlmain;

	menu = &(doom->menu);
	sdlmain = &(doom->sdlmain);
	stop_enem_soundsources(doom->game.enemy, doom->map.num_enemies);
	alSourceStopv(NB_SOUND_SOURCES - 1, &(sdlmain->sound.source[1]));
	while (doom->state == MENU_STATE)
	{
		ft_bzero(menu->background->pixels, \
					menu->background->h * menu->background->pitch);
		draw_border(menu->background, 0xFFFFFF);
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if (menu_events(doom) != 0)
				break ;
		if (sdlmain->win_w != sdlmain->win_surf->w \
				&& sdlmain->win_h != sdlmain->win_surf->h)
			if (reset_doom(doom))
				return (error_return("reset doom error\n", NULL));
		if (blit_menu_surfs(menu, sdlmain) != 0)
			return (1);
	}
	return (0);
}
