/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/09 00:08:20 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int is_in_map(t_vecdb *player)
{
	if (player->x < 0 || player->x >= MINIMAP_WIDTH)
		return (0);
	if (player->y < 0 || player->y >= MINIMAP_HEIGHT)
		return (0);
	return (1);
}

int game_loop(t_doom *doom, t_sdlmain *sdlmain)
{
	const Uint8 *keyboard_state;

	//t_vecdb vec1 = {50, 20}; // start of "first" wall
	//t_vecdb vec2 = {50, 30}; // end of "first" wall
	//t_vecdb vec3 = {70, 100};
	//t_vecdb vec4 = {90, 20};
	t_vecdb vec1 = {50, 50}; // start of "first" wall
	t_vecdb vec2 = {50, 60}; // end of "first" wall
	t_vecdb vec3 = {100, 100};
	t_vecdb vec4 = {80, 50};
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
	SDL_WarpMouseInWindow(sdlmain->win, WIN_W / 2, WIN_H / 2);
	while (doom->data.quit == 0)
	{
		ft_bzero(doom->surfs.perspective_mmap->pixels, doom->surfs.perspective_mmap->h * doom->surfs.perspective_mmap->pitch);
		while (SDL_PollEvent(&(sdlmain->event)) != 0)
			if (handle_events(&sdlmain->event, &doom->data) == 1)
				return (0);
		/*if (doom->data.menu_activate)
		{
			if ((menu_loop(&sdlmain->win, &sdlmain->win_surf, &doom->data.menu_activate)) == 1)
				doom->data.menu_activate = 0;
		}*/
		//handle events (for now player movement and HUD activation/deactivation)
		handle_keys(doom, walls, keyboard_state);
		if (doom->data.hud_flags & COLORFLAG)
			doom->surfs.perspective_mmap->userdata = "yescolor";
		else
			doom->surfs.perspective_mmap->userdata = "nocolor";
		draw_perspective_minimap(doom->surfs.perspective_mmap, &doom->player, walls);
		if ((SDL_BlitScaled(doom->surfs.perspective_mmap, NULL, sdlmain->win_surf, &myrect_thirdmap)) < 0)
		{
			printf("BlitScale error = %s\n", SDL_GetError());
			return (1);
		}
		draw_map(sdlmain, doom, walls, &doom->data.hud_flags);
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &doom->sdl.surf->clip_rect)) < 0)
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, NULL)) < 0)
		if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n",
					   SDL_GetError());
			return (1);
		}
	}
	return (0);
}

int	main_loop()
{
	t_doom doom;
	t_menu menu;
	t_sdlmain sdlmain;
	int	quit;

	quit = 0;
	if (init_sdl_and_ttf() == 1 || init_sdlmain(&sdlmain) == 1 \
		|| init_doom(&doom) || init_menu(&menu) == 1)
		quit = -1;
	/*
	if (init_sdl_and_ttf() == 1)
		quit = -1;
		//return (1);
	if (init_sdlmain(&sdlmain) == 1)
		quit = -1;
		//return (free_sdlmain(&sdlmain));
	if (init_doom(&doom) == 1)
		quit = -1;
		//return (free_doom(&doom));
	if (init_menu(&menu) == 1)
		quit = -1;
	*/
	while (quit == 0)
	{
		// IF ANY OF THE LOOPS FAIL --> RETURN AND EXIT PROPERLY
		if (game_loop(&doom, &sdlmain) == 1)
		{
			quit = -1;
			break ;
		}
		if (doom.data.quit == 1)
			break ;
		if (menu_loop(&menu, &sdlmain) == 1)
		{
			quit = -1;
			break;
		}
	}
	free_doom(&doom);
	free_menu(&menu);
	free_sdlmain(&sdlmain);
	quit_sdl_and_ttf();
	if (quit == -1)
		return (error_return("Error during main loop init\n", NULL));
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
