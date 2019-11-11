/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/11 16:24:36 by afonck           ###   ########.fr       */
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

void	basic_move(t_vecdb *player, double *angle, const Uint8 *keyboard_state)
{
	if (keyboard_state[SDL_SCANCODE_UP])
	{
		player->x += cos(*angle);
		player->y += sin(*angle);
	}
	if (keyboard_state[SDL_SCANCODE_DOWN])
	{
		player->x -= cos(*angle);
		player->y -= sin(*angle);
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
	double angle = 0.0;
	t_vec vec1 = {100, 20};
	t_vec vec2 = {100, 70};
	t_vecdb playerdb = {100, 100};
	t_vecdb direcdb;//= {cos(angle) * 5 + playerdb.x, sin(angle) * 5 + playerdb.y};
	t_vec player;
	t_vec direc;

	//current_fps = 100;
	doom->data.img_ptr = doom->sdl.surf->pixels;
	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(doom->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!doom->data.quit)
	{
		while (SDL_PollEvent(&(doom->sdl.event)) != 0)
			check_quit(&(doom->sdl.event), &(doom->data.quit));
		ft_bzero(doom->data.img_ptr, WIN_WIDTH * WIN_HEIGHT);
		/*if ((SDL_UpdateWindowSurface(doom->sdl.win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n", \
				SDL_GetError());
			return ;
		}*/
		basic_move(&playerdb, &angle, keyboard_state);
		direcdb.x = cos(angle) * 5 + playerdb.x;
		direcdb.y = sin(angle) * 5 + playerdb.y;
		player.x = (int)playerdb.x;
		player.y = (int)playerdb.y;
		direc.x = (int)direcdb.x;
		direc.y = (int)direcdb.y;
		draw_line(&vec1, &vec2, doom->data.img_ptr, 0xFFFFFF);
		draw_line(&player, &direc, doom->data.img_ptr, 0xFF0000);
		fill_pix(doom->data.img_ptr, player.x, player.y, 0xFFFF00);
		if ((SDL_UpdateWindowSurface(doom->sdl.win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n", \
				SDL_GetError());
			return ;
		}
		//if (init_fps_surf(&(doom->ttf), current_fps, &start_clock) == -1)
		//	return ;
		//movement(&(doom->player), &(doom->data), keyboard_state);
		//multithread(doom);
		//if ((blit_and_update(&(doom->ttf.surf_message), &(doom->sdl.surf), \
		//	&(doom->sdl.win))) == -1)
		//	return ;
		//update_fps(&delta_clock, &start_clock, &current_fps, &doom->data.fps);
		//print_map((*doom->data.map_ptr), doom->data.map_height, doom->data.map_width, &doom->player);
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
