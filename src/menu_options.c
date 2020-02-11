/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:01:21 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 21:02:23 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

int		highlight_first_and_second_option(t_menu *menu, TTF_Font *font)
{
	if (menu->current_option == FIRST_OPTION_SELECT)
	{
		if (highlight_text(&font, &menu->options[0], \
			&menu->text_color, "/ editor \\") == -1)
			return (1);
		assign_sdlrect(&menu->options_rects[0], \
			create_vec((menu->background->w - menu->options[0]->w) / 2, \
			menu->options_rects[1].y - menu->options[1]->h), create_vec(0, 0));
	}
	else if (menu->current_option == SECOND_OPTION_SELECT)
	{
		if (highlight_text(&font, &menu->options[1], \
				&menu->text_color, "/ return to game \\") == -1)
			return (1);
		assign_sdlrect(&menu->options_rects[1], \
			create_vec((menu->background->w - menu->options[1]->w) / 2, \
			(menu->background->h - menu->options[1]->h) / 2), create_vec(0, 0));
	}
	return (0);
}

int		highlight_select(t_menu *menu, TTF_Font *font)
{
	if (menu->prev_option == menu->current_option)
		return (0);
	if (highlight_first_and_second_option(menu, font) != 0)
		return (1);
	if (menu->current_option == THIRD_OPTION_SELECT)
	{
		if (highlight_text(&font, &menu->options[2], \
			&menu->text_color, "/ resize window \\") == -1)
			return (1);
		assign_sdlrect(&menu->options_rects[2], \
			create_vec((menu->background->w - menu->options[2]->w) / 2, \
			menu->options_rects[1].y + menu->options[1]->h), create_vec(0, 0));
	}
	else if (menu->current_option == FOURTH_OPTION_SELECT)
	{
		if (highlight_text(&font, &menu->options[3], \
				&menu->text_color, "/ quit game \\") == -1)
			return (1);
		assign_sdlrect(&menu->options_rects[3], \
			create_vec((menu->background->w - menu->options[3]->w) / 2, \
			menu->options_rects[2].y + menu->options[2]->h), create_vec(0, 0));
	}
	return (0);
}
