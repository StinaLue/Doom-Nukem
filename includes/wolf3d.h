#ifndef WOLF_3D
# define WOLF_3D

# include "SDL.h"

# define TITLE "TEST"
# define WIN_WIDTH 800
# define WIN_HEIGHT 800


typedef struct			s_sdlcomp
{
	SDL_Window		*win;
	SDL_Surface		*surf;
	SDL_Surface		*img;
}				t_sdlcomp;

typedef struct			s_wolf
{
	t_sdlcomp		sdlcomp;
}				t_wolf;

#endif
