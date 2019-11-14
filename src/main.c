/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/14 15:44:06 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

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
		player->x += cos(*angle) / 10; // == speed reduction
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

void	print_first_map(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	t_wall transfo_wall;
	t_vec transfo_player = {50, 50};
	t_vec transfo_direc = {50, 45};
	int i = 0;
	while (i < NB_WALLS) // looping through each existing wall
	{
		int tx1 = walls[i].start_wall.x - player->pos.x;
		int ty1 = walls[i].start_wall.y - player->pos.y;

		int tx2 = walls[i].end_wall.x - player->pos.x;
		int ty2 = walls[i].end_wall.y - player->pos.y;

		int tz1 = tx1 * cos(player->angle) + ty1 * sin(player->angle);
		int tz2 = tx2 * cos(player->angle) + ty2 * sin(player->angle);

		tx1 = tx1 * sin(player->angle) - ty1 * cos(player->angle);
		tx2 = tx2 * sin(player->angle) - ty2 * cos(player->angle);

		transfo_wall.start_wall.x = 50 - tx1;
		transfo_wall.start_wall.y = 50 - tz1;
		transfo_wall.end_wall.x = 50 - tx2;
		transfo_wall.end_wall.y = 50 - tz2;
		draw_line(&transfo_wall.start_wall, &transfo_wall.end_wall, surf, 0xFFFFFF);
		i++;
	}
	draw_line(&transfo_player, &transfo_direc, surf, 0xFF0000);
	fill_pix(surf, transfo_player.x, transfo_player.y, 0xFFFF00);
}

void	print_second_map(SDL_Surface *surf, t_player *player, t_wall *walls)
{
	int i;

	i = 0;
	while (i < NB_WALLS) // looping through each existing wall -> we do the same in print_first_map
	{
		draw_line(&walls[i].start_wall, &walls[i].end_wall, surf, 0xFFFFFF);
		i++;
	}
	draw_line(&player->pos, &player->direc, surf, 0xFF0000);
	fill_pix(surf, player->pos.x, player->pos.y, 0xFFFF00);
}

void	main_loop(t_doom *doom)
{
	const Uint8 *keyboard_state;

	t_vec vec1 = {50, 20}; // start of "first" wall
	t_vec vec2 = {50, 70}; // end of "first" wall
	t_vec vec3 = {70, 90};
	t_vec vec4 = {90, 20};
	t_wall walls[NB_WALLS] = {{vec1, vec2}, {vec2, vec3}, {vec3, vec4}, {vec4, vec1}};

	//double angle = 0.0; direction angle of player
	t_vecdb playerdb = {70, 70}; // player pos in float
	t_vecdb direcdb; // player direction in float

	SDL_Rect myrect_firstmap = {.x=0, .y=0, .w=WIN_WIDTH / 2, .h=WIN_HEIGHT}; // Stretching rectangle to print the map in fullscreen
	SDL_Rect myrect_secondmap = {.x=WIN_WIDTH / 2, .y=0, .w=WIN_WIDTH, .h=WIN_HEIGHT}; // Stretching rectangle to print the map in fullscreen

	/*
		When creating a surface, the last four parameters correspond to the RGBA masks for the created surface. They need to correspond
		to the format of the surface we copy to (the window)
		SDL_ConvertSurface function can be used to adapt the format of a new surface to the format of an other surface (the window in our case)

		NOT FORGET --> if something feels wrong about the colors in the project, it could come from the format of the surfaces, including the
		surface of the window
	*/
	if ((doom->sdl.first_map = SDL_CreateRGBSurface(0, FIRST_MAP_WIDTH, FIRST_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((doom->sdl.second_map = SDL_CreateRGBSurface(0, SECOND_MAP_WIDTH, SECOND_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	//my_map = SDL_ConvertSurface(my_map, doom->sdl.surf->format, 0);

	t_vec mid_window_top = {FIRST_MAP_WIDTH - 1, 0};
	t_vec mid_window_bottom = {FIRST_MAP_WIDTH - 1, FIRST_MAP_HEIGHT - 1};

	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(doom->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!doom->data.quit)
	{
		ft_bzero(doom->sdl.first_map->pixels, doom->sdl.first_map->h * doom->sdl.first_map->pitch);
		ft_bzero(doom->sdl.second_map->pixels, doom->sdl.second_map->h * doom->sdl.second_map->pitch);
		draw_line(&mid_window_top, &mid_window_bottom, doom->sdl.first_map, 0xFFFFFF);

		while (SDL_PollEvent(&(doom->sdl.event)) != 0)
			check_quit(&(doom->sdl.event), &(doom->data.quit));

		//move the player and assign his new position, need float and then int converting because of angle calculation
		basic_move(&playerdb, &doom->player.angle, keyboard_state);
		direcdb.x = cos(doom->player.angle) * 5 + playerdb.x;
		direcdb.y = sin(doom->player.angle) * 5 + playerdb.y;
		doom->player.pos.x = (int)playerdb.x;
		doom->player.pos.y = (int)playerdb.y;
		doom->player.direc.x = (int)direcdb.x;
		doom->player.direc.y = (int)direcdb.y;


		print_first_map(doom->sdl.first_map, &doom->player, walls);

		print_second_map(doom->sdl.second_map, &doom->player, walls);

		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &doom->sdl.surf->clip_rect)) < 0)
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, NULL)) < 0)
		if ((SDL_BlitScaled(doom->sdl.first_map, NULL, doom->sdl.win_surf, &myrect_firstmap)) < 0)
			printf("BlitScale error = %s\n", SDL_GetError());
		if ((SDL_BlitScaled(doom->sdl.second_map, NULL, doom->sdl.win_surf, &myrect_secondmap)) < 0)
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

	init_doom(&doom);
	if (WIN_WIDTH > 1920 || WIN_HEIGHT > 1080 || WIN_WIDTH < 100 || WIN_HEIGHT < 100)
		return (1);
	if (init_sdl(&(doom.sdl.win), &(doom.sdl.win_surf)) != EXIT_SUCCESS)
		return (free_sdl_quit(&(doom.sdl.win)));
	main_loop(&doom);
	free_sdl(&(doom.sdl.win));
	return (EXIT_SUCCESS);
}
