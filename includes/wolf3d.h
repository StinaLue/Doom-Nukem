#ifndef WOLF_3D
# define WOLF_3D

# include "SDL.h"

# define TITLE "TEST"
# define WIN_WIDTH 800
# define WIN_HEIGHT 800

# define MAX_MAP 100

void				draw_line();

typedef struct			s_sdl
{
	SDL_Window		*win;
	SDL_Renderer		*ren;
	SDL_Texture		*tex;
	SDL_Event		event;
}				t_sdl;

typedef struct			s_data
{
	int			quit;
	int			pixels[WIN_WIDTH * WIN_HEIGHT];
	int			map[MAX_MAP][MAX_MAP];
	int			widthMap;
	int			heightMap;
}				t_data;

typedef struct 			s_player
{
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
}				t_player;

typedef struct			s_raycast
{
	int			mapX;
	int			mapY;
	double			camX;
	double			rayPosX;
	double			rayPosY;
	double			rayDirX;
	double			rayDirY;
}				t_raycast;

typedef struct			s_dda
{
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	double			perpWallDist;
	int			stepX;
	int			stepY;
}				t_dda;

typedef struct			s_wolf
{
	t_sdl			sdl;
	t_data			data;
	t_player		player;
	t_raycast		raycast;
	t_dda			dda;
}				t_wolf;

#endif
