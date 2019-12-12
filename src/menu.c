/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:27:36 by afonck            #+#    #+#             */
/*   Updated: 2019/12/09 12:54:08 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int init_menu(t_menu *menu)
{
	menu->current_option = 0;
	menu->activate = 1;
	//Load the background image
	menu->background = NULL;

	//Open the font
	if ((menu->font = TTF_OpenFont("assets/fonts/dukes-3d.ttf", 28 / SIZE)) == NULL)
		return (error_return("TTF_OpenFont error = %s\n", TTF_GetError()));
	assign_sdlcolor(&menu->textColor, 255, 0, 0);
	assign_sdlrect(&menu->background_rect, create_vec((WIN_W / 8) / 2, (WIN_H / 4) / 2), create_vec(0, 0));//MENU_WIDTH, MENU_HEIGHT));
	if ((menu->menu_title = TTF_RenderText_Solid(menu->font, "MENU", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->first_option = TTF_RenderText_Solid(menu->font, "editor", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->second_option = TTF_RenderText_Solid(menu->font, "return to game", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->third_option = TTF_RenderText_Solid(menu->font, "quit game", menu->textColor)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", TTF_GetError()));
	if ((menu->background = SDL_CreateRGBSurface(0, WIN_W - (WIN_W / 8), WIN_H - (WIN_H / 4), 32, 0, 0, 0, 0)) == NULL)
		return (error_return("SDL_CreateRGBSurface error = %s\n", SDL_GetError()));
	assign_sdlrect(&menu->menu_title_rect, create_vec((menu->background->w - menu->menu_title->w) / 2, (menu->background->h - menu->menu_title->h) / 8), create_vec(0, 0));
	assign_sdlrect(&menu->first_option_rect, create_vec((menu->background->w - menu->first_option->w) / 2, menu->second_option_rect.y - menu->second_option->h), create_vec(0, 0));
	assign_sdlrect(&menu->second_option_rect, create_vec((menu->background->w - menu->second_option->w) / 2, (menu->background->h - menu->second_option->h) / 2), create_vec(0, 0));
	assign_sdlrect(&menu->third_option_rect, create_vec((menu->background->w - menu->third_option->w) / 2, menu->second_option_rect.y + menu->second_option->h), create_vec(0, 0));
	draw_border(menu->background, 0xFFFFFF);

	return (0);
}

void	browse_options(SDL_Event *event, int *option)
{
	if (event->key.keysym.sym == SDLK_DOWN && *option < 3)
		*option += 1;
	if (event->key.keysym.sym == SDLK_UP && *option > 1)
		*option -= 1;
}

void	launch_option(t_menu *menu, int *option_selected, SDL_Window **win, SDL_Surface **win_surf)
{
	if (*option_selected == FIRST_OPTION_SELECT)
	{
		menu->editor_flag = 1;
		editor(win, win_surf, &menu->editor_flag);
		menu->editor_flag = 0;
	}
	else if (*option_selected == SECOND_OPTION_SELECT)
		menu->activate = 0;
	else if (*option_selected == THIRD_OPTION_SELECT)
		menu->activate = 0;
}

void	menu_events(t_menu *menu, SDL_Window **win, SDL_Surface **win_surf)
{
		if (menu->event.type == SDL_KEYDOWN && menu->event.key.repeat == 0)
		{
			if (menu->event.key.keysym.sym == SDLK_TAB)
				menu->activate = 0;
			browse_options(&menu->event, &menu->current_option);
			if (menu->event.key.keysym.sym == SDLK_RETURN)
				launch_option(menu, &menu->current_option, win, win_surf);
		}
}

int	highlight_select(t_menu *menu)
{
	if (reset_text(&menu->font, &menu->first_option, &menu->textColor, "editor") == -1)
		return (1);
	if (reset_text(&menu->font, &menu->second_option, &menu->textColor, "return to game") == -1)
		return (1);
	if (reset_text(&menu->font, &menu->third_option, &menu->textColor, "quit game") == -1)
		return (1);
	assign_sdlrect(&menu->first_option_rect, create_vec((menu->background->w - menu->first_option->w) / 2, menu->second_option_rect.y - menu->second_option->h), create_vec(0, 0));
	assign_sdlrect(&menu->second_option_rect, create_vec((menu->background->w - menu->second_option->w) / 2, (menu->background->h - menu->second_option->h) / 2), create_vec(0, 0));
	assign_sdlrect(&menu->third_option_rect, create_vec((menu->background->w - menu->third_option->w) / 2, menu->second_option_rect.y + menu->second_option->h), create_vec(0, 0));
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
		if (highlight_text(&menu->font, &menu->third_option, &menu->textColor, "/ quit game \\") == -1)
			return (1);
		assign_sdlrect(&menu->third_option_rect, create_vec((menu->background->w - menu->third_option->w) / 2, menu->second_option_rect.y + menu->second_option->h), create_vec(0, 0));
	}
	return (0);
}

int menu_loop(t_menu *menu, t_sdlmain *sdlmain)
{
	//t_menu menu;

	//if (init_menu(&menu) != 0)
	//	return (error_return("Error in init_menu function\n", NULL));
	while (menu->activate == 1)
	{
		ft_bzero(menu->background->pixels, menu->background->h * menu->background->pitch);
		draw_border(menu->background, 0xFFFFFF);
		while (SDL_PollEvent(&menu->event) != 0)
			menu_events(menu, &sdlmain->win, &sdlmain->win_surf);
		
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
		if ((SDL_BlitSurface(menu->background, NULL, sdlmain->win_surf, &menu->background_rect)) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));

		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
			return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError()));
	}
	menu->activate = 1;
	return (0);
}