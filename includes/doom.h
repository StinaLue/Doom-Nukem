/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:54 by sluetzen          #+#    #+#             */
/*   Updated: 2019/11/28 17:51:48 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# define TITLE "DOOM"

# define NB_WALLS 4

/*
** DIMENSIONS
*/

# define ROT_MAP_WIDTH 100
# define ROT_MAP_HEIGHT 100

# define FIXED_MAP_WIDTH 100
# define FIXED_MAP_HEIGHT 100

# define THIRD_MAP_WIDTH 1800 / 3//600
# define THIRD_MAP_HEIGHT 1000 / 3//600

# define WIN_WIDTH 1800
# define WIN_HEIGHT 1000

# define HFOV (0.73 * THIRD_MAP_HEIGHT)
# define VFOV (0.2 * THIRD_MAP_HEIGHT)

/*
** FLAGS
*/

# define ROT_MAP_SHOW 1//0x00000001
# define FIX_MAP_SHOW 2//0x00000010
# define COLORFLAG 4//0x00000100

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

typedef struct	s_wall3d
{
	t_vec	 	top_left;
	t_vec	 	top_right;
	t_vec	 	bottom_left;
	t_vec	 	bottom_right;
}				t_wall3d;

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*win_surf;
	SDL_Surface *fixed_mmap;
	SDL_Surface *rot_mmap;
	SDL_Surface *perspective_mmap;
	SDL_Event	event;
}				t_sdl;

typedef struct	s_data
{
	int			quit;
	char		hud_flags;
}				t_data;

typedef	struct	s_wall
{
	t_vecdb		start_wall;
	t_vecdb		end_wall;
	int			color;
	//int		flags; BIT FLAGS for walls specifications?
}				t_wall;

typedef struct	s_player
{
	t_vecdb		pos;
	t_vecdb		direc;
	double		angle;
	double		view_z;
}				t_player;

typedef struct	s_doom
{
	t_sdl		sdl;
	t_data		data;
	t_player	player;
}				t_doom;

int 	check_collision(double pos_x, double pos_y, t_wall *walls);

void	init_rotate_wall(t_wall *new_wall, const t_wall *old_wall, const t_player *player);

int		is_in_map(t_vecdb *player);

/*
** VECTOR FUNCTIONS
*/

t_vec			create_vec(int x, int y);

void			give_vec_values(t_vec *vec, int x, int y);

void			vectorcpy(t_vec *one, const t_vec *two);

t_vec			vecdb_to_vec(t_vecdb vectordb);

t_vecdb			vec_to_vecdb(t_vec vector);

t_vecdb			rotate2d(t_vecdb vector, double angle);

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
** POLL EVENT FUNCTIONS
*/
void			handle_events(SDL_Event *event, t_data *data);

/*
** EVENT FUNCTIONS
*/
void			handle_keys(t_doom *doom, t_wall *walls, const Uint8 *keyboard_state);

/*
** PRINT MINIMAP FUNCTIONS
*/

void			draw_map(t_sdl *sdl, t_player *player, t_wall *walls, char *hud_flags);

void			draw_full_fixedmap(SDL_Surface *surf, t_player *player, t_wall *walls, SDL_Surface *winsurf);
//void			draw_fixed_minimap(SDL_Surface *surf, t_player *player, t_wall *walls);

void			draw_full_rotmap(SDL_Surface *surf, t_player *player, t_wall *walls, SDL_Surface *winsurf);
//void			draw_rot_minimap(SDL_Surface *surf, t_player *player, t_wall *walls);

void			draw_perspective_minimap(SDL_Surface *surf, t_player *player, t_wall *walls);

/*
** DRAWING FUNCTIONS
*/

void			blit_in_rect(SDL_Surface *surf, SDL_Surface *winsurf, int whichsurf);

void			fill_pix(SDL_Surface *surf, int x, int y, int color);

void			draw_line(const t_vec a, const t_vec b, SDL_Surface *surf, int color);


/*
** FREE FUNCTIONS
*/
void			free_sdl(SDL_Window **win);

int				free_sdl_quit(SDL_Window **win);

/*
** PARSE FUNCTIONS
*/

int				parse_everything(t_wall *walls);


#endif
