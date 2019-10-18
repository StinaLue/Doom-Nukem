/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/18 13:12:49 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

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

void	check_quit(SDL_Event *event, int *quit)
{
	if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && \
		event->key.keysym.sym == SDLK_ESCAPE))
		*quit = 1;
}

void	main_loop(t_wolf *wolf)
{
	int			start_clock;
	int			delta_clock;
	int			current_fps;
	const Uint8 *keyboard_state;

	current_fps = 100;
	wolf->data.img_ptr = wolf->sdl.surf->pixels;
	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(wolf->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!wolf->data.quit)
	{
		while (SDL_PollEvent(&(wolf->sdl.event)) != 0)
			check_quit(&(wolf->sdl.event), &(wolf->data.quit));
		if (init_fps_surf(&(wolf->ttf), current_fps, &start_clock) == -1)
			return ;
		movement(&(wolf->player), &(wolf->data), keyboard_state);
		multithread(wolf);
		if ((blit_and_update(&(wolf->ttf.surf_message), &(wolf->sdl.surf), \
			&(wolf->sdl.win))) == -1)
			return ;
		update_fps(&delta_clock, &start_clock, &current_fps, &wolf->data.fps);
	}
}

int		main(int argc, char *argv[])
{
	t_wolf	wolf;
	int		map[MAX_MAP][MAX_MAP];

	wolf.data.map_ptr = &map;
	if (argc != 2)
		return (argc_error());
	if (MAX_MAP > 100 || WIN_WIDTH > 1920 || WIN_HEIGHT > 1080 || MAX_MAP < 10 \
		|| WIN_WIDTH < 100 || WIN_HEIGHT < 100)
		return (size_error());
	if (NB_THREADS > 10 || NB_THREADS < 1)
		return (nbthreads_error());
	check_title(argv[1]);
	fill_tex(wolf.data.texture);
	init_wolf(&wolf, argv[1]);
	if (init_sdl(&(wolf.sdl.win), &(wolf.sdl.surf)) != EXIT_SUCCESS)
		return (free_sdl_quit(&(wolf.sdl.win)));
	if (init_ttf(&(wolf.ttf)) != EXIT_SUCCESS)
		return (free_sdl_ttf_quit(&(wolf.sdl.win), &(wolf.ttf)));
	main_loop(&wolf);
	free_sdl(&(wolf.sdl.win));
	free_ttf(&(wolf.ttf));
	return (EXIT_SUCCESS);
}
