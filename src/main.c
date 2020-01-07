/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/07 16:49:45 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include "libbmp.h"

int game_loop(t_doom *doom)
{
	t_game *game;
	t_sdlmain *sdlmain;
	const Uint8 *keyboard_state;
	Uint32 startclock = 0;
	//Uint32 deltaclock = 0;
	//Uint32 currentFPS = 0;
	//int frame = 0;
	int itt = 0;

	startclock = SDL_GetTicks();

	game = &(doom->game);
	sdlmain = &(doom->sdlmain);

	//if (parse_everything(walls) != 0)
	//	return (error_return("parsing error\n", NULL));

	SDL_Rect myrect_thirdmap;
	
	myrect_thirdmap = create_sdlrect(0, 0, doom->sdlmain.win_surf->w, doom->sdlmain.win_surf->h);
	/*
		When creating a surface, the last four parameters correspond to the RGBA masks for the created surface. They need to correspond
		to the format of the surface we copy to (the window)
		SDL_ConvertSurface function can be used to adapt the format of a new surface to the format of an other surface (the window in our case)

		NOT FORGET --> if something feels wrong about the colors in the project, it could come from the format of the surfaces, including the
		surface of the window
	*/
	//my_map = SDL_ConvertSurface(my_map, doom->sdl.surf->format, 0);

	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(sdlmain->win, sdlmain->win_surf->w / 2, sdlmain->win_surf->h / 2);
	startclock = SDL_GetTicks();
	while (doom->state == GAME_STATE)
	{
		ft_bzero(game->surfs.perspective_view->pixels, game->surfs.perspective_view->h * game->surfs.perspective_view->pitch);
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
			if (handle_events(doom) != 0)
				break ;
		handle_keys(game, &doom->map, keyboard_state);
		if (game->data.hud_flags & COLORFLAG)
			game->surfs.perspective_view->userdata = "yescolor";
		else
			game->surfs.perspective_view->userdata = "nocolor";
		draw_perspective_view(game->surfs.perspective_view, &game->player, &doom->map);
		if ((SDL_BlitScaled(game->surfs.perspective_view, NULL, sdlmain->win_surf, &myrect_thirdmap)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
		if ((draw_map(sdlmain, game, &doom->map, &game->data.hud_flags)) == 1)
			return (error_return("error during map drawing\n", NULL));
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &doom->sdl.surf->clip_rect)) < 0)
		if ((SDL_BlitScaled(game->surfs.weapons, &game->surfs.katana[(int)((float)SDL_GetTicks() / 400) % 4], sdlmain->win_surf, NULL)) != 0)
			printf("%s\n", SDL_GetError());
		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
			return (error_return("SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError()));
		itt++;
		if (SDL_GetTicks() - startclock >= 1000)
		{
			printf("fps:%d\n", itt);
			itt = 0;
			startclock = SDL_GetTicks();
		}
	}
	return (0);
}

void null_doom_pointers(t_doom *doom)
{
	doom->game.surfs.fixed_mmap = NULL;
	doom->game.surfs.rot_mmap = NULL;
	doom->game.surfs.perspective_view = NULL;
	doom->game.surfs.weapons = NULL;
	doom->menu.background = NULL;
	doom->menu.menu_title = NULL;
	doom->menu.first_option = NULL;
	doom->menu.second_option = NULL;
	doom->menu.third_option = NULL;
	doom->menu.fourth_option = NULL;
	doom->menu.font = NULL;
	doom->editor.editor_surf = NULL;
	doom->editor.instruct_surf = NULL;
	doom->sdlmain.win = NULL;
	doom->sdlmain.win_surf = NULL;
	doom->sdlmain.music = NULL;
	doom->map.sector_head = NULL;
	doom->editor.edit_map.sector_head = NULL;
}

int	main_loop()
{
	t_doom	doom;
	int		ret;

	ret = 0;
	doom.state = GAME_STATE;
	doom.sdlmain.win_w = HD_W;
	doom.sdlmain.win_h = HD_H;
	null_doom_pointers(&doom);
	if (init_map(&doom.map) == 1 || init_sdl_and_ttf() == 1 || init_sdlmain(&doom.sdlmain) == 1 \
		|| init_game(&doom.game, &doom.sdlmain) || init_menu(&doom.menu, &doom.sdlmain) == 1)/* \
		|| init_editor(&doom.editor, &doom.sdlmain) == 1)*/
	{
		ret = 1;
		doom.state = QUIT_STATE;
	}
	while (doom.state != QUIT_STATE)
	{
		if (doom.state == GAME_STATE)
			ret = game_loop(&doom);
		else if (doom.state == MENU_STATE)
			ret = menu_loop(&doom);
		else if (doom.state == EDITOR_STATE)
			//ret = editor_loop(&doom);
		if (ret == 1)
			doom.state = QUIT_STATE;
	}
	free_game(&doom.game);
	free_menu(&doom.menu);
	free_editor(&doom.editor);
	free_sdlmain(&doom.sdlmain);
	quit_sdl_and_ttf();
	if (ret == 1)
		return (error_return("Error during main loop\n", NULL));
	return (0);
}

int main(/*int argc, char *argv[]*/)
{
	//if (WIN_W > 1920 || WIN_H > 1080 || WIN_W < 100 || WIN_H < 100)
	//	return (1);
	if (main_loop() == 1)
	{
		return (error_return("The program %{r}s 😢\n", "FAILED"));
	}
	return (EXIT_SUCCESS);
}
