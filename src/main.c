#include "SDL.h"
#include "libft.h"

SDL_bool test(SDL_Point point, SDL_Rect rect)
{
	if (point.x >= rect.x && point.x <= (rect.x + rect.w) &&
			point.y >= rect.y && point.y <= (rect.y + rect.h))
		return SDL_TRUE;
	else
		return SDL_FALSE;
}

int main()
{
	SDL_Window *win;
	SDL_Renderer *renderer;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_dprintf(2, "SDL_Init Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	//OR SDL_CreateWindowAndRenderer --> 2 in 1
	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		ft_dprintf(2, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	SDL_Delay(3000);
	printf("%s\n", SDL_GetWindowTitle(win));
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		ft_dprintf(2, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
