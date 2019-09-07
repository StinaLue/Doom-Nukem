#ifndef WOLF_3D
# define WOLF_3D

# include "SDL.h"

# define TITLE "TEST"
# define WIN_WIDTH 800
# define WIN_HEIGHT 800


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
}				t_data;

typedef struct			s_wolf
{
	t_sdl			sdl;
	t_data			data;
}				t_wolf;

#endif
