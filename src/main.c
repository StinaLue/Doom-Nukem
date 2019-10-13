/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:57:03 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/13 16:02:58 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include "wolf3d.h"

#include <pthread.h>
#define MAP_WIDTH 9
#define MAP_HEIGHT 9

void	free_SDL(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex)
{
	SDL_DestroyTexture(*tex);
	*tex = NULL;
	SDL_DestroyRenderer(*ren);
	*ren = NULL;
	SDL_DestroyWindow(*win);
	*win = NULL;
	SDL_Quit();
}

void	free_TTF(t_ttf *ttf)
{
	TTF_CloseFont(ttf->font);
	ttf->font = NULL;
	SDL_FreeSurface(ttf->surf_message);
	ttf->surf_message = NULL;
	SDL_DestroyTexture(ttf->message);
	ttf->message = NULL;
	ft_memdel((void **)&ttf->fps);
	TTF_Quit();
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

void	fill_chartab(char chartab[MAX_MAP][MAX_MAP], char *title, int *map_width, int *map_height)
{
	char	*line;
	int	ret;
	int	fd;
	int	w;

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

int	init_SDL(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_dprintf(STDERR_FILENO, "SDL_Init Error: %{r}s\n", SDL_GetError());
		return (EXIT_FAILURE);
	}
	if ((*win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, \
			SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "SDL_CreateWindow Error: %{r}s\n", SDL_GetError());
		return (EXIT_FAILURE);
	}
	if ((*ren = SDL_CreateRenderer(*win, -1, 0/* SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC*/)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "SDL_CreateRenderer Error: %{r}s\n", SDL_GetError());
		return (EXIT_FAILURE);
	}
	if ((*tex = SDL_CreateTexture(*ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
			WIN_WIDTH, WIN_HEIGHT)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "SDL_CreateTexture Error: %{r}s\n", SDL_GetError());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_TTF(t_ttf *ttf)
{
	if (TTF_Init() != 0)
	{
		ft_dprintf(STDERR_FILENO, "TTF_Init Error: %{r}s\n", TTF_GetError());
		return (EXIT_FAILURE);
	}
	if ((ttf->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 24)) == NULL) //this opens a font style and sets a size
	{
		ft_dprintf(STDERR_FILENO, "TTF_OpenFont Error: %{r}s\n", TTF_GetError());
		return (EXIT_FAILURE);
	}
	ttf->color.r = 0;
	ttf->color.g = 0;
	ttf->color.b = 0;
	ttf->color.a = 100;
	ttf->rect.x = 0;
	ttf->rect.y = 0;
	//ttf->rect.w = 100;
	//ttf->rect.h = 100;
	ttf->rect.w = WIN_WIDTH / 8;
	ttf->rect.h = WIN_HEIGHT / 8;
	return (EXIT_SUCCESS);
}

void	init_sdl_struct(t_sdl *sdl)
{
	sdl->win = NULL;
	sdl->ren = NULL;
	sdl->tex = NULL;
}

void	init_ttf_struct(t_ttf *ttf)
{
	ttf->font = NULL;
}

void	init_data_struct(t_data *data, char *title)
{
	data->quit = 0;
	//ft_memset(data->pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	data->img_ptr = NULL;
	fill_map(data->map_ptr, title, &(data->map_width), &(data->map_height));
}

int		find_player_pos(double *x, double *y, int map[MAX_MAP][MAX_MAP], int map_width, int map_height)
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
				return (EXIT_SUCCESS);
			}
			j++;
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "no suitable starting position found for player, exiting...\n");
	return (EXIT_FAILURE);
}

