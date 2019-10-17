/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/17 14:22:43 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

char	check_line(char *line)
{
	if (*line == '\0')
		return ('\0');
	while (*line != '\0')
	{
		if (*line != '0' && *line != '1' && *line != 'X')
			return (*line);
		line++;
	}
	return ('0');
}

/*
**	Checks which values the map has.
**	1 = wall, 0 = walkable space, X = position of player
*/

void	copy_line(char *charline, char *line, int width)
{
	int i;

	i = 0;
	while (i < width)
	{
		charline[i] = line[i];
		i++;
	}
}

void	fill_chartab(char chartab[MAX_MAP][MAX_MAP], char *title,
						int *map_width, int *map_height)
{
	char	*line;
	int		ret;
	int		fd;
	int		w;

	*map_height = 0;
	ret = 0;
	w = 0;
	if ((fd = open(title, O_RDONLY | O_NOFOLLOW)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s could not be opened\n", title);
		exit(EXIT_FAILURE);
	}
	while ((ret = get_next_line(fd, &line)) > 0 && *map_height < MAX_MAP)
	{
		if (check_line(line) != '0')
		{
			ft_dprintf(STDERR_FILENO, "invalid character %{r}c in map\n", check_line(line));
			ft_memdel((void **)&line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		if (*map_height == 0)
			w = ft_strlen(line);
		*map_width = ft_strlen(line);
		if (*map_width != w)
		{
			ft_dprintf(STDERR_FILENO, "%{r}s is an uneven map, only rectangles or squares are allowed\n", title);
			ft_memdel((void **)&line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		if (*map_width > MAX_MAP)
		{
			ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX to %{b}d\n", title, *map_width);
			ft_memdel((void **)&line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		copy_line(chartab[*map_height], line, *map_width);
		ft_memdel((void **)&line);
		(*map_height)++;
	}
	ft_memdel((void **)&line);
	close(fd);
	if (*map_height >= MAX_MAP)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX to %{b}d\n", title, *map_height);
		exit(EXIT_FAILURE);
	}
}

/*
**	Parsing the input file
*/

void	fill_map(int (*map)[MAX_MAP][MAX_MAP], char *title,
					int *map_width, int *map_height)
{
	char	chartab[MAX_MAP][MAX_MAP];
	int		i;
	int		j;

	i = 0;
	fill_chartab(chartab, title, map_width, map_height);
	while (i < *map_height)
	{
		j = 0;
		while (j < *map_width)
		{
			if (chartab[i][j] == 'X')
				(*map)[i][j] = 'X';
			else
				(*map)[i][j] = chartab[i][j] - '0';
			j++;
		}
		i++;
	}
}

void	verify_bordermap(int const (*map)[MAX_MAP][MAX_MAP],
						char *title, int map_width, int map_height)
{
	int i;
	int j;
	int k;
	int l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	while ((*map)[0][i] == 1 && i < map_width)
		i++;
	while ((*map)[map_height - 1][j] == 1 && j < map_width)
		j++;
	while ((*map)[k][0] == 1 && k < map_height)
		k++;
	while ((*map)[l][map_width - 1] == 1 && l < map_height)
		l++;
	if (i != map_width || j != map_width || k != map_height || l != map_height)
	{
		ft_dprintf(STDERR_FILENO, "map %{r}s is not surrounded by walls (1), exiting...\n", title);
		exit(EXIT_FAILURE);
	}
}

/*
**	Verify that the map is surrounded by walls (1)
*/

void	find_player_pos(t_player *player, int map[MAX_MAP][MAX_MAP],
						int map_width, int map_height)
{
	int	i;
	int	j;

	i = 0;
	player->x = 0;
	player->y = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (map[i][j] == 'X')
			{
				player->x = j + 0.000001;
				player->y = i + 0.000001;
				map[i][j] = 0;
				return ;
			}
			j++;
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "no suitable starting position found for player, exiting...\n");
	exit(EXIT_FAILURE);
}

/*
**	Function that searches for the player (X) in the map.
*/

void	fill_pix(Uint32 *pixels, int x, int y, int color)
{
	if (x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
		pixels[x + y * WIN_WIDTH] = color;
}

void	draw_vertical(Uint32 *pixels, int x, int y1, int y2, int color)
{
	while (y1 < y2)
	{
		fill_pix(pixels, x, y1, color);
		y1++;
	}
}

void	print_map(int map[MAX_MAP][MAX_MAP], int width,
					int height, t_player *player)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if ((int)player->x == j && (int)player->y == i)
				ft_printf(". ");
			else
				ft_printf("%d ", map[i][j]);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	main_loop(t_wolf *wolf)
{
	int		start_clock;
	int		delta_clock;
	int		current_fps;
	char	test_fps[4];

	current_fps = 0;
	wolf->data.img_ptr = wolf->sdl.surf->pixels;
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_WarpMouseInWindow(wolf->sdl.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	while (!wolf->data.quit)
	{
		while (SDL_PollEvent(&(wolf->sdl.event)) != 0)
		{
			if (wolf->sdl.event.type == SDL_QUIT || (wolf->sdl.event.type == SDL_KEYDOWN && wolf->sdl.event.key.keysym.sym == SDLK_ESCAPE))
				wolf->data.quit = 1;
		}
		start_clock = SDL_GetTicks();
		test_fps[3] = '\0';
		test_fps[2] = (current_fps % 10) + '0';
		current_fps /= 10;
		test_fps[1] = (current_fps % 10) + '0';
		current_fps /= 10;
		test_fps[0] = (current_fps % 10) + '0';
		wolf->ttf.fps = &test_fps[0];//ft_itoa(current_fps);
		
		if ((wolf->ttf.surf_message = TTF_RenderText_Solid(wolf->ttf.font, wolf->ttf.fps, wolf->ttf.color)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, "TTF_RenderText_Solid error = %{r}s\n", TTF_GetError());
			return ;
		}
		movement(&(wolf->player), &(wolf->data), keyboard_state);
		multithread(wolf);
		if ((SDL_BlitSurface(wolf->ttf.surf_message, NULL, wolf->sdl.surf, NULL)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_BlitSurface error = %{r}s\n", SDL_GetError());
			return ;
		}
		SDL_FreeSurface(wolf->ttf.surf_message);
		wolf->ttf.surf_message = NULL;
		if ((SDL_UpdateWindowSurface(wolf->sdl.win)) < 0)
		{
			ft_dprintf(STDERR_FILENO, "SDL_UpdateWindowSurface error = %{r}s\n", SDL_GetError());
			return ;
		}
		delta_clock = SDL_GetTicks() - start_clock;
		if (delta_clock != 0)
			current_fps = 1000 / delta_clock;
	}
}

int	main(int argc, char *argv[])
{
	t_wolf	wolf;
	int		map[MAX_MAP][MAX_MAP];

	wolf.data.map_ptr = &map;
	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "usage: ./wolf3d %{g}s\n", "[valid .w3d map]");
		return (EXIT_FAILURE);
	}
	if (MAX_MAP > 100 || WIN_WIDTH > 1920 || WIN_HEIGHT > 1080 || MAX_MAP < 10 || WIN_WIDTH < 100 || WIN_HEIGHT < 100)
	{
		ft_dprintf(STDERR_FILENO, "max/min size of map = %{b}s, you chose %{r}d / max/min screen size = %{b}s, you chose %{r}d x %{r}d\n", "100/10", MAX_MAP, "1920 x 1080/100 x 100", WIN_WIDTH, WIN_HEIGHT);
		return (EXIT_FAILURE);
	}
	if (NB_THREADS > 50 || NB_THREADS < 1)
	{
		ft_printf("max nb of threads = %{r}s, you chose %{r}d\n", "50", NB_THREADS);
		return (EXIT_FAILURE);
	}
	fill_tex(wolf.data.texture);
	init_wolf(&wolf, argv[1]);
	if (init_sdl(&(wolf.sdl.win), &(wolf.sdl.surf)) != EXIT_SUCCESS)
	{
		free_sdl(&(wolf.sdl.win));
		return (EXIT_FAILURE);
	}
	if (init_ttf(&(wolf.ttf)) != EXIT_SUCCESS)
	{
		free_sdl(&(wolf.sdl.win));
		free_ttf(&(wolf.ttf));
		return (EXIT_FAILURE);
	}
	main_loop(&wolf);
	free_sdl(&(wolf.sdl.win));
	free_ttf(&(wolf.ttf));
	return (EXIT_SUCCESS);
}
