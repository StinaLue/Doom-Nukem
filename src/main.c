/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/05 17:16:44 by phaydont         ###   ########.fr       */
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

void	draw_editor(SDL_Surface *editor_surf, double offset)
{
	int x = 0;
	int y;
	char point_values[NBPOINTS][2]; // saves all the coordinates (x, y) for the whole grid -> only works without zooming for now
	int i = 0;
	while (x < editor_surf->w - offset)
	{
		x += offset;
		y = 0;
		while (y < editor_surf->h - offset)
		{
			y += offset;
			fill_pix(editor_surf, x, y, 0xFFFFFF);
			if (offset == OFFSET)
			{
				point_values[i][0] = x / offset; // need to put this into struct to keep the values even when zooming
				point_values[i][1] = y / offset;
			}
			i++;
		}
	}
	//printf("x: %d\n", point_values[244][0]);
	//printf("y: %d\n", point_values[244][1]);
}

void editor(SDL_Window **win, SDL_Surface **win_surf, int *editor_flag)
{
	SDL_Surface *editor_surf = NULL;
	SDL_Surface *instruct_surf = NULL;
	SDL_Event event;
	double offset = OFFSET;
	//SDL_Rect editor_rect = {0, WIN_HEIGHT, 0, WIN_WIDTH / 1.5};
	SDL_Rect editor_rect = {0, 0, WIN_WIDTH / 1.5, WIN_HEIGHT};
	SDL_Rect instruct_rect = {WIN_WIDTH / 1.5, 0, WIN_WIDTH - (WIN_WIDTH / 1.5), WIN_HEIGHT};
	if ((editor_surf = SDL_CreateRGBSurface(0, WIN_WIDTH / 1.5, WIN_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	if ((instruct_surf = SDL_CreateRGBSurface(0, WIN_WIDTH - (WIN_WIDTH / 1.5), WIN_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		printf("create surface error = %s\n", SDL_GetError());
	while (*editor_flag == 1)
	{
		ft_bzero(editor_surf->pixels, editor_surf->h * editor_surf->pitch);
		ft_bzero(instruct_surf->pixels, instruct_surf->h * instruct_surf->pitch);
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_e)
					*editor_flag = 0;
				if (event.key.keysym.sym == SDLK_UP && offset < 100 / SIZE)
					offset++;
				else if (event.key.keysym.sym == SDLK_DOWN && offset > 20 / SIZE)
					offset--;
			}
		}
		draw_editor(editor_surf, offset);
		if ((SDL_BlitScaled(editor_surf, NULL, *win_surf, &editor_rect)) < 0)
			ft_dprintf(STDERR_FILENO, "BlitScale error = %s\n", SDL_GetError());

		if ((SDL_BlitScaled(instruct_surf, NULL, *win_surf, &instruct_rect)) < 0)
			ft_dprintf(STDERR_FILENO, "BlitScale error = %s\n", SDL_GetError());

		if ((SDL_UpdateWindowSurface(*win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n",
					   SDL_GetError());
			return;
		}
	}
}

int main_loop(t_doom *doom)
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
	
	myrect_thirdmap = create_sdlrect(0, 0, WIN_WIDTH, WIN_HEIGHT);
	/*
		When creating a surface, the last four parameters correspond to the RGBA masks for the created surface. They need to correspond
		to the format of the surface we copy to (the window)
		SDL_ConvertSurface function can be used to adapt the format of a new surface to the format of an other surface (the window in our case)

		NOT FORGET --> if something feels wrong about the colors in the project, it could come from the format of the surfaces, including the
		surface of the window
	*/
	if ((doom->sdl.rot_mmap = SDL_CreateRGBSurface(0, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((doom->sdl.fixed_mmap = SDL_CreateRGBSurface(0, MINIMAP_WIDTH, MINIMAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	if ((doom->sdl.perspective_mmap = SDL_CreateRGBSurface(0, THIRD_MAP_WIDTH, THIRD_MAP_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		return (error_return("create surface error = %{r}s\n", SDL_GetError()));
	//my_map = SDL_ConvertSurface(my_map, doom->sdl.surf->format, 0);

	keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(doom->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!doom->data.quit)
	{
		ft_bzero(doom->sdl.perspective_mmap->pixels, doom->sdl.perspective_mmap->h * doom->sdl.perspective_mmap->pitch);
		while (SDL_PollEvent(&(doom->sdl.event)) != 0)
			handle_events(&doom->sdl.event, &doom->data);
		if (doom->data.menu_flag)
		{
			if ((menu_loop(&doom->sdl.win, &doom->sdl.win_surf, &doom->data.menu_flag)) == 1)
				doom->data.menu_flag = 0;
		}
		//handle events (for now player movement and HUD activation/deactivation)
		handle_keys(doom, walls, keyboard_state);
		//if (doom->data.editor_flag)
		//	editor(&doom->sdl.win, &doom->sdl.win_surf, &doom->data.editor_flag);
		if (doom->data.hud_flags & COLORFLAG)
			doom->sdl.perspective_mmap->userdata = "yescolor";
		else
			doom->sdl.perspective_mmap->userdata = "nocolor";
		draw_perspective_minimap(doom->sdl.perspective_mmap, &doom->player, walls);
		if ((SDL_BlitScaled(doom->sdl.perspective_mmap, NULL, doom->sdl.win_surf, &myrect_thirdmap)) < 0)
		{
			printf("BlitScale error = %s\n", SDL_GetError());
			free_sdl(&doom->sdl);
			return (1);
		}
		draw_map(&doom->sdl, &doom->player, walls, &doom->data.hud_flags);
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, &doom->sdl.surf->clip_rect)) < 0)
		//if ((SDL_BlitScaled(my_map, NULL, doom->sdl.surf, NULL)) < 0)
		if ((SDL_UpdateWindowSurface(doom->sdl.win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n",
					   SDL_GetError());
			free_sdl(&doom->sdl);
			return (1);
		}
	}
	return (0);
}

int main(/*int argc, char *argv[]*/)
{
	t_doom doom;

	init_doom(&doom);
	if (WIN_WIDTH > 1920 || WIN_HEIGHT > 1080 || WIN_WIDTH < 100 || WIN_HEIGHT < 100)
		return (1);
	if (init_sdl(&(doom.sdl.win), &(doom.sdl.win_surf)) != EXIT_SUCCESS)
		return (free_sdl_quit(&doom.sdl));
	if (TTF_Init() != 0)
	{
		ft_dprintf(STDERR_FILENO, "TTF_Init Error: %{r}s\n", TTF_GetError());
		return (EXIT_FAILURE);
	}
	//return (free_sdl_quit(&(doom.sdl.win)));
	if (main_loop(&doom) == 1)
		ft_dprintf(STDERR_FILENO, "Error during main loop\n");
	TTF_Quit();
	//free_sdl(&(doom.sdl.win));
	free_sdl(&doom.sdl);
	return (EXIT_SUCCESS);
}
