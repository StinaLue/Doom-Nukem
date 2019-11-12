/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/13 01:02:51 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
/*
int		blit_and_update(SDL_Surface **fps, SDL_Surface **screen, \
			SDL_Window **win)
{
	if ((SDL_BlitSurface(*fps, NULL, *screen, NULL)) < 0)
	{
		ft_dprintf(STDERR_FILENO, "SDL_BlitSurface error = %{r}s\n", \
			SDL_GetError());
		return (-1);
	}
	SDL_FreeSurface(*fps);
	*fps = NULL;
	if ((SDL_UpdateWindowSurface(*win)) < 0)
	{
		ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n", \
			SDL_GetError());
		return (-1);
	}
	return (0);
}
*/
void	check_quit(SDL_Event *event, int *quit)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && \
		event->key.keysym.sym == SDLK_ESCAPE))
		*quit = 1;
}

int		is_in_map(t_vecdb *player)
{
	if (player->x < 0 || player->x >= FIRST_MAP_WIDTH)
		return (0);
	if (player->y < 0 || player->y >= FIRST_MAP_HEIGHT)
		return (0);
	return (1);
}

void	basic_move(t_vecdb *player, double *angle, const Uint8 *keyboard_state)
{
	if (!is_in_map(player))
	{
		player->x = 70;
		player->y = 70;
	}
	if (keyboard_state[SDL_SCANCODE_UP])
	{
		player->x += cos(*angle) / 5; //5 == speed reduction
		player->y += sin(*angle) / 5;
	}
	if (keyboard_state[SDL_SCANCODE_DOWN])
	{
		player->x -= cos(*angle) / 5;
		player->y -= sin(*angle) / 5;
	}
	if (keyboard_state[SDL_SCANCODE_LEFT])
		*angle -= 0.1;
	if (keyboard_state[SDL_SCANCODE_RIGHT])
		*angle += 0.1;
}

void	main_loop(t_doom *doom)
{
	//int			start_clock;
	//int			delta_clock;
	//int			current_fps;
	const Uint8 *keyboard_state;

	SDL_Surface *my_map = NULL; // surface for the map
	Uint32 *img_map_ptr; // pointer to the pixels of the map surface

	t_vec vec1 = {50, 20}; // start of wall
	t_vec vec2 = {50, 70}; // end of wall

	double angle = 0.0; // direction angle of player
	t_vecdb playerdb = {70, 70}; // player pos in float
	t_vecdb direcdb; // player direction in float
	t_vec player; // player pos in int
	t_vec direc; // player pos in float

	SDL_Rect myrect = {.x=0, .y=0, .w=WIN_WIDTH, .h=WIN_HEIGHT}; // Stretching rectangle to print the map in fullscreen

	//current_fps = 100;
	/*
		When creating a surface, the last four parameters correspond to the RGBA masks for the created surface. They need to correspond
		to the format of the surface we copy to (the window)
		SDL_ConvertSurface function can be used to adapt the format of a new surface to the format of an other surface (the window in our case)

		NOT FORGET --> if something feels wrong about the colors in the project, it could come from the format of the surfaces, including the
		surface of the window
	*/
	if ((my_map = SDL_CreateRGBSurface(0, FIRST_MAP_WIDTH, FIRST_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	//my_map = SDL_ConvertSurface(my_map, doom->sdl.surf->format, 0);
	img_map_ptr = my_map->pixels;
	doom->data.img_ptr = doom->sdl.surf->pixels;
	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(doom->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!doom->data.quit)
	{
		ft_bzero(img_map_ptr, (FIRST_MAP_WIDTH * FIRST_MAP_HEIGHT) * 4);
		while (SDL_PollEvent(&(doom->sdl.event)) != 0)
			check_quit(&(doom->sdl.event), &(doom->data.quit));
		//ft_bzero(doom->data.img_ptr, WIN_WIDTH * WIN_HEIGHT);

		//move the player and assign his new position, need float and then int converting because of angle calculation
		basic_move(&playerdb, &angle, keyboard_state);
		direcdb.x = cos(angle) * 5 + playerdb.x;
		direcdb.y = sin(angle) * 5 + playerdb.y;
		player.x = (int)playerdb.x;
		player.y = (int)playerdb.y;
		direc.x = (int)direcdb.x;
		direc.y = (int)direcdb.y;


		//draw_line(&vec1, &vec2, doom->data.img_ptr, 0xFFFFFF);
		//draw_line(&player, &direc, doom->data.img_ptr, 0xFF0000);
		//fill_pix(doom->data.img_ptr, player.x, player.y, 0xFFFF00);
		//SDL_LockSurface(my_map);
		draw_line(&vec1, &vec2, img_map_ptr, 0xFFFFFF);
		draw_line(&player, &direc, img_map_ptr, 0xFF0000);
		fill_pix(img_map_ptr, player.x, player.y, 0xFFFF00);
		//SDL_UnlockSurface(my_map);
		//write(1, &my_map->pixels[50 + (20 * 100)], 1);
		//SDL_BlitSurface(my_map, NULL, doom->sdl.surf, NULL);
		if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &myrect)) < 0)
			printf("BlitScale error = %s\n", SDL_GetError());
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

	if (MAX_MAP > 100 || WIN_WIDTH > 1920 || WIN_HEIGHT > 1080 || MAX_MAP < 10 \
		|| WIN_WIDTH < 100 || WIN_HEIGHT < 100)
		return (1);
	if (init_sdl(&(doom.sdl.win), &(doom.sdl.surf)) != EXIT_SUCCESS)
		return (free_sdl_quit(&(doom.sdl.win)));
	//if (init_ttf(&(doom.ttf)) != EXIT_SUCCESS)
	//	return (free_sdl_ttf_quit(&(doom.sdl.win), &(doom.ttf)));
	main_loop(&doom);
	free_sdl(&(doom.sdl.win));
	//free_ttf(&(doom.ttf));
	return (EXIT_SUCCESS);
}
