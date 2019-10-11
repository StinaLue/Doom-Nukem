/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/11 16:19:01 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include "wolf3d.h"

#include <pthread.h>
#define MAP_WIDTH 9
#define MAP_HEIGHT 9

void	free_sdl(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex)
{
	SDL_DestroyTexture(*tex);
	*tex = NULL;
	SDL_DestroyRenderer(*ren);
	*ren = NULL;
	SDL_DestroyWindow(*win);
	*win = NULL;
	SDL_Quit();
}

int	load_media(SDL_Surface **img, char *path)
{
	*img = SDL_LoadBMP(path);
	if (*img == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	check_line(char *line)
{
	while (*line != '\0')
	{
		if (*line != '0' && *line != '1' && *line != 'X')
			return (*line);
		line++;
	}
	return ('0');
}

void	copy_line(char charline[MAX_MAP], char *line, int width)
{
	int i;

	i = 0;
	while (i < width)
	{
		charline[i] = line[i];
		i++;
	}
}

void	fill_chartab(char chartab[MAX_MAP][MAX_MAP], char *title, int *map_width, int *map_height)
{
	char	*line;
	int		ret;
	int		fd;

	*map_height = 0;
	ret = 0;
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
			close(fd);
			exit(EXIT_FAILURE);
		}
		*map_width = ft_strlen(line);
		if (*map_width > MAX_MAP)
		{
			ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX to %{b}d\n", title, *map_width);
			close(fd);
			exit(EXIT_FAILURE);
		}
		copy_line(chartab[*map_height], line, *map_width);
		//chartab[height] = ft_strdup(line);
		(*map_height)++;
	}
	if (*map_height >= MAX_MAP)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX to %{b}d\n", title, *map_height);
		close(fd);
		exit(EXIT_FAILURE);
	}
}

void	fill_map(int (*map)[MAX_MAP][MAX_MAP], char *title, int *map_width, int *map_height)
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

int	init_sdl_official(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_dprintf(STDERR_FILENO, "SDL_Init Error: %{r}s\n", SDL_GetError());
		return (EXIT_FAILURE);
	}
	*win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, \
			SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (*win == NULL)
	{
		ft_dprintf(STDERR_FILENO, "SDL_CreateWindow Error: %{r}s\n", SDL_GetError());
		return (EXIT_FAILURE);
	}
	*ren = SDL_CreateRenderer(*win, -1, 0);
	*tex = SDL_CreateTexture(*ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
			WIN_WIDTH, WIN_HEIGHT);
	return (EXIT_SUCCESS);
}

int	init_ttf_official(TTF_Font **font)
{
	if (TTF_Init() != 0)
	{
		ft_dprintf(STDERR_FILENO, "TTF_Init Error: %{r}s\n", TTF_GetError());
		return (EXIT_FAILURE);
	}
	*font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 24); //this opens a font style and sets a size
	if (*font == NULL)
	{
		ft_dprintf(STDERR_FILENO, "TTF_OpenFont Error: %{r}s\n", TTF_GetError());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	sdl_init(t_sdl *sdl)
{
	sdl->win = NULL;
	sdl->ren = NULL;
	sdl->tex = NULL;
}

void	ttf_init_struct(t_ttf *ttf)
{
	ttf->font = NULL;
}

void	data_init(t_data *data, char *title)
{
	data->quit = 0;
	//ft_memset(data->pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	data->img_ptr = NULL;
	fill_map(data->map_ptr, title, &(data->map_width), &(data->map_height));
}

void	player_pos(double *x, double *y, int map[MAX_MAP][MAX_MAP], int map_width, int map_height)
{
	int	i;
	int	j;

	i = 0;
	*x = 0;
	*y = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (map[i][j] == 'X')
			{
				*x = j;
				*y = i;
				map[i][j] = 0;
				return ;
			}
			j++;
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "no suitable starting position found for player, exiting...\n");
}

void	player_init(t_player *player, int map[MAX_MAP][MAX_MAP], int map_width, int map_height)
{
	player_pos(&player->x, &player->y, map, map_width, map_height);
	player->x_dir = -1;
	player->y_dir = 0;
	player->x_camera_vector = 0;
	player->y_camera_vector = 0.66;
}

void	raycast_init(t_raycast *raycast, double x, double y)
{
	raycast->pos_x = x;
	raycast->pos_y = y;
}

void	wolf_init(t_wolf *wolf, char *title)
{
	sdl_init(&(wolf->sdl));
	ttf_init_struct(&(wolf->ttf));
	data_init(&(wolf->data), title);
	player_init(&(wolf->player), *(wolf->data.map_ptr), wolf->data.map_width, wolf->data.map_height);
	raycast_init(&(wolf->raycast), wolf->player.x, wolf->player.y);
}

