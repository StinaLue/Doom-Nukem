#ifndef WOLF_3D
# define WOLF_3D

# include "SDL.h"
# include "SDL_ttf.h"

# define TITLE "TEST"
//# define WIN_WIDTH 800
//# define WIN_HEIGHT 800
# define WIN_WIDTH 1680
# define WIN_HEIGHT 1050

# define NB_THREADS 60

# define MAX_MAP 100

void				draw_line();

typedef struct			s_sdl
{
	SDL_Window		*win;
	SDL_Renderer		*ren;
	SDL_Texture		*tex;
	SDL_Event		event;
}				t_sdl;

typedef struct			s_ttf
{
	TTF_Font		*font;
	SDL_Surface		*surf_message;
	SDL_Texture		*message;
	char			*fps;
	SDL_Color		color;
	SDL_Rect		rect;
}				t_ttf;

typedef struct			s_data
{
	int			quit;
//	int			pixels[WIN_WIDTH * WIN_HEIGHT];
	int			*img_ptr;
//	int			map[MAX_MAP][MAX_MAP];
	int			(*map_ptr)[MAX_MAP][MAX_MAP];
	int			widthMap;
	int			heightMap;
	int			xStart;
	int			xEnd;
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
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
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
	int			hit;
	int			side;
}				t_dda;

typedef struct			s_wolf
{
	t_sdl			sdl;
	t_ttf			ttf;
	t_data			data;
	t_player		player;
	t_raycast		raycast;
	t_dda			dda;
}				t_wolf;

#endif
