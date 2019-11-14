/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                           :+:      :+:    :+:   */
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
# include "SDL_ttf.h"
# define TITLE "DOOM"

# define NB_WALLS 4

# define FIRST_MAP_WIDTH 100
# define FIRST_MAP_HEIGHT 100

# define SECOND_MAP_WIDTH 100
# define SECOND_MAP_HEIGHT 100

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define NB_THREADS 8
# define MAX_MAP 100
# define MAX_LOOK_DOWN -400
# define MAX_LOOK_UP 400
# define X_SIDE	0
# define Y_SIDE 1

# define TEX_W 128
# define TEX_H 128

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*surf;
	SDL_Event	event;
}				t_sdl;

typedef struct	s_ttf
{
	TTF_Font	*font;
	SDL_Surface	*surf_message;
	char		*fps;
	SDL_Color	color;
	SDL_Rect	rect;
}				t_ttf;

typedef struct	s_data
{
	Uint32		*win_img_ptr;
	int			quit;
}				t_data;

typedef struct	s_img_data
{
	Uint32		*img_ptr;
	int			rowsize;
	int			height;
}				t_img_data;

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

typedef	struct	s_wall
{
	t_vec		start_wall;
	t_vec		end_wall;
	//int			flags; BIT FLAGS for walls specifications?
}				t_wall;

typedef struct	s_bresen
{
	t_vec		point_one;
	t_vec		point_two;
	int			xinc;
	int			yinc;
	int			dx;
	int			dy;
}				t_bresen;

typedef struct	s_player
{
	t_vec		playerpos;
	double		angle;
}				t_player;

typedef struct	s_doom
{
	t_sdl		sdl;
	t_data		data;
	t_vec		player_pos;
}				t_doom;

void			fill_pix(t_img_data *img_data, int x, int y, int color);

void			draw_line(const t_vec a, const t_vec b, t_img_data *img_data, int color);

void			free_sdl(SDL_Window **win);

int				free_sdl_quit(SDL_Window **win);

int				init_sdl(SDL_Window **win, SDL_Surface **surf);

#endif
