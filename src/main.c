/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/05 15:51:11 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int		is_in_map(t_vecdb *player)
{
	if (player->x < 0 || player->x >= MINIMAP_WIDTH)
		return (0);
	if (player->y < 0 || player->y >= MINIMAP_HEIGHT)
		return (0);
	return (1);
}

void	main_loop(t_doom *doom)
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
		printf("parsing error\n");
	}

	SDL_Rect myrect_thirdmap = {.x=0, .y=0, .w=WIN_WIDTH, .h=WIN_HEIGHT}; // Stretching rectangle to print the map in fullscreen
	/*
		When creating a surface, the last four parameters correspond to the RGBA masks for the created surface. They need to correspond
		to the format of the surface we copy to (the window)
		SDL_ConvertSurface function can be used to adapt the format of a new surface to the format of an other surface (the window in our case)

		NOT FORGET --> if something feels wrong about the colors in the project, it could come from the format of the surfaces, including the
		surface of the window
	*/
	if ((doom->sdl.rot_mmap = SDL_CreateRGBSurface(0, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((doom->sdl.fixed_mmap = SDL_CreateRGBSurface(0, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((doom->sdl.perspective_mmap = SDL_CreateRGBSurface(0, THIRD_MAP_WIDTH, THIRD_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	//my_map = SDL_ConvertSurface(my_map, doom->sdl.surf->format, 0);

	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(doom->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!doom->data.quit)
	{
		ft_bzero(doom->sdl.perspective_mmap->pixels, doom->sdl.perspective_mmap->h * doom->sdl.perspective_mmap->pitch);
		while (SDL_PollEvent(&(doom->sdl.event)) != 0)
			handle_events(&doom->sdl.event, &doom->data);

		//handle events (for now player movement and HUD activation/deactivation)
		handle_keys(doom, walls, keyboard_state);

		if (doom->data.hud_flags & COLORFLAG)
			doom->sdl.perspective_mmap->userdata = "yescolor";
		else
			doom->sdl.perspective_mmap->userdata = "nocolor";
		
		(void)myrect_thirdmap;
		draw_perspective_minimap(doom->sdl.perspective_mmap, &doom->player, walls);
		if ((SDL_BlitScaled(doom->sdl.perspective_mmap, NULL, doom->sdl.win_surf, &myrect_thirdmap)) < 0)
			printf("BlitScale error = %s\n", SDL_GetError());

		draw_map(&doom->sdl, &doom->player, walls, &doom->data.hud_flags);

		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &doom->sdl.surf->clip_rect)) < 0)
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, NULL)) < 0)
		if ((SDL_UpdateWindowSurface(doom->sdl.win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n", \
				SDL_GetError());
			return ;
		}
	}
}

int		main(/*int argc, char *argv[]*/)
{
	t_doom	doom;

	init_doom(&doom);
	if (WIN_WIDTH > 1920 || WIN_HEIGHT > 1080 || WIN_WIDTH < 100 || WIN_HEIGHT < 100)
		return (1);
	if (init_sdl(&(doom.sdl.win), &(doom.sdl.win_surf)) != EXIT_SUCCESS)
		return (free_sdl_quit(&(doom.sdl.win)));
	main_loop(&doom);
	free_sdl(&(doom.sdl.win));
	return (EXIT_SUCCESS);
}
