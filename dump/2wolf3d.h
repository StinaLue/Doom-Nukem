#ifndef WOLF_3D
# define WOLF_3D

# include "SDL.h"

# define TITLE "TEST"
# define WIN_WIDTH 800
# define WIN_HEIGHT 800


typedef struct			s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*surf;
	SDL_Surface		*img;
	SDL_Event		event;
}				t_sdl;

typedef struct			s_wolf
{
	t_sdl			sdl;
	int			quit;
}				t_wolf;

#endif