void	fill_pix(int *pixels, int x, int y, int color)
{
	if (x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
		pixels[x + y * WIN_WIDTH] = color;
}

void	draw_vertical(int *pixels, int x, int y1, int y2, int color)
{
	while (y1 < y2)
	{
		fill_pix(pixels, x, y1, color);
		y1++;
	}
}

void	ray_init(t_raycast *raycast, t_dda *dda, t_player const *player, int x)
{
	raycast->cam_x = 2 * x / (double)WIN_WIDTH - 1;

	raycast->pos_x = player->x;
	raycast->pos_y = player->y;

	raycast->dir_x = player->x_dir + player->x_camera_vector * raycast->cam_x;
	raycast->dir_y = player->y_dir + player->y_camera_vector * raycast->cam_x;
	raycast->x = (int)raycast->pos_x;
	raycast->y = (int)raycast->pos_y;

	raycast->height = 0;
	raycast->start_line = 0;
	raycast->end_line = 0;

	/*
	** SEEMS LIKE BOTH OF THE FOLLOWING METHODS WORK
	*/
	if (raycast->dir_x != 0)
		dda->distance_x = ft_absfloat(1 / raycast->dir_x);
	else
		dda->distance_x = ft_absfloat(1 / 0.00001); // MAYBE A BUG, WORKS FOR NOW THO?
	if (raycast->dir_y != 0)
		dda->distance_y = ft_absfloat(1 / raycast->dir_y);
	else
		dda->distance_y = ft_absfloat(1 / 0.00001);
	//dda->distance_x = sqrt(1 + (raycast->dir_y * raycast->dir_y) / (raycast->dir_x * raycast->dir_x));
	//dda->distance_y = sqrt(1 + (raycast->dir_x * raycast->dir_x) / (raycast->dir_y * raycast->dir_y));
	dda->hit = 0;
	dda->side = 0;
}

void	print_map(int map[MAX_MAP][MAX_MAP], int width, int height)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			ft_printf("%d ", map[i][j]);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	dda_init(t_raycast const *raycast, t_dda *dda)
{
	if (raycast->dir_x < 0)
	{
		dda->x_wall_hit = -1;
		dda->distance_x_side = (raycast->pos_x - raycast->x) * dda->distance_x;
	}
	else
	{
		dda->x_wall_hit = 1;
		dda->distance_x_side = (raycast->x + 1 - raycast->pos_x) * dda->distance_x;
	}
	if (raycast->dir_y < 0)
	{
		dda->y_wall_hit = -1;
		dda->distance_y_side = (raycast->pos_y - raycast->y) * dda->distance_y;
	}
	else
	{
		dda->y_wall_hit = 1;
		dda->distance_y_side = (raycast->y + 1 - raycast->pos_y) * dda->distance_y;
	}
}

void	dda_calculation(t_raycast *raycast, t_dda *dda, t_data const *data)
{
	while (dda->hit == 0 && raycast->x < data->map_width && \
			raycast->y < data->map_height && raycast->x > 0 && raycast->y > 0)
	{
		if (dda->distance_x_side < dda->distance_y_side)
		{
			dda->distance_x_side += dda->distance_x;
			raycast->x += dda->x_wall_hit;
			dda->side = 0;
		}
		else
		{
			dda->distance_y_side += dda->distance_y;
			raycast->y += dda->y_wall_hit;
			dda->side = 1;
		}
		//if (data->map[raycast->x][raycast->y] > 0)
		if ((*data->map_ptr)[raycast->y][raycast->x] == 1)
			dda->hit = 1;
	}
}

void	height_calculation(t_raycast *raycast, t_dda *dda)
{
	if (dda->side == 0)
		dda->distance_wall = /*(raycast->dir_x == 0.0) ? 0 : */ft_absfloat((raycast->x -
					raycast->pos_x + (1 - dda->x_wall_hit) / 2) / raycast->dir_x);
	else
		dda->distance_wall = /*(raycast->dir_y == 0.0) ? 0 :*/ft_absfloat((raycast->y -
					raycast->pos_y + (1 - dda->y_wall_hit) / 2) / raycast->dir_y);
	//if (dda->distance_wall != 0)
		raycast->height = ft_absolute((int)(WIN_HEIGHT / dda->distance_wall));
//	else
//		raycast->height = 0;
	raycast->start_line = -raycast->height / 2 + WIN_HEIGHT / 2;
	if (raycast->start_line < 0)
		raycast->start_line = 0;
	raycast->end_line = raycast->height / 2 + WIN_HEIGHT / 2;
	if (raycast->end_line >= WIN_HEIGHT)
		raycast->end_line = WIN_HEIGHT - 1;
}

void	raycasting(t_player const *player, t_raycast *raycast, t_dda *dda, t_data *data, int x)
{
	int	color;

	color = 0;
	ray_init(raycast, dda, player, x);
	dda_init(raycast, dda);
	dda_calculation(raycast, dda, data);
	height_calculation(raycast, dda);
	/*switch(data->map[raycast->x][raycast->y])
	  {
	  case 1:  color = 16711680;  break; //red
	  case 2:  color = 65280;  break; //green
	  case 3:  color = 255;   break; //blue
	  case 4:  color = 16777215;  break; //white
	  default: color = 16776960; break; //yellow
	  }*/
	if ((*data->map_ptr)[raycast->y][raycast->x] == 1)
		color = 230;
	if (dda->side == 1)
		color = color / 2;
	draw_vertical(data->img_ptr, x, raycast->start_line, raycast->end_line, color);
	/*
	**	if (x == 450 || x == 451)
	**	{
	**	ft_printf("cam_x %f color is: %d start_line: %d, end_line: %d and x: %d\n", raycast->cam_x, color, raycast->start_line, raycast->end_line, x);
	**	ft_printf("AND height = %d\n", raycast->height);
	**	}
	*/
}

void	*iterate_raycast(void *param)
{
	t_wolf	*wolf;
	int		x;

	wolf = (t_wolf *)param;
	x = wolf->data.start_thread;
	while (x < wolf->data.end_thread)
	{
		raycasting(&(wolf->player), &(wolf->raycast), &(wolf->dda), &(wolf->data), x);
		x++;
	}
	return (NULL);
}

void	multithread(t_wolf *wolf)
{
	t_wolf		params[NB_THREADS];
	pthread_t	threads[NB_THREADS];
	int			i;

	i = 0;
	while (i < NB_THREADS)
	{
		ft_memcpy((void *)&params[i], (void *)wolf, sizeof(t_wolf));
		params[i].data.start_thread = (WIN_WIDTH / NB_THREADS) * i;
		params[i].data.end_thread = (WIN_WIDTH / NB_THREADS) * (i + 1);
		pthread_create(&threads[i], NULL, iterate_raycast, &params[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
}

void	speed(t_player *player, t_sdl *sdl, t_data *data)
{
	double speed;
	double rotspeed;
	double save_x_dir;
	double save_x_camera_vector;

	speed = 0.1;
	rotspeed = 0.06;
	save_x_dir = player->x_dir;
	save_x_camera_vector = player->x_camera_vector;
	if (sdl->event.key.keysym.sym == SDLK_w)
	{
		if ((*data->map_ptr)[(int)(player->y + player->y_dir * speed)][(int)player->x] == 0)
			player->y += player->y_dir * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x + player->x_dir * speed)] == 0)
			player->x += player->x_dir * speed;
	}
	if (sdl->event.key.keysym.sym == SDLK_s)
	{
		if ((*data->map_ptr)[(int)(player->y - player->y_dir * speed)][(int)player->x] == 0)
			player->y -= player->y_dir * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x - player->x_dir * speed)] == 0)
			player->x -= player->x_dir * speed;
	}
	if (sdl->event.type == SDL_MOUSEMOTION)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		if (sdl->event.motion.xrel > 0)
			rotspeed = -rotspeed;
		player->x_dir = player->x_dir * cos(rotspeed) - player->y_dir * sin(rotspeed);
		player->y_dir = save_x_dir * sin(rotspeed) + player->y_dir * cos(rotspeed);
		player->x_camera_vector = player->x_camera_vector * cos(rotspeed) - player->y_camera_vector * sin(rotspeed);
		player->y_camera_vector = save_x_camera_vector * sin(rotspeed) + player->y_camera_vector * cos(rotspeed);
	}
	if (sdl->event.key.keysym.sym == SDLK_a || sdl->event.key.keysym.sym == SDLK_d)
	{
		if (sdl->event.key.keysym.sym == SDLK_d)
			rotspeed = -rotspeed;
		player->x_dir = player->x_dir * cos(rotspeed) - player->y_dir * sin(rotspeed);
		player->y_dir = save_x_dir * sin(rotspeed) + player->y_dir * cos(rotspeed);
		player->x_camera_vector = player->x_camera_vector * cos(rotspeed) - player->y_camera_vector * sin(rotspeed);
		player->y_camera_vector = save_x_camera_vector * sin(rotspeed) + player->y_camera_vector * cos(rotspeed);
	}
}

