/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/21 19:12:27 by sluetzen         ###   ########.fr       */
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
	if (player->x < 0 || player->x >= ROT_MAP_WIDTH)
		return (0);
	if (player->y < 0 || player->y >= ROT_MAP_HEIGHT)
		return (0);
	return (1);
}

int		check_side_wall(double pos_x, double pos_y, t_vecdb start_wall, t_vecdb end_wall)
{
	double det = (start_wall.x - end_wall.x) * (start_wall.y - pos_y) - (start_wall.x - pos_x) * (start_wall.y - end_wall.y);
	if (det > -20.0) // the lower this number, the bigger the distance between player and collision will be
		return (1);
	else
		return (0);
}

int 	check_collision(double pos_x, double pos_y, t_wall *walls)
{
	int i;
	i = 0;
	while(i < NB_WALLS)//loop through each wall
	{
		if (check_side_wall(pos_x, pos_y, walls[i].start_wall, walls[i].end_wall))
			return (1);
		i++;
	}
	return (0);
}

void	basic_move(t_player *player, t_wall *walls, const Uint8 *keyboard_state)
{
	double pos_x = player->pos.x;
	double pos_y = player->pos.y;
	if (!is_in_map(&player->pos))
	{
		player->pos.x = 70;
		player->pos.y = 70;
	}
	if (keyboard_state[SDL_SCANCODE_UP])
	{
		player->pos.x += cos(player->angle) / 10; // == speed reduction
		player->pos.y += sin(player->angle) / 10;
		if (check_collision(player->pos.x, player->pos.y, walls))
		{
			player->pos.x = pos_x;
			player->pos.y = pos_y;
		}
	}
	if (keyboard_state[SDL_SCANCODE_DOWN])
	{
		player->pos.x -= cos(player->angle) / 10;
		player->pos.y -= sin(player->angle) / 10;
		if (check_collision(player->pos.x, player->pos.y, walls))
		{
			player->pos.x = pos_x;
			player->pos.y = pos_y;
		}
	}
	if (keyboard_state[SDL_SCANCODE_LEFT])
		player->angle -= 0.01;
	if (keyboard_state[SDL_SCANCODE_RIGHT])
		player->angle += 0.01;
	player->direc.x = cos(player->angle) * 5 + player->pos.x;
	player->direc.y = sin(player->angle) * 5 + player->pos.y;
}

