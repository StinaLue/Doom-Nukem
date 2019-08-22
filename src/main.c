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
	SDL_Surface *bmp;
	SDL_Texture *texture;
	char *path_bmp = "/Users/afonck/Desktop/Wolf3D/src/test.bmp";

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_dprintf(2, "SDL_Init Error: %{r}s\n", SDL_GetError());
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	//OR SDL_CreateWindowAndRenderer --> 2 in 1
	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		ft_dprintf(2, "SDL_CreateWindow Error: %{r}s\n", SDL_GetError());
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", SDL_GetWindowTitle(win));
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		ft_dprintf(2, "SDL_CreateRenderer Error: %{r}s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	bmp = SDL_LoadBMP(path_bmp);
	if (bmp == NULL)
	{
		ft_dprintf(2, "SDL_LoadBMP Error: %{r}s\n", SDL_GetError());
		SDL_FreeSurface(bmp);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	texture = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	if (texture == NULL)
	{
		ft_dprintf(2, "SDL_CreateTextureFromSurface Error: %{r}s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	for (int i = 0; i < 3; ++i)
	{
		//First clear the renderer
		SDL_RenderClear(renderer);
		//Draw the texture
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		//Update the screen
		SDL_RenderPresent(renderer);
		//Take a quick break after all that hard work
		SDL_Delay(1000);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
