/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:27:36 by afonck            #+#    #+#             */
/*   Updated: 2019/12/13 16:11:52 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int init_menu(t_menu *menu, t_sdlmain *sdlmain)
{
	menu->current_option = 0;
	menu->previous_state = QUIT_STATE;
	//Load the background image
	menu->background = NULL;

	//Open the font
	if ((menu->font = TTF_OpenFont("assets/fonts/dukes-3d.ttf", 28)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	assign_sdlcolor(&menu->textColor, 255, 0, 0);
	assign_sdlrect(&menu->background_rect, create_vec((sdlmain->win_surf->w / 8) / 2, (sdlmain->win_surf->h / 4) / 2), create_vec(0, 0));//MENU_WIDTH, MENU_HEIGHT));
	if ((menu->menu_title = TTF_RenderText_Solid(menu->font, "MENU", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->first_option = TTF_RenderText_Solid(menu->font, "editor", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->second_option = TTF_RenderText_Solid(menu->font, "return to game", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->third_option = TTF_RenderText_Solid(menu->font, "resize window", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->fourth_option = TTF_RenderText_Solid(menu->font, "quit game", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->background = SDL_CreateRGBSurface(0, sdlmain->win_surf->w - (sdlmain->win_surf->w / 8), sdlmain->win_surf->h - (sdlmain->win_surf->h / 4), 32, 0, 0, 0, 0)) == NULL)
		return (error_return("SDL_CreateRGBSurface error = %s\n", SDL_GetError()));
	assign_sdlrect(&menu->menu_title_rect, create_vec((menu->background->w - menu->menu_title->w) / 2, (menu->background->h - menu->menu_title->h) / 8), create_vec(0, 0));
	assign_sdlrect(&menu->first_option_rect, create_vec((menu->background->w - menu->first_option->w) / 2, menu->second_option_rect.y - menu->second_option->h), create_vec(0, 0));
	assign_sdlrect(&menu->second_option_rect, create_vec((menu->background->w - menu->second_option->w) / 2, (menu->background->h - menu->second_option->h) / 2), create_vec(0, 0));
	assign_sdlrect(&menu->third_option_rect, create_vec((menu->background->w - menu->third_option->w) / 2, menu->second_option_rect.y + menu->second_option->h), create_vec(0, 0));
	assign_sdlrect(&menu->fourth_option_rect, create_vec((menu->background->w - menu->fourth_option->w) / 2, menu->third_option_rect.y + menu->third_option->h), create_vec(0, 0));
	draw_border(menu->background, 0xFFFFFF);

	return (0);
}

void	browse_options(SDL_Event *event, int *option)
{
	if (event->key.keysym.sym == SDLK_DOWN && *option < 4)
		*option += 1;
	if (event->key.keysym.sym == SDLK_UP && *option > 1)
		*option -= 1;
}

void	change_win_dimensions(int *width, int *height)
{
	if (*width == HD_W && *height == HD_H)
	{
		*width = FULLHD_W;
		*height = FULLHD_H;
	}
	else if (*width == FULLHD_W && *height == FULLHD_H)
	{
		*width = HD_W;
		*height = HD_H;
	}
}

void	launch_option(t_doom *doom)
{
	t_menu *menu;
	t_sdlmain *sdlmain;

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
	t_menu *menu;
	t_sdlmain *sdlmain;

	menu = &(doom->menu);
	sdlmain = &(doom->sdlmain);
	if (sdlmain->event.type == SDL_KEYDOWN && sdlmain->event.key.repeat == 0)
	{
		if (sdlmain->event.key.keysym.sym == SDLK_TAB)
			doom->state = menu->previous_state;
		browse_options(&sdlmain->event, &menu->current_option);
		if (sdlmain->event.key.keysym.sym == SDLK_RETURN)
			launch_option(doom);
	}
	if (doom->state != MENU_STATE)
		return (1);
	return (0);
}

int	highlight_select(t_menu *menu)
{
	if (reset_text(&menu->font, &menu->first_option, &menu->textColor, "editor") == -1)
		return (1);
	if (reset_text(&menu->font, &menu->second_option, &menu->textColor, "return to game") == -1)
		return (1);
	if (reset_text(&menu->font, &menu->third_option, &menu->textColor, "resize window") == -1)
		return (1);
	if (reset_text(&menu->font, &menu->fourth_option, &menu->textColor, "quit game") == -1)
		return (1);
	assign_sdlrect(&menu->first_option_rect, create_vec((menu->background->w - menu->first_option->w) / 2, menu->second_option_rect.y - menu->second_option->h), create_vec(0, 0));
	assign_sdlrect(&menu->second_option_rect, create_vec((menu->background->w - menu->second_option->w) / 2, (menu->background->h - menu->second_option->h) / 2), create_vec(0, 0));
	assign_sdlrect(&menu->third_option_rect, create_vec((menu->background->w - menu->third_option->w) / 2, menu->second_option_rect.y + menu->second_option->h), create_vec(0, 0));
	assign_sdlrect(&menu->fourth_option_rect, create_vec((menu->background->w - menu->fourth_option->w) / 2, menu->third_option_rect.y + menu->third_option->h), create_vec(0, 0));
	if (menu->current_option == FIRST_OPTION_SELECT)
	{
		if (highlight_text(&menu->font, &menu->first_option, &menu->textColor, "/ editor \\") == -1)
			return (1);
		assign_sdlrect(&menu->first_option_rect, create_vec((menu->background->w - menu->first_option->w) / 2, menu->second_option_rect.y - menu->second_option->h), create_vec(0, 0));
	}
	else if (menu->current_option == SECOND_OPTION_SELECT)
	{
		if (highlight_text(&menu->font, &menu->second_option, &menu->textColor, "/ return to game \\") == -1)
			return (1);
		//assign_sdlrect(&menu->second_option_rect, create_vec((menu->background->w - menu->second_option->w) / 2, menu->first_option_rect.y + menu->first_option->h), create_vec(0, 0));
		assign_sdlrect(&menu->second_option_rect, create_vec((menu->background->w - menu->second_option->w) / 2, (menu->background->h - menu->second_option->h) / 2), create_vec(0, 0));
	}
	else if (menu->current_option == THIRD_OPTION_SELECT)
	{
		if (highlight_text(&menu->font, &menu->third_option, &menu->textColor, "/ resize window \\") == -1)
			return (1);
		assign_sdlrect(&menu->third_option_rect, create_vec((menu->background->w - menu->third_option->w) / 2, menu->second_option_rect.y + menu->second_option->h), create_vec(0, 0));
	}
	else if (menu->current_option == FOURTH_OPTION_SELECT)
	{
		if (highlight_text(&menu->font, &menu->fourth_option, &menu->textColor, "/ quit game \\") == -1)
			return (1);
		assign_sdlrect(&menu->fourth_option_rect, create_vec((menu->background->w - menu->fourth_option->w) / 2, menu->third_option_rect.y + menu->third_option->h), create_vec(0, 0));
	}
	return (0);
}

int	reset_doom(t_doom *doom)
{
	free_game(&doom->game);
	free_menu(&doom->menu);
	free_editor(&doom->editor);
	free_sdlmain(&doom->sdlmain);
	quit_sdl_and_ttf();
	if (init_sdl_and_ttf() == 1 || init_sdlmain(&doom->sdlmain) == 1 \
		|| init_game(&doom->game, &doom->sdlmain) || init_menu(&doom->menu, &doom->sdlmain) == 1 \
		|| init_editor(&doom->editor, &doom->sdlmain) == 1)
		return (1);
	return (0);
}

int menu_loop(t_doom *doom)
{
	t_menu *menu;
	t_sdlmain *sdlmain;

	menu = &(doom->menu);
	sdlmain = &(doom->sdlmain);
	while (doom->state == MENU_STATE)
	{
		ft_bzero(menu->background->pixels, menu->background->h * menu->background->pitch);
		draw_border(menu->background, 0xFFFFFF);
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if (menu_events(doom) != 0)
				break ;
		//printf("winw %d winh %d surf w %d surf h %d\n", sdlmain->win_w, sdlmain->win_h, sdlmain->win_surf->w, sdlmain->win_surf->h);
		if (sdlmain->win_w != sdlmain->win_surf->w && sdlmain->win_h != sdlmain->win_surf->h)
			if (reset_doom(doom))
				return (error_return("reset doom error\n", NULL));
		if ((SDL_BlitSurface(menu->menu_title, NULL, menu->background, &menu->menu_title_rect)) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		if (highlight_select(menu) == 1)
			return (error_return("Error in highlight selection function\n", NULL));
		if ((SDL_BlitSurface(menu->first_option, NULL, menu->background, &menu->first_option_rect)) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		if ((SDL_BlitSurface(menu->second_option, NULL, menu->background, &menu->second_option_rect)) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		if ((SDL_BlitSurface(menu->third_option, NULL, menu->background, &menu->third_option_rect)) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		if ((SDL_BlitSurface(menu->fourth_option, NULL, menu->background, &menu->fourth_option_rect)) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		if ((SDL_BlitSurface(menu->background, NULL, sdlmain->win_surf, &menu->background_rect)) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));

		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
			return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError()));
	}
	return (0);
}