void	main_loop(t_doom *doom)
{
	const Uint8 *keyboard_state;

	t_vecdb vec1 = {50, 20}; // start of "first" wall
	t_vecdb vec2 = {50, 70}; // end of "first" wall
	t_vecdb vec3 = {70, 90};
	t_vecdb vec4 = {90, 20};
	t_wall walls[NB_WALLS] = {{vec1, vec2, 0xFF0000}, {vec2, vec3, 0x00FF00}, {vec3, vec4, 0x0000FF}, {vec4, vec1, 0x00FFFF}};
	//t_wall walls[NB_WALLS] = {{vec1, vec2, 0xFF0000}};

	if (parse_everything(walls) != 0)
	{
		printf("parsing error\n");
	}

	//double angle = 0.0; direction angle of player

	SDL_Rect myrect_firstmap = {.x=0, .y=0, .w=(WIN_WIDTH / 8), .h=WIN_HEIGHT / 4}; // Stretching rectangle to print the map in fullscreen
	SDL_Rect myrect_secondmap = {.x=(WIN_WIDTH / 8), .y=0, .w=(WIN_WIDTH / 8), .h=WIN_HEIGHT / 4}; // Stretching rectangle to print the map in fullscreen
	SDL_Rect myrect_thirdmap = {.x=0, .y=0, .w=WIN_WIDTH, .h=WIN_HEIGHT}; // Stretching rectangle to print the map in fullscreen
	/*
		When creating a surface, the last four parameters correspond to the RGBA masks for the created surface. They need to correspond
		to the format of the surface we copy to (the window)
		SDL_ConvertSurface function can be used to adapt the format of a new surface to the format of an other surface (the window in our case)

		NOT FORGET --> if something feels wrong about the colors in the project, it could come from the format of the surfaces, including the
		surface of the window
	*/
	if ((doom->sdl.rot_mmap = SDL_CreateRGBSurface(0, ROT_MAP_WIDTH, ROT_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((doom->sdl.fixed_mmap = SDL_CreateRGBSurface(0, FIXED_MAP_WIDTH, FIXED_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((doom->sdl.perspective_mmap = SDL_CreateRGBSurface(0, THIRD_MAP_WIDTH, THIRD_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	//my_map = SDL_ConvertSurface(my_map, doom->sdl.surf->format, 0);

	t_vec bottomleft_leftmap = {0, ROT_MAP_HEIGHT - 1};
	t_vec bottomleft_rightmap = {0, FIXED_MAP_HEIGHT - 1};
	t_vec bottomright_leftmap = {ROT_MAP_WIDTH - 1, ROT_MAP_HEIGHT - 1};
	t_vec bottomright_rightmap = {FIXED_MAP_WIDTH - 1, FIXED_MAP_HEIGHT - 1};
	t_vec topleft_leftmap = {0, 0};
	t_vec topleft_rightmap = {0, 0};
	t_vec topright_leftmap = {ROT_MAP_WIDTH - 1, 0};
	t_vec topright_rightmap = {FIXED_MAP_WIDTH - 1, 0};

	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(doom->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!doom->data.quit)
	{
		ft_bzero(doom->sdl.rot_mmap->pixels, doom->sdl.rot_mmap->h * doom->sdl.rot_mmap->pitch);
		ft_bzero(doom->sdl.fixed_mmap->pixels, doom->sdl.fixed_mmap->h * doom->sdl.fixed_mmap->pitch);
		ft_bzero(doom->sdl.perspective_mmap->pixels, doom->sdl.perspective_mmap->h * doom->sdl.perspective_mmap->pitch);
		while (SDL_PollEvent(&(doom->sdl.event)) != 0)
			check_quit(&(doom->sdl.event), &(doom->data.quit));

		//move the player and assign his new position, need float and then int converting because of angle calculation
		basic_move(&doom->player, walls, keyboard_state);

		draw_perspective_minimap(doom->sdl.perspective_mmap, &doom->player, walls);
		draw_fixed_minimap(doom->sdl.fixed_mmap, &doom->player, walls);
		draw_rot_minimap(doom->sdl.rot_mmap, &doom->player, walls);
		draw_line(topleft_leftmap, topright_leftmap, doom->sdl.rot_mmap, 0xFFFFFF);
		draw_line(topleft_rightmap, topright_rightmap, doom->sdl.fixed_mmap, 0xFFFFFF);
		draw_line(bottomleft_leftmap, bottomright_leftmap, doom->sdl.rot_mmap, 0xFFFFFF);
		draw_line(bottomleft_rightmap, bottomright_rightmap, doom->sdl.fixed_mmap, 0xFFFFFF);
		draw_line(topleft_leftmap, bottomleft_leftmap, doom->sdl.rot_mmap, 0xFFFFFF);
		draw_line(topleft_rightmap, bottomleft_rightmap, doom->sdl.fixed_mmap, 0xFFFFFF);
		draw_line(topright_rightmap, bottomright_rightmap, doom->sdl.fixed_mmap, 0xFFFFFF);

		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &doom->sdl.surf->clip_rect)) < 0)
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, NULL)) < 0)
		if ((SDL_BlitScaled(doom->sdl.perspective_mmap, NULL, doom->sdl.win_surf, &myrect_thirdmap)) < 0)
			printf("BlitScale error = %s\n", SDL_GetError());
		if ((SDL_BlitScaled(doom->sdl.rot_mmap, NULL, doom->sdl.win_surf, &myrect_firstmap)) < 0)
			printf("BlitScale error = %s\n", SDL_GetError());
		if ((SDL_BlitScaled(doom->sdl.fixed_mmap, NULL, doom->sdl.win_surf, &myrect_secondmap)) < 0)
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
