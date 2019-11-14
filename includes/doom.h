/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h   	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:54 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/26 12:21:27 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# define TITLE "DOOM"

# define NB_WALLS 4

# define ROT_MAP_WIDTH 100
# define ROT_MAP_HEIGHT 100

# define FIXED_MAP_WIDTH 100
# define FIXED_MAP_HEIGHT 100

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

/*
** VECTOR STRUCTS
*/
typedef struct	s_vec
{
	int			x;
	int			y;
}				t_vec;

typedef struct	s_vecdb
{
	double		x;
	double		y;
}				t_vecdb;

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*win_surf;
	SDL_Surface *fixed_mmap;
	SDL_Surface *rot_mmap;
	SDL_Event	event;
}				t_sdl;

typedef struct	s_data
{
	int			quit;
}				t_data;

typedef	struct	s_wall
{
	t_vec		start_wall;
	t_vec		end_wall;
	//int		flags; BIT FLAGS for walls specifications?
}				t_wall;

typedef struct	s_player
{
	t_vecdb		pos;
	t_vecdb		direc;
	double		angle;
}				t_player;

typedef struct	s_doom
{
	t_sdl		sdl;
	t_data		data;
	t_player	player;
}				t_doom;

/*
** INIT FUNCTIONS
*/
void			init_doom(t_doom *doom);

int				init_sdl(SDL_Window **win, SDL_Surface **surf);

/*
** INIT STRUCT FUNCTIONS
*/
void			init_sdl_struct(t_sdl *sdl);

void			init_data_struct(t_data *data);

void			init_player_struct(t_player *player);

/*
** PRINT MINIMAP FUNCTIONS
*/

void			draw_fixed_minimap(SDL_Surface *surf, t_player *player, t_wall *walls);

void			draw_rot_minimap(SDL_Surface *surf, t_player *player, t_wall *walls);

/*
** DRAWING FUNCTIONS
*/
void			fill_pix(SDL_Surface *surf, int x, int y, int color);

void			draw_line(const t_vec a, const t_vec b, SDL_Surface *surf, int color);


/*
** FREE FUNCTIONS
*/
void			free_sdl(SDL_Window **win);

int				free_sdl_quit(SDL_Window **win);

#endif
