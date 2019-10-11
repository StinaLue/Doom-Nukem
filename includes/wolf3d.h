/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:54 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/11 14:53:49 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_3D
# define WOLF_3D

# include "SDL.h"
# include "SDL_ttf.h"
# define TITLE "TEST"
# define WIN_WIDTH 1680
# define WIN_HEIGHT 1050
# define NB_THREADS 60
# define MAX_MAP 100

void				draw_line();

typedef struct			s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*tex;
	SDL_Event		event;
}						t_sdl;

typedef struct			s_ttf
{
	TTF_Font		*font;
}						t_ttf;

typedef struct			s_data
{
	int				quit;
//	int				pixels[WIN_WIDTH * WIN_HEIGHT];
	int				*img_ptr;
//	int				map[MAX_MAP][MAX_MAP];
	int				(*map_ptr)[MAX_MAP][MAX_MAP];
	int				map_width;
	int				map_height;
	int				start_thread;
	int				end_thread;
}						t_data;

typedef struct			s_player
{
	double			x;
	double			y;
	double			x_dir;
	double			y_dir;
	double			x_camera_vector;
	double			y_camera_vector;
}						t_player;

typedef struct			s_raycast
{
	int				x;
	int				y;
	double			cam_x;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	int				height;
	int				start_line;
	int				end_line;
}						t_raycast;

typedef struct			s_dda
{
	double			distance_x_side;
	double			distance_y_side;
	double			distance_x;
	double			distance_y;
	double			distance_wall;
	int				x_wall_hit;
	int				y_wall_hit;
	int				hit;
	int				side;
}						t_dda;

typedef struct			s_wolf
{
	t_sdl			sdl;
	t_ttf			ttf;
	t_data			data;
	t_player		player;
	t_raycast		raycast;
	t_dda			dda;
}						t_wolf;

#endif
