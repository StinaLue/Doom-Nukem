#include "libft.h"
#include <math.h>
#include "wolf3d.h"

#include <pthread.h>

//#define mapWidth 24
//#define mapHeight 24

#define mapWidth 9
#define mapHeight 9
/*
   int worldMap[mapWidth][mapHeight]=
   {
   {1,1,1,1,1},
   {1,0,0,0,1},
   {1,0,0,0,1},
   {1,0,0,0,1},
   {1,3,0,0,1},
   {1,0,2,0,1},
   {1,0,0,0,1},
   {1,1,1,1,1}
   };
 */
/*
   int worldMap[mapWidth][mapHeight]=
   {
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
   };
 */

void	freeSDL(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex)
{
	SDL_DestroyTexture(*tex);
	*tex = NULL;
	SDL_DestroyRenderer(*ren);
	*ren = NULL;
	SDL_DestroyWindow(*win);
	*win = NULL;
	SDL_Quit();
}

int	loadMedia(SDL_Surface **img, char *path)
{
	*img = SDL_LoadBMP(path);
	if (*img == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	checkLine(char *line)
{
	while (*line != '\0')
	{
		if (*line != '0' && *line != '1' && *line != 'X')
			return (*line);
		line++;
	}
	return ('0');
}

void	copyLine(char charline[MAX_MAP], char *line, int width)
{
	int i;

	i = 0;
	while (i < width)
	{
		charline[i] = line[i];
		i++;
	}
}

void	fillChartab(char chartab[MAX_MAP][MAX_MAP], char *title, int *widthMap, int *heightMap)
{
	char	*line;
	int	ret;
	int	fd;

	*heightMap = 0;
	ret = 0;
	if ((fd = open(title, O_RDONLY | O_NOFOLLOW)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s could not be opened\n", title);
		exit(EXIT_FAILURE);
	}
	while ((ret = get_next_line(fd, &line)) > 0 && *heightMap < MAX_MAP)
	{
		if (checkLine(line) != '0')
		{
			ft_dprintf(STDERR_FILENO, "invalid character %{r}c in map\n", checkLine(line));
			close(fd);
			exit(EXIT_FAILURE);
		}
		*widthMap = ft_strlen(line);
		if (*widthMap > MAX_MAP)
		{
			ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX to %{b}d\n", title, *widthMap);
			close(fd);
			exit(EXIT_FAILURE);
		}
		copyLine(chartab[*heightMap], line, *widthMap);
		//chartab[lineHeight] = ft_strdup(line);
		(*heightMap)++;
	}
	if (*heightMap >= MAX_MAP)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX to %{b}d\n", title, *heightMap);
		close(fd);
		exit(EXIT_FAILURE);
	}
}

void	fillMap(int map[MAX_MAP][MAX_MAP], char *title, int *widthMap, int *heightMap)
{
	char 	chartab[MAX_MAP][MAX_MAP];
	int	i;
	int	j;

	i = 0;
	fillChartab(chartab, title, widthMap, heightMap);
	while (i < *heightMap)
	{
		j = 0;
		while (j < *widthMap)
		{
			if (chartab[i][j] == 'X')
				map[i][j] = 88;
			else
				map[i][j] = chartab[i][j] - '0';
			j++;
		}
		i++;
	}
}

int	initSDL(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex)
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

void	initSdlStruct(t_sdl *sdl)
{
	sdl->win = NULL;
	sdl->ren = NULL;
	sdl->tex = NULL;
}

void	initDataStruct(t_data *data, char *title)
{
	data->quit = 0;
	//ft_memset(data->pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	data->img_ptr = NULL;
	fillMap(data->map, title, &(data->widthMap), &(data->heightMap));
}

void	findPlayerPos(double *posX, double *posY, int map[MAX_MAP][MAX_MAP], int widthMap, int heightMap)
{
	int	i;
	int	j;

	i = 0;
	*posX = 0;
	*posY = 0;
	while (i < heightMap)
	{
		j = 0;
		while (j < widthMap)
		{
			if (map[i][j] == 88)
			{
				*posX = j;// + 0.5;
				*posY = i;// + 0.5;
				map[i][j] = 0;
				return;
			}
			j++;
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "no suitable starting position found for player, exiting...\n");
}

void	initPlayerStruct(t_player *player, int map[MAX_MAP][MAX_MAP], int widthMap, int heightMap)
{
	findPlayerPos(&player->posX, &player->posY, map, widthMap, heightMap);
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;
}

void	initRaycastStruct(t_raycast *raycast, double posX, double posY)
{
	raycast->rayPosX = posX;
	raycast->rayPosY = posY;
}

void	initWolf(t_wolf *wolf, char *title)
{
	initSdlStruct(&(wolf->sdl));
	initDataStruct(&(wolf->data), title);
	initPlayerStruct(&(wolf->player), wolf->data.map, wolf->data.widthMap, wolf->data.heightMap);
	initRaycastStruct(&(wolf->raycast), wolf->player.posX, wolf->player.posY);
}

void	fillPix(int *pixels, int x, int y, int color)
{
	if (x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
		pixels[x + y * WIN_WIDTH] = color;
}

void	drawVertical(int *pixels, int x, int y1, int y2, int color)
{
	while (y1 < y2)
	{
		fillPix(pixels, x, y1, color);
		y1++;
	}
}

void	rayInit(t_raycast *raycast, t_dda *dda, t_player const *player, int x)
{
	raycast->camX = 2 * x / (double)WIN_WIDTH - 1;

	raycast->rayPosX = player->posX;
	raycast->rayPosY = player->posY;

	raycast->rayDirX = player->dirX + player->planeX * raycast->camX;
	raycast->rayDirY = player->dirY + player->planeY * raycast->camX;
	raycast->mapX = (int)raycast->rayPosX;
	raycast->mapY = (int)raycast->rayPosY;

	raycast->lineHeight = 0;
	raycast->drawStart = 0;
	raycast->drawEnd = 0;

	/*
	   SEEMS LIKE BOTH OF THE FOLLOWING METHODS WORK
	 */
	//dda->deltaDistX = ft_absfloat(1 / raycast->rayDirX);
	//dda->deltaDistY = ft_absfloat(1 / raycast->rayDirY);
	dda->deltaDistX = sqrt(1 + (raycast->rayDirY * raycast->rayDirY) / (raycast->rayDirX * raycast->rayDirX));
	dda->deltaDistY = sqrt(1 + (raycast->rayDirX * raycast->rayDirX) / (raycast->rayDirY * raycast->rayDirY));
	dda->hit = 0;
	dda->side = 0;
}

void	printMap(int map[MAX_MAP][MAX_MAP], int width, int height)
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

void	ddaInit(t_raycast const *raycast, t_dda *dda)
{
	if (raycast->rayDirX < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (raycast->rayPosX - raycast->mapX) * dda->deltaDistX;
	}
	else
	{
		dda->stepX = 1;
		dda->sideDistX = (raycast->mapX + 1.0 - raycast->rayPosX) * dda->deltaDistX;
	}
	if (raycast->rayDirY < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (raycast->rayPosY - raycast->mapY) * dda->deltaDistY;
	}
	else
	{
		dda->stepY = 1;
		dda->sideDistY = (raycast->mapY + 1.0 - raycast->rayPosY) * dda->deltaDistY;
	}
}

void	ddaLoop(t_raycast *raycast, t_dda *dda, t_data const *data)
{
	while (dda->hit == 0 && raycast->mapX < data->widthMap && \
			raycast->mapY < data->heightMap && raycast->mapX > 0 && raycast->mapY > 0)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			raycast->mapX += dda->stepX;
			dda->side = 0;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			raycast->mapY += dda->stepY;
			dda->side = 1;
		}
		//if (data->map[raycast->mapX][raycast->mapY] > 0)
		if (data->map[raycast->mapY][raycast->mapX] == 1)
			dda->hit = 1;
	}
}

void	wallHeightCalc(t_raycast *raycast, t_dda *dda)
{
	if (dda->side == 0)
		dda->perpWallDist = ft_absfloat((raycast->mapX - raycast->rayPosX
					+ (1 - dda->stepX) / 2) / raycast->rayDirX);
	else
		dda->perpWallDist = ft_absfloat((raycast->mapY - raycast->rayPosY
					+ (1 - dda->stepY) / 2) / raycast->rayDirY);
	raycast->lineHeight = ft_absolute((int)(WIN_HEIGHT / dda->perpWallDist));
	raycast->drawStart = -raycast->lineHeight / 2 + WIN_HEIGHT / 2;
	if (raycast->drawStart < 0)
		raycast->drawStart = 0;
	raycast->drawEnd = raycast->lineHeight / 2 + WIN_HEIGHT / 2;
	if (raycast->drawEnd >= WIN_HEIGHT)
		raycast->drawEnd = WIN_HEIGHT - 1;
}

void	raycasting(t_player const *player, t_raycast *raycast, t_dda *dda, t_data *data, int x)
{
	int	color;
	color = 0;

	rayInit(raycast, dda, player, x);
	ddaInit(raycast, dda);
	ddaLoop(raycast, dda, data);
	wallHeightCalc(raycast, dda);

	/*switch(data->map[raycast->mapX][raycast->mapY])
	  {
	  case 1:  color = 16711680;  break; //red
	  case 2:  color = 65280;  break; //green
	  case 3:  color = 255;   break; //blue
	  case 4:  color = 16777215;  break; //white
	  default: color = 16776960; break; //yellow
	  }*/
	if (data->map[raycast->mapY][raycast->mapX] == 1)
		color = 255;
	if (dda->side == 1)
		color = color / 2;
	drawVertical(data->img_ptr, x, raycast->drawStart, raycast->drawEnd, color);
}

void	*iterateRaycast(void *param)
{
	t_wolf *wolf;
	int x;

	wolf = (t_wolf *)param;
	x = wolf->data.xStart;
	while (x < wolf->data.xEnd)
	{
		raycasting(&(wolf->player), &(wolf->raycast), &(wolf->dda), &(wolf->data), x);
		x++;
	}
	return (NULL);
}

void	multithread(t_wolf *wolf)
{
	//int		startClock;
	//int		deltaClock;
	//int		currentFPS;

	t_wolf		params[NB_THREADS];
	pthread_t	threads[NB_THREADS];
	int		i;

	i = 0;
	//startClock = SDL_GetTicks();
	while (i < NB_THREADS)
	{
		ft_memcpy((void *)&params[i], (void *)wolf, sizeof(t_wolf));
		params[i].data.xStart = (WIN_WIDTH / NB_THREADS) * i;
		params[i].data.xEnd = (WIN_WIDTH / NB_THREADS) * (i + 1);
		pthread_create(&threads[i], NULL, iterateRaycast, &params[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	//deltaClock = SDL_GetTicks() - startClock;
	//if (deltaClock != 0)
	//{
	//	currentFPS = 1000 / deltaClock;
	//	ft_printf("%d\n", currentFPS);
	//}
}

void	speed(t_player *player, t_sdl *sdl, t_data *data)
{
	//double speed = 0.08;
	//double rotspeed = 0.04;
	double speed = 0.1;
	double rotspeed = 0.06;

	if (sdl->event.key.keysym.sym == SDLK_w)
	{
		if(data->map[(int)(player->posY + player->dirY * speed)][(int)player->posX] == 0)
			player->posY += player->dirY * speed;
		if(data->map[(int)player->posY][(int)(player->posX + player->dirX * speed)] == 0)
			player->posX += player->dirX * speed;
	}
	if (sdl->event.key.keysym.sym == SDLK_s)
	{
		if(data->map[(int)(player->posY - player->dirY * speed)][(int)player->posX] == 0)
			player->posY -= player->dirY * speed;
		if(data->map[(int)player->posY][(int)(player->posX - player->dirX * speed)] == 0)
			player->posX -= player->dirX * speed;
	}

	if (sdl->event.type == SDL_MOUSEMOTION)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		//SDL_WarpMouseInWindow(sdl->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		//printf("x event = %d, y event = %d\n", sdl->event.motion.xrel, sdl->event.motion.yrel);
		if (sdl->event.motion.xrel > 0)
		{
			double saveDirX = player->dirX;
			player->dirX = player->dirX * cos(-rotspeed) - player->dirY * sin(-rotspeed);
			player->dirY = saveDirX * sin(-rotspeed) + player->dirY * cos(-rotspeed);
			double savePlaneX = player->planeX;
			player->planeX = player->planeX * cos(-rotspeed) - player->planeY * sin(-rotspeed);
			player->planeY = savePlaneX * sin(-rotspeed) + player->planeY * cos(-rotspeed);
		}
		else
		{
			double oldDirX = player->dirX;
			player->dirX = player->dirX * cos(rotspeed) - player->dirY * sin(rotspeed);
			player->dirY = oldDirX * sin(rotspeed) + player->dirY * cos(rotspeed);
			double savePlaneX = player->planeX;
			player->planeX = player->planeX * cos(rotspeed) - player->planeY * sin(rotspeed);
			player->planeY = savePlaneX * sin(rotspeed) + player->planeY * cos(rotspeed);
		}
	}
	if (sdl->event.key.keysym.sym == SDLK_d)
	{
		double saveDirX = player->dirX;
		player->dirX = player->dirX * cos(-rotspeed) - player->dirY * sin(-rotspeed);
		player->dirY = saveDirX * sin(-rotspeed) + player->dirY * cos(-rotspeed);
		double savePlaneX = player->planeX;
		player->planeX = player->planeX * cos(-rotspeed) - player->planeY * sin(-rotspeed);
		player->planeY = savePlaneX * sin(-rotspeed) + player->planeY * cos(-rotspeed);
	}
	if (sdl->event.key.keysym.sym == SDLK_a)
	{
		double oldDirX = player->dirX;
		player->dirX = player->dirX * cos(rotspeed) - player->dirY * sin(rotspeed);
		player->dirY = oldDirX * sin(rotspeed) + player->dirY * cos(rotspeed);
		double savePlaneX = player->planeX;
		player->planeX = player->planeX * cos(rotspeed) - player->planeY * sin(rotspeed);
		player->planeY = savePlaneX * sin(rotspeed) + player->planeY * cos(rotspeed);
	}
}

void mainLoop(t_wolf *wolf)
{
	int pixels[WIN_WIDTH * WIN_HEIGHT];
	wolf->data.img_ptr = &pixels[0];
	//int	leftMouseButtonDown = 0;

	while (!wolf->data.quit)
	{
		//SDL_UpdateTexture(sdl->tex, NULL, data->pixels, WIN_WIDTH * sizeof(int));
		while (SDL_PollEvent(&(wolf->sdl.event)) != 0)
		{
			ft_memset(pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
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
			   drawVertical(data->pixels, sdl->event.motion.x, sdl->event.motion.y - 100, sdl->event.motion.y + 100, 0);
			//fillPix(data->pixels, sdl->event.motion.x, sdl->event.motion.y, 0);
			//data->pixels[sdl->event.motion.y * WIN_WIDTH + sdl->event.motion.x] = 0;
			 */ 
			speed(&(wolf->player), &(wolf->sdl), &(wolf->data));
			//SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, 255);
			SDL_UpdateTexture(wolf->sdl.tex, NULL, pixels, WIN_WIDTH * sizeof(int));
			SDL_RenderClear(wolf->sdl.ren);
			SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.tex, NULL, NULL);
			SDL_RenderPresent(wolf->sdl.ren);
		}
	}
}

int main(int argc, char *argv[])
{
	t_wolf	wolf;

	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "usage: ./wolf3d %{g}s\n", "[valid .w3d map]");
		return (EXIT_FAILURE);
	}
	initWolf(&wolf, argv[1]);
	if (initSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex)) != EXIT_SUCCESS)
	{
		freeSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
		return (EXIT_FAILURE);
	}
	mainLoop(&wolf);
	freeSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
	return (EXIT_SUCCESS);
}
