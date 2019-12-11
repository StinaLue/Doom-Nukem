/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 15:06:01 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int game_loop(t_doom *doom, t_sdlmain *sdlmain)
{
	const Uint8 *keyboard_state;

	t_vecdb vec1 = {50, 20}; // start of "first" wall
	t_vecdb vec2 = {50, 30}; // end of "first" wall
	t_vecdb vec3 = {70, 100};
	t_vecdb vec4 = {90, 20};
	/* t_vecdb vec1 = {60, 70}; 
	t_vecdb vec2 = {70, 200}; 		<--COLLISION TEST MAP
	t_vecdb vec3 = {80, 70};
	t_vecdb vec4 = {70, -60};*/
	t_wall walls[NB_WALLS] = {{vec1, vec2, 0xFF0000}, {vec2, vec3, 0x00FF00}, {vec3, vec4, 0x0000FF}, {vec4, vec1, 0x00FFFF}};
	//t_wall walls[NB_WALLS] = {{vec1, vec2, 0xFF0000}};

	if (parse_everything(walls) != 0)
	{
		ft_dprintf(STDERR_FILENO, "parsing error\n");
		return (1);
	}

	SDL_Rect myrect_thirdmap;
	
	myrect_thirdmap = create_sdlrect(0, 0, WIN_W, WIN_H);
	/*
		When creating a surface, the last four parameters correspond to the RGBA masks for the created surface. They need to correspond
		to the format of the surface we copy to (the window)
		SDL_ConvertSurface function can be used to adapt the format of a new surface to the format of an other surface (the window in our case)

		NOT FORGET --> if something feels wrong about the colors in the project, it could come from the format of the surfaces, including the
		surface of the window
	*/
	//my_map = SDL_ConvertSurface(my_map, doom->sdl.surf->format, 0);

	keyboard_state = SDL_GetKeyboardState(NULL);
	int event_return = 0;
	SDL_WarpMouseInWindow(sdlmain->win, WIN_W / 2, WIN_H / 2);
	while (doom->data.activate == 1)
	{
		ft_bzero(doom->surfs.perspective_mmap->pixels, doom->surfs.perspective_mmap->h * doom->surfs.perspective_mmap->pitch);
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
			if ((event_return = handle_events(&sdlmain->event, &doom->data)) != CONTINUE_GAME)
				return(event_return);
		handle_keys(doom, walls, keyboard_state);
		if (doom->data.hud_flags & COLORFLAG)
			doom->surfs.perspective_mmap->userdata = "yescolor";
		else
			doom->surfs.perspective_mmap->userdata = "nocolor";
		draw_perspective_minimap(doom->surfs.perspective_mmap, &doom->player, walls);
		if ((SDL_BlitScaled(doom->surfs.perspective_mmap, NULL, sdlmain->win_surf, &myrect_thirdmap)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
		if ((draw_map(sdlmain, doom, walls, &doom->data.hud_flags)) == 1)
			return (error_return("error during map drawing\n", NULL));
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &doom->sdl.surf->clip_rect)) < 0)
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, NULL)) < 0)
		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
			return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError()));
	}
	return (QUIT_GAME);
}

int	main_loop()
{
	t_game game;
	/*t_doom doom;
	t_menu menu;
	t_editor editor;
	t_sdlmain sdlmain;*/
	int	quit;

	quit = 0;
	if (init_sdl_and_ttf() == 1 || init_sdlmain(&game.sdlmain) == 1 \
		|| init_doom(&game.doom) || init_menu(&game.menu) == 1 || init_editor(&game.editor) == 1)
		quit = -1;
	int state = GAME_STATE;
	game.doom.data.activate = 1;
	int loop_ret = 0;
	while (quit == 0)
	{
		// IF ANY OF THE LOOPS FAIL --> RETURN AND EXIT PROPERLY
		if (state == GAME_STATE)
		{
			loop_ret = game_loop(&game.doom, &game.sdlmain);
			if (loop_ret == ERROR_GAME)
			{
				quit = -1;
				break ;
			}
			else if (loop_ret == MENU_GAME)
				game.menu.activate = 1;
			else if (loop_ret == QUIT_GAME)
				game.doom.data.activate = 0;
		}
		else if (state == MENU_STATE)
		{
			loop_ret = menu_loop(&game.menu, &game.sdlmain);
			if (loop_ret == ERROR_MENU)
			{
				quit = -1;
				break ;
			}
			else if (loop_ret == FIRST_OPT)
			{ 
				game.doom.data.activate = 0;
				game.menu.activate = 0;
				game.editor.activate = 1;
			}
			else if (loop_ret == SECOND_OPT)
			{
				game.menu.activate = 0;
				game.editor.activate = 0;
				game.doom.data.activate = 1;
			}
			else if (loop_ret == THIRD_OPT)
			{
				game.menu.activate = 0;
				game.editor.activate = 0;
				quit = 1;
			}
			else if (loop_ret == QUIT_MENU)
				game.menu.activate = 0;
		}
		else if (state == EDITOR_STATE)
		{
			loop_ret = editor_loop(&game.editor, &game.sdlmain);
			if (loop_ret == ERROR_EDITOR)
			{
				quit = -1;
				break ;
			}
			else if (loop_ret == MENU_EDITOR)
				game.menu.activate = 1;
			else if (loop_ret == QUIT_EDITOR)
				game.editor.activate = 0;
		}
		if (game.doom.data.activate == 0 && game.menu.activate == 0 && game.editor.activate == 0)
			quit = 1;
		else if (game.menu.activate == 1)
			state = MENU_STATE;
		else if (game.editor.activate == 1)
			state = EDITOR_STATE;
		else if (game.doom.data.activate == 1)
			state = GAME_STATE;
	}
	free_doom(&game.doom);
	free_menu(&game.menu);
	free_editor(&game.editor);
	free_sdlmain(&game.sdlmain);
	quit_sdl_and_ttf();
	if (quit == -1)
		return (error_return("Error during main loop\n", NULL));
	return (0);
}

int main(/*int argc, char *argv[]*/)
{
	if (WIN_W > 1920 || WIN_H > 1080 || WIN_W < 100 || WIN_H < 100)
		return (1);
	if (main_loop() == 1)
	{
		return (error_return("Error during main loop\n", NULL));
	}
	return (EXIT_SUCCESS);
}
