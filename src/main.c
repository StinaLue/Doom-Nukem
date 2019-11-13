/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/13 23:38:25 by sluetzen         ###   ########.fr       */
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

// THIS VARIABLE SHOULD NOT BE GLOBAL, TEMPORARLY DONE FOR MAKING THINGS EASY
static double angle = 0.0;// direction angle of player

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
		player->x += cos(*angle) / 10; //5 == speed reduction
		player->y += sin(*angle) / 10;
	}
	if (keyboard_state[SDL_SCANCODE_DOWN])
	{
		player->x -= cos(*angle) / 10;
		player->y -= sin(*angle) / 10;
	}
	if (keyboard_state[SDL_SCANCODE_LEFT])
		*angle -= 0.01;//0.1;
	if (keyboard_state[SDL_SCANCODE_RIGHT])
		*angle += 0.01;//0.1;
}

void	print_first_map(t_img_data *img_data, t_vec *player, t_vec *direc, t_wall *walls)
{
	t_wall transfo_wall;
	t_vec transfo_player = {50, 50};
	t_vec transfo_direc = {50, 45};
	(void)player;
	(void)direc;
	int i = 0;
	while (i < 4) // looping through each existing wall
	{
		int tx1 = walls[i].start_wall.x - player->x;
		int ty1 = walls[i].start_wall.y - player->y;

		int tx2 = walls[i].end_wall.x - player->x;
		int ty2 = walls[i].end_wall.y - player->y;

		int tz1 = tx1 * cos(angle) + ty1 * sin(angle);
		int tz2 = tx2 * cos(angle) + ty2 * sin(angle);

		tx1 = tx1 * sin(angle) - ty1 * cos(angle);
		tx2 = tx2 * sin(angle) - ty2 * cos(angle);

		transfo_wall.start_wall.x = 50 - tx1;
		transfo_wall.start_wall.y = 50 - tz1;
		transfo_wall.end_wall.x = 50 - tx2;
		transfo_wall.end_wall.y = 50 - tz2;
		draw_line(&transfo_wall.start_wall, &transfo_wall.end_wall, img_data, 0xFFFFFF);
		i++;
}
	draw_line(&transfo_player, &transfo_direc, img_data, 0xFF0000);
	fill_pix(img_data->img_ptr, &transfo_player, 0xFFFF00, FIRST_MAP_WIDTH);
}

void	print_second_map(t_img_data *img_data, t_vec *player, t_vec *direc, t_wall *walls)
{
	int i;

	i = 0;
	while (i < 4) // looping through each existing wall -> we do the same in print_first_map
	{
		draw_line(&walls[i].start_wall, &walls[i].end_wall, img_data, 0xFFFFFF);
		i++;
	}
	draw_line(player, direc, img_data, 0xFF0000);
	fill_pix(img_data->img_ptr, player, 0xFFFF00, FIRST_MAP_WIDTH);
}

void	main_loop(t_doom *doom)
{
	//int			start_clock;
	//int			delta_clock;
	//int			current_fps;
	//current_fps = 100;

	const Uint8 *keyboard_state;

	SDL_Surface *my_first_map = NULL; // surface for the first map
	SDL_Surface *my_second_map = NULL; // surface for the second map
	t_img_data img_data_firstmap;
	t_img_data img_data_secondmap;

	t_vec vec1 = {50, 20}; // start of "first" wall
	t_vec vec2 = {50, 70}; // end of "first" wall
	t_vec vec3 = {70, 90};
	t_vec vec4 = {90, 20};
	t_wall walls[4] = {{vec1, vec2}, {vec2, vec3}, {vec3, vec4}, {vec4, vec1}};

	//double angle = 0.0; direction angle of player
	t_vecdb playerdb = {70, 70}; // player pos in float
	t_vecdb direcdb; // player direction in float
	t_vec player; // player pos in int
	t_vec direc; // player pos in float

	SDL_Rect myrect_firstmap = {.x=0, .y=0, .w=WIN_WIDTH / 2, .h=WIN_HEIGHT}; // Stretching rectangle to print the map in fullscreen
	SDL_Rect myrect_secondmap = {.x=WIN_WIDTH / 2, .y=0, .w=WIN_WIDTH, .h=WIN_HEIGHT}; // Stretching rectangle to print the map in fullscreen

	/*
		When creating a surface, the last four parameters correspond to the RGBA masks for the created surface. They need to correspond
		to the format of the surface we copy to (the window)
		SDL_ConvertSurface function can be used to adapt the format of a new surface to the format of an other surface (the window in our case)

		NOT FORGET --> if something feels wrong about the colors in the project, it could come from the format of the surfaces, including the
		surface of the window
	*/
	if ((my_first_map = SDL_CreateRGBSurface(0, FIRST_MAP_WIDTH, FIRST_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((my_second_map = SDL_CreateRGBSurface(0, SECOND_MAP_WIDTH, SECOND_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	//my_map = SDL_ConvertSurface(my_map, doom->sdl.surf->format, 0);

	img_data_firstmap.img_ptr = my_first_map->pixels;
	img_data_firstmap.rowsize = FIRST_MAP_WIDTH;

	img_data_secondmap.img_ptr = my_second_map->pixels;
	img_data_secondmap.rowsize = SECOND_MAP_WIDTH;

	doom->data.img_ptr = doom->sdl.surf->pixels;

	t_vec mid_window_top = {FIRST_MAP_WIDTH - 1, 0};
	t_vec mid_window_bottom = {FIRST_MAP_WIDTH - 1, FIRST_MAP_HEIGHT - 1};

	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(doom->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!doom->data.quit)
	{
		ft_bzero(img_data_firstmap.img_ptr, (FIRST_MAP_WIDTH * FIRST_MAP_HEIGHT) * 4);
		ft_bzero(img_data_secondmap.img_ptr, (SECOND_MAP_WIDTH * SECOND_MAP_HEIGHT) * 4);
		draw_line(&mid_window_top, &mid_window_bottom, &img_data_firstmap, 0xFFFFFF);

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

		print_first_map(&img_data_firstmap, &player, &direc, walls);
		//draw_line(&vec1, &vec2, &img_data_firstmap, 0xFFFFFF);
		//draw_line(&player, &direc, &img_data_firstmap, 0xFF0000);
		//fill_pix(img_data_firstmap.img_ptr, &player, 0x55FFFF00, FIRST_MAP_WIDTH);

		print_second_map(&img_data_secondmap, &player, &direc, walls);
		//draw_line(&vec1, &vec2, &img_data_secondmap, 0xFFFFFF);
		//draw_line(&player, &direc, &img_data_secondmap, 0xFF0000);
		//fill_pix(img_data_secondmap.img_ptr, &player, 0x55FFFF00, SECOND_MAP_WIDTH);

		//SDL_UnlockSurface(my_map);
		//write(1, &my_map->pixels[50 + (20 * 100)], 1);
		//SDL_BlitSurface(my_map, NULL, doom->sdl.surf, NULL);

		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &doom->sdl.surf->clip_rect)) < 0)
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, NULL)) < 0)
		if ((SDL_BlitScaled(my_first_map, NULL, doom->sdl.surf, &myrect_firstmap)) < 0)
			printf("BlitScale error = %s\n", SDL_GetError());
		if ((SDL_BlitScaled(my_second_map, NULL, doom->sdl.surf, &myrect_secondmap)) < 0)
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