int		init_player_struct(t_player *player, int map[MAX_MAP][MAX_MAP], int map_width, int map_height)
{
	if ((find_player_pos(&player->x, &player->y, map, map_width, map_height)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	player->x_dir = -1;
	player->y_dir = 0;
	player->cam_vector_x = 0;
	player->cam_vector_y = 0.66;
	player->up_and_down = 0;
	player->crouch		= 0;
	return (EXIT_SUCCESS);
}

void	init_raycast_struct(t_raycast *raycast, double x, double y)
{
	raycast->pos_x = x;
	raycast->pos_y = y;
}

void	init_wolf(t_wolf *wolf, char *title)
{
	init_sdl_struct(&(wolf->sdl));
	init_ttf_struct(&(wolf->ttf));
	init_data_struct(&(wolf->data), title);
	if ((init_player_struct(&(wolf->player), *(wolf->data.map_ptr), wolf->data.map_width, wolf->data.map_height)) == EXIT_FAILURE)
	{
		ft_memdel((void **)&wolf->data.img_ptr);
		exit(EXIT_FAILURE);
	}
	init_raycast_struct(&(wolf->raycast), wolf->player.x, wolf->player.y);
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

	raycast->dir_x = player->x_dir + player->cam_vector_x * raycast->cam_x;
	raycast->dir_y = player->y_dir + player->cam_vector_y * raycast->cam_x;
	raycast->map_x = (int)raycast->pos_x;
	raycast->map_y = (int)raycast->pos_y;

	raycast->height = 0;
	raycast->start_line = 0;
	raycast->end_line = 0;

	/*
	** SEEMS LIKE BOTH OF THE FOLLOWING METHODS WORK
	*/
	if (raycast->dir_x != 0)
		dda->dist_x_to_x = ft_absfloat(1 / raycast->dir_x);
	else
		dda->dist_x_to_x = ft_absfloat(1 / 0.00001); // MAYBE A BUG, WORKS FOR NOW THO?
	if (raycast->dir_y != 0)
		dda->dist_y_to_y = ft_absfloat(1 / raycast->dir_y);
	else
		dda->dist_y_to_y = ft_absfloat(1 / 0.00001);
	//dda->dist_x_to_x = sqrt(1 + (raycast->dir_y * raycast->dir_y) / (raycast->dir_x * raycast->dir_x));
	//dda->dist_y_to_y = sqrt(1 + (raycast->dir_x * raycast->dir_x) / (raycast->dir_y * raycast->dir_y));
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
/*
void	dda_init(t_raycast const *raycast, t_dda *dda)
{
	if (raycast->dir_x < 0)
	{
		dda->dir_step_x = -1;
		dda->distance_x_side =  dda->dist_x_to_x * (raycast->pos_x - raycast->map_x);
	}
	else
	{
		dda->dir_step_x = 1;
		dda->distance_x_side = dda->dist_x_to_x * (raycast->map_x + 1 - raycast->pos_x);
	}
	if (raycast->dir_y < 0)
	{
		dda->dir_step_y = -1;
		dda->distance_y_side = dda->dist_y_to_y * (raycast->pos_y - raycast->map_y);
	}
	else
	{
		dda->dir_step_y = 1;
		dda->distance_y_side = dda->dist_y_to_y * (raycast->map_y + 1 - raycast->pos_y);
	}
}*/

void	dda_init(t_raycast const *raycast, t_dda *dda)
{
	dda->dir_step_x = (raycast->dir_x < 0 ? -1 : 1);
	dda->dir_step_y = (raycast->dir_y < 0 ? -1 : 1);
	if (raycast->dir_x < 0)
		dda->distance_x_side = dda->dist_x_to_x * (raycast->pos_x - raycast->map_x);
	else
		dda->distance_x_side = dda->dist_x_to_x * (raycast->map_x + 1 - raycast->pos_x);
	if (raycast->dir_y < 0)
		dda->distance_y_side = dda->dist_y_to_y * (raycast->pos_y - raycast->map_y);
	else
		dda->distance_y_side = dda->dist_y_to_y * (raycast->map_y + 1 - raycast->pos_y);
}

void	dda_calculation(t_raycast *raycast, t_dda *dda, t_data const *data)
{
	while (dda->hit == 0 && raycast->map_x < data->map_width && \
			raycast->map_y < data->map_height && raycast->map_x > 0 && raycast->map_y > 0)
	{
		if (dda->distance_x_side < dda->distance_y_side)
		{
			dda->distance_x_side += dda->dist_x_to_x;
			raycast->map_x += dda->dir_step_x;
			dda->side = 0;
		}
		else
		{
			dda->distance_y_side += dda->dist_y_to_y;
			raycast->map_y += dda->dir_step_y;
			dda->side = 1;
		}
		//if (data->map[raycast->map_x][raycast->map_y] > 0)
		if ((*data->map_ptr)[raycast->map_y][raycast->map_x] == 1)
			dda->hit = 1;
	}
}

void	height_calculation(t_raycast *raycast, t_dda *dda, int updown, double crouch)
{
	if (dda->side == 0)
		dda->distance_wall = /*(raycast->dir_x == 0.0) ? 0 : */ft_absfloat((raycast->map_x -
					raycast->pos_x + (1 - dda->dir_step_x) / 2) / raycast->dir_x);
	else
		dda->distance_wall = /*(raycast->dir_y == 0.0) ? 0 :*/ft_absfloat((raycast->map_y -
					raycast->pos_y + (1 - dda->dir_step_y) / 2) / raycast->dir_y);
	//if (dda->distance_wall != 0)
		raycast->height = ft_absolute((int)(WIN_HEIGHT / dda->distance_wall));
//	else
//		raycast->height = 0;
	raycast->start_line = -raycast->height / 2 + WIN_HEIGHT / 2 + updown - crouch * 1.2;
	raycast->end_line = raycast->height / 2 + WIN_HEIGHT / 2 + updown - crouch;
	if (raycast->start_line < 0)
		raycast->start_line = 0;
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
	height_calculation(raycast, dda, player->up_and_down, player->crouch);
	/*switch(data->map[raycast->map_x][raycast->map_y])
	  {
	  case 1:  color = 16711680;  break; //red
	  case 2:  color = 65280;  break; //green
	  case 3:  color = 255;   break; //blue
	  case 4:  color = 16777215;  break; //white
	  default: color = 16776960; break; //yellow
	  }*/
	if ((*data->map_ptr)[raycast->map_y][raycast->map_x] == 1)
		color = 230;
	if (dda->side == 0 && player->x < raycast->map_x)
		color = 16711680;
	if (dda->side == 1)
	{
		if (player->y < raycast->map_y)
			color = color / 2;
		else
			color = color / 5;
	}
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

void	movement(t_player *player, t_sdl *sdl, t_data *data, const Uint8 *keyboard_state_array)
{
	double speed;
	double rotspeed;
	double save_x_dir;
	double save_cam_vector_x;
	int x = 0;
	int y = 0;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetRelativeMouseState(&x, &y);

	speed = 0.1;
	rotspeed = 0.06;
	save_x_dir = player->x_dir;
	save_cam_vector_x = player->cam_vector_x;
    if (keyboard_state_array[SDL_SCANCODE_UP] || keyboard_state_array[SDL_SCANCODE_W])
    {
		if ((*data->map_ptr)[(int)(player->y + player->y_dir * speed)][(int)player->x] == 0)
			player->y += player->y_dir * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x + player->x_dir * speed)] == 0)
			player->x += player->x_dir * speed;
    }
    if (keyboard_state_array[SDL_SCANCODE_DOWN] || keyboard_state_array[SDL_SCANCODE_S])
    {
		if ((*data->map_ptr)[(int)(player->y - player->y_dir * speed)][(int)player->x] == 0)
			player->y -= player->y_dir * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x - player->x_dir * speed)] == 0)
			player->x -= player->x_dir * speed;
    }
    if (keyboard_state_array[SDL_SCANCODE_D])
    {
		if ((*data->map_ptr)[(int)(player->y + player->cam_vector_y * speed)][(int)player->x] == 0)
			player->y += player->cam_vector_y * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x + player->cam_vector_x * speed)] == 0)
			player->x += player->cam_vector_x * speed;
	}
    if (keyboard_state_array[SDL_SCANCODE_A])
    {
		if ((*data->map_ptr)[(int)(player->y - player->cam_vector_y * speed)][(int)player->x] == 0)
			player->y -= player->cam_vector_y * speed;
		if ((*data->map_ptr)[(int)player->y][(int)(player->x - player->cam_vector_x * speed)] == 0)
			player->x -= player->cam_vector_x * speed;
    }
	if (keyboard_state_array[SDL_SCANCODE_LCTRL])
	{
		if  (player->crouch < 20)
			player->crouch = player->crouch + 4;
	}
	if (!keyboard_state_array[SDL_SCANCODE_LCTRL] && player->crouch > 0)
	{
			player->crouch = player->crouch - 4;
	}
	if (y > 0 && player->up_and_down > MAX_LOOK_DOWN)
	{
		player->up_and_down -= 20;
	}
	if (y < 0 && player->up_and_down < MAX_LOOK_UP)
	{
		player->up_and_down += 20;
	}
    if (keyboard_state_array[SDL_SCANCODE_RIGHT] || keyboard_state_array[SDL_SCANCODE_E] || x > 0)
    {
		rotspeed = -rotspeed;
		player->x_dir = player->x_dir * cos(rotspeed) - player->y_dir * sin(rotspeed);
		player->y_dir = save_x_dir * sin(rotspeed) + player->y_dir * cos(rotspeed);
		player->cam_vector_x = player->cam_vector_x * cos(rotspeed) - player->cam_vector_y * sin(rotspeed);
		player->cam_vector_y = save_cam_vector_x * sin(rotspeed) + player->cam_vector_y * cos(rotspeed);
    }
    if (keyboard_state_array[SDL_SCANCODE_LEFT] || keyboard_state_array[SDL_SCANCODE_Q] || x < 0)
    {
		player->x_dir = player->x_dir * cos(rotspeed) - player->y_dir * sin(rotspeed);
		player->y_dir = save_x_dir * sin(rotspeed) + player->y_dir * cos(rotspeed);
		player->cam_vector_x = player->cam_vector_x * cos(rotspeed) - player->cam_vector_y * sin(rotspeed);
		player->cam_vector_y = save_cam_vector_x * sin(rotspeed) + player->cam_vector_y * cos(rotspeed);
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
	int		current_FPS;

	current_FPS = 0;
	//int pixels[WIN_WIDTH * WIN_HEIGHT];
	//wolf->data.img_ptr = &pixels[0];
	if ((wolf->data.img_ptr = create_pixel_tab()) == NULL)
		return ;

	//int	leftMouseButtonDown = 0;

	while (!wolf->data.quit)
	{
		//SDL_UpdateTexture(sdl->tex, NULL, data->pixels, WIN_WIDTH * sizeof(int));
		while (SDL_PollEvent(&(wolf->sdl.event)) != 0)
		{
			if (wolf->sdl.event.type == SDL_QUIT || (wolf->sdl.event.type == SDL_KEYDOWN && wolf->sdl.event.key.keysym.sym == SDLK_ESCAPE))
				wolf->data.quit = 1;
		}
			start_clock = SDL_GetTicks();
			wolf->ttf.fps = ft_itoa(current_FPS);
			
			if ((wolf->ttf.surf_message = TTF_RenderText_Solid(wolf->ttf.font, wolf->ttf.fps, wolf->ttf.color)) == NULL)
			{
				ft_dprintf(STDERR_FILENO, "TTF_RenderText_Solid error = %{r}s\n", TTF_GetError());
				ft_memdel((void **)&wolf->ttf.fps);
				return ;
			}
			ft_memdel((void **)&wolf->ttf.fps);
			if ((wolf->ttf.message = SDL_CreateTextureFromSurface(wolf->sdl.ren, wolf->ttf.surf_message)) == NULL)
			{
				ft_dprintf(STDERR_FILENO, "SDL_CreateTextureFromSurface error = %{r}s\n", SDL_GetError());
				return ;
			}
		SDL_FreeSurface(wolf->ttf.surf_message);
		wolf->ttf.surf_message = NULL;
		//ft_memset(pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
		ft_memset(wolf->data.img_ptr, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
		//raycasting(player, raycast, dda, data);
		multithread(wolf);
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		movement(&(wolf->player), &(wolf->sdl), &(wolf->data), keyboard_state_array);
		//SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
		SDL_UpdateTexture(wolf->sdl.tex, NULL, wolf->data.img_ptr, WIN_WIDTH * sizeof(int));
		SDL_RenderClear(wolf->sdl.ren);
		SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.tex, NULL, NULL);
		SDL_RenderCopy(wolf->sdl.ren, wolf->ttf.message, NULL, &wolf->ttf.rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
		SDL_RenderPresent(wolf->sdl.ren);
		delta_clock = SDL_GetTicks() - start_clock;
		if (delta_clock != 0)
			current_FPS = 1000 / delta_clock;
		SDL_DestroyTexture(wolf->ttf.message);
		//printf("%s\n", SDL_GetError());
		wolf->ttf.message = NULL;
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
	init_wolf(&wolf, argv[1]);
	if (init_SDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex)) != EXIT_SUCCESS)
	{
		free_SDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
		return (EXIT_FAILURE);
	}
	if (init_TTF(&(wolf.ttf)) != EXIT_SUCCESS)
	{
		free_SDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
		free_TTF(&(wolf.ttf));
		return (EXIT_FAILURE);
	}
	main_loop(&wolf);
	ft_memdel((void *)&wolf.data.img_ptr);
	free_SDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
	free_TTF(&(wolf.ttf));
	return (EXIT_SUCCESS);
}