int	*create_pixel_tab(void)
{
	int *ptr;

	ptr = NULL;
	if ((ptr = (int *)malloc(sizeof(int) * WIN_WIDTH * WIN_HEIGHT)) == NULL)
		return (NULL);
	ft_memset(ptr, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	return (ptr);
}

void	main_loop(t_wolf *wolf)
{
	int		start_clock;
	int		delta_clock;
	int		current_fps;

	current_fps = 0;
	//int pixels[WIN_WIDTH * WIN_HEIGHT];
	//wolf->data.img_ptr = &pixels[0];
	if ((wolf->data.img_ptr = create_pixel_tab()) == NULL)
		return ; //NOT OKAY YETTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
	TTF_Font *Sans = TTF_OpenFont("/Library/Fonts/Arial.ttf", 24); //this opens a font style and sets a size
	if (!Sans)
		ft_printf("%s\n", TTF_GetError());

	//ft_printf("sans = %p\n", Sans);
SDL_Color Black = {0, 0, 0, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

//SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, "put your text here", Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

//SDL_Texture* Message = SDL_CreateTextureFromSurface(wolf->sdl.ren, surface_message); //now you can convert it into a texture

SDL_Rect Message_rect;//create a rect
Message_rect.x = 0;  //controls the rect's x coordinate
Message_rect.y = 0; // controls the rect's y coordinte
Message_rect.w = 100; // controls the width of the rect
Message_rect.h = 100; // controls the height of the rect

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	//int	leftMouseButtonDown = 0;

	while (!wolf->data.quit)
	{
		//SDL_UpdateTexture(sdl->tex, NULL, data->pixels, WIN_WIDTH * sizeof(int));
		while (SDL_PollEvent(&(wolf->sdl.event)) != 0)
		{
			start_clock = SDL_GetTicks();
			char *fps;

			fps = ft_itoa(current_fps);
			SDL_Surface	*surface_message = TTF_RenderText_Solid(Sans, fps, Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
			free(fps);
			fps = NULL;
			SDL_Texture	*Message = SDL_CreateTextureFromSurface(wolf->sdl.ren, surface_message); //now you can convert it into a texture
			//ft_memset(pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
			ft_memset(wolf->data.img_ptr, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
			//raycasting(player, raycast, dda, data);
			multithread(wolf);
			if (wolf->sdl.event.type == SDL_QUIT || wolf->sdl.event.key.keysym.sym == SDLK_ESCAPE)
				wolf->data.quit = 1;
			/*
			if (sdl->event.type == SDL_MOUSEBUTTONUP)
			if (sdl->event.button.button == SDL_BUTTON_LEFT)
			leftMouseButtonDown = 0;
			if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
			if (sdl->event.button.button == SDL_BUTTON_LEFT)
			leftMouseButtonDown = 1;
			if (sdl->event.type == SDL_MOUSEMOTION)
			if (leftMouseButtonDown)
			draw_vertical(data->pixels, sdl->event.motion.x, sdl->event.motion.y - 100, sdl->event.motion.y + 100, 0);
			//fill_pix(data->pixels, sdl->event.motion.x, sdl->event.motion.y, 0);
			//data->pixels[sdl->event.motion.y * WIN_WIDTH + sdl->event.motion.x] = 0;
			*/
			speed(&(wolf->player), &(wolf->sdl), &(wolf->data));
			//SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
			SDL_UpdateTexture(wolf->sdl.tex, NULL, wolf->data.img_ptr, WIN_WIDTH * sizeof(int));
			SDL_RenderClear(wolf->sdl.ren);
			SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.tex, NULL, NULL);
			SDL_RenderCopy(wolf->sdl.ren, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
			SDL_RenderPresent(wolf->sdl.ren);
			delta_clock = SDL_GetTicks() - start_clock;
			if (delta_clock != 0)
				current_fps = 1000 / delta_clock;
		}
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
	wolf_init(&wolf, argv[1]);
	if (init_sdl_official(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex)) != EXIT_SUCCESS)
	{
		free_sdl(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
		return (EXIT_FAILURE);
	}
	if (init_ttf_official(&(wolf.ttf.font)) != EXIT_SUCCESS)
	{
		free_sdl(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
		return (EXIT_FAILURE);
	}
	//TTF_Init();
	main_loop(&wolf);
	ft_memdel((void *)&wolf.data.img_ptr);
	free_sdl(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
	return (EXIT_SUCCESS);
}
