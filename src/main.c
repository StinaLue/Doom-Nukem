#include "libft.h"

#include "wolf3d.h"

#define mapWidth 24
#define mapHeight 24

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
		ft_dprintf(2, "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	initSDL(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_dprintf(2, "SDL_Init Error: %{r}s\n", SDL_GetError());
		return (EXIT_FAILURE);
	}
	*win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, \
			SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (*win == NULL)
	{
		ft_dprintf(2, "SDL_CreateWindow Error: %{r}s\n", SDL_GetError());
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

void	initDataStruct(t_data *data)
{
	data->quit = 0;
	ft_memset(data->pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
}

void	initPlayerStruct(t_player *player)
{
	player->posX = 22;
	player->posY = 12;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;
}

void	initWolf(t_wolf *wolf)
{
	initSdlStruct(&(wolf->sdl));
	initDataStruct(&(wolf->data));
	initPlayerStruct(&(wolf->player));
}

void	fillPix(int *pixels, int x, int y, int color)
{
	if (x < WIN_WIDTH && y < WIN_HEIGHT && x > 0 && y > 0)
		pixels[x + y * WIN_WIDTH] = color;
}

void	drawVertical(int **pixels, int x, int y1, int y2, int color)
{
	while (y1 < y2)
	{
		fillPix(*pixels, x, y1, color);
		y1++;
	}
}

void	raycast(t_player *player, int *pixels)
{
	double cameraX;
	double rayDirX;
	double rayDirY;

	int	mapX = player->posX;
	int	mapY = player->posY;

	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;

	int	stepX;
	int	stepY;

	int	hit = 0;
	int	side;

	int	lineHeight;

	int	drawStart;
	int	drawEnd;
	int	color;

	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cameraX = 2 * x / WIN_WIDTH - 1;
		rayDirX = player->dirX + player->planeX * cameraX;
		rayDirY = player->dirY + player->planeY * cameraX;

		deltaDistX = ft_absolute(1 / rayDirX);
		deltaDistY = ft_absolute(1 / rayDirY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapX + 1.0 - player->posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - player->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - player->posY + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= drawStart)
			drawEnd = WIN_HEIGHT - 1;

		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 16711680;  break; //red
			case 2:  color = 65280;  break; //green
			case 3:  color = 255;   break; //blue
			case 4:  color = 16777215;  break; //white
			default: color = 16776960; break; //yellow
		}
		if (side == 1)
			color = color / 2;
		//HEEEEEEEEEEEEERE
		drawVertical(&pixels, x, drawStart, drawEnd, color);
	}
	x++;
}

void	speed(t_player *player, t_sdl *sdl)
{
	double speed = 0.1;

	if (sdl->event.key.keysym.sym == SDLK_w)
	{
		if(worldMap[(int)(player->posX + player->dirX * speed)][(int)player->posY] == 0)
			player->posX += player->dirX * speed;
		if(worldMap[(int)player->posX][(int)(player->posY + player->dirY * speed)] == 0)
			player->posY += player->dirY * speed;
	}
	if (sdl->event.key.keysym.sym == SDLK_s)
	{
		if(worldMap[(int)(player->posX - player->dirX * speed)][(int)player->posY] == 0)
			player->posX -= player->dirX * speed;
		if(worldMap[(int)player->posX][(int)(player->posY - player->dirY * speed)] == 0)
			player->posY -= player->dirY * speed;
	}
	if (sdl->event.key.keysym.sym == SDLK_d)
	{
		player->dirY = player->dirX + player->dirY;//* sin(-speed) + player
		player->dirX = player->dirX - player->dirY;//* cos(-speed) - player->dirY * sin(-speed);
		player->planeY = player->planeX - player->planeY;
		player->planeX = player->planeX + player->planeY;
	}
	if (sdl->event.key.keysym.sym == SDLK_a)
	{
		player->dirY = player->dirX + player->dirY;//* sin(-speed) + player
		player->dirX = player->dirX - player->dirY;//* cos(-speed) - player->dirY * sin(-speed);
		player->planeY = player->planeX - player->planeY;
		player->planeX = player->planeX + player->planeY;
	}
}

void mainLoop(t_sdl *sdl, t_data *data, t_player *player)
{
	//int	leftMouseButtonDown = 0;

	while (!data->quit)
	{
		SDL_UpdateTexture(sdl->tex, NULL, data->pixels, WIN_WIDTH * sizeof(int));
		while (SDL_PollEvent(&(sdl->event)) != 0)
		{
			raycast(player, data->pixels);//&(data->pixels));
			/*
			   if (sdl->event.type == SDL_QUIT || sdl->event.key.keysym.sym == SDLK_ESCAPE)
			   data->quit = 1;
			   if (sdl->event.type == SDL_MOUSEBUTTONUP)
			   if (sdl->event.button.button == SDL_BUTTON_LEFT)
			   leftMouseButtonDown = 0;
			   if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
			   if (sdl->event.button.button == SDL_BUTTON_LEFT)
			   leftMouseButtonDown = 1;
			   if (sdl->event.type == SDL_MOUSEMOTION)
			   if (leftMouseButtonDown)
			   fillPix(data->pixels, sdl->event.motion.x, sdl->event.motion.y, 0);
			//data->pixels[sdl->event.motion.y * WIN_WIDTH + sdl->event.motion.x] = 0;
			 */
			speed(player, sdl);
			SDL_RenderClear(sdl->ren);
			SDL_RenderCopy(sdl->ren, sdl->tex, NULL, NULL);
			SDL_RenderPresent(sdl->ren);
		}
	}
}

int main()
{
	t_wolf	wolf;

	initWolf(&wolf);
	if (initSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex)) != EXIT_SUCCESS)
	{
		freeSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
		return (EXIT_FAILURE);
	}
	mainLoop(&wolf.sdl, &wolf.data, &wolf.player);
	freeSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
	return (EXIT_SUCCESS);
}
