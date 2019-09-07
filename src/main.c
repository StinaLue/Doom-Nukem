#include "libft.h"

#include "wolf3d.h"

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

void	initWolf(t_wolf *wolf)
{
	wolf->sdl.win = NULL;
	wolf->sdl.ren = NULL;
	wolf->sdl.tex = NULL;
	wolf->quit = 0;
}

int main()
{
	t_wolf	wolf;
	int	leftMouseButtonDown = 0;
	int	pixels[WIN_WIDTH * WIN_HEIGHT];

	initWolf(&wolf);
	ft_memset(pixels, 255, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	if (initSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex)) != EXIT_SUCCESS)
	{
		freeSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
		return (EXIT_FAILURE);
	}
	while (!wolf.quit)
	{
		SDL_UpdateTexture(wolf.sdl.tex, NULL, pixels, WIN_WIDTH * sizeof(int));
		while (SDL_PollEvent(&(wolf.sdl.event)) != 0)
		{
			if (wolf.sdl.event.type == SDL_QUIT)
				wolf.quit = 1;
			if (wolf.sdl.event.type == SDL_MOUSEBUTTONUP)
				if (wolf.sdl.event.button.button == SDL_BUTTON_LEFT)
					leftMouseButtonDown = 0;
			if (wolf.sdl.event.type == SDL_MOUSEBUTTONDOWN)
				if (wolf.sdl.event.button.button == SDL_BUTTON_LEFT)
					leftMouseButtonDown = 1;
			if (wolf.sdl.event.type == SDL_MOUSEMOTION)
				if (leftMouseButtonDown)
					pixels[wolf.sdl.event.motion.y * WIN_WIDTH + wolf.sdl.event.motion.x] = 0;
		SDL_RenderClear(wolf.sdl.ren);
        	SDL_RenderCopy(wolf.sdl.ren, wolf.sdl.tex, NULL, NULL);
        	SDL_RenderPresent(wolf.sdl.ren);
		}
	}
	freeSDL(&(wolf.sdl.win), &(wolf.sdl.ren), &(wolf.sdl.tex));
	return (EXIT_SUCCESS);
}
