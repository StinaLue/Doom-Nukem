/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:54 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/08 00:17:42 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "SDL_ttf.h"
# define TITLE "DOOM"

# define NB_WALLS 4
# define SQRT2 1.4142135623730950488

/*
** DIMENSIONS
*/

# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200

# define THIRD_MAP_WIDTH 1800 / 4//600
# define THIRD_MAP_HEIGHT 1000 / 4//600

# define SIZE 2
# define WIN_W (1800 / SIZE)
# define WIN_H (1000 / SIZE)
# define OFFSET (20 / SIZE)

# define MENU_WIDTH WIN_W - (WIN_W / 8)
# define MENU_HEIGHT WIN_H - (WIN_H / 4)

# define HFOV (0.5 * THIRD_MAP_HEIGHT)
# define VFOV (0.2 * THIRD_MAP_HEIGHT)

# define NBPOINTS 2891 // map has 59 * 49 points
# define MAX_WALLS 30
/*
** HUD FLAGS
*/

# define ROT_MAP_SHOW 1//0x00000001
# define FIX_MAP_SHOW 2//0x00000010
# define COLORFLAG 4//0x00000100

/*
** MENU FLAGS
*/

# define FIRST_OPTION_SELECT 1

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
	int			menu_flag;
	int			editor_flag;
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
	t_vecdb		inertia;
	double		angle;
	double		view_z;
}				t_player;

typedef struct	s_doom
{
	t_sdl		sdl;
	t_data		data;
	t_player	player;
}				t_doom;

typedef struct 	s_editor
{
    t_wall      walls;
    int         clicked;
	t_vec 		grid_values[NBPOINTS];
    t_vec       mouse_pos;
}				t_editor;

typedef struct	s_menu
{
	//The surfaces
	SDL_Surface *background;
	SDL_Surface *menu_title;
	SDL_Surface *first_option;

	//Clip rectangles
	SDL_Rect background_rect;
	SDL_Rect menu_title_rect;
	SDL_Rect first_option_rect;
	//The event structure
	SDL_Event event;

	//The font that's going to be used
	TTF_Font *font;

	//The color of the font
	SDL_Color textColor;
	char flags;
}				t_menu;

int 	check_collision(double pos_x, double pos_y, t_wall *walls);

void	init_rotate_wall(t_wall *new_wall, const t_wall *old_wall, const t_player *player);

int		is_in_map(t_vecdb *player);

/*
** VECTOR FUNCTIONS
*/
double			get_magnitude(t_vecdb a, t_vecdb b);

void			multvec(t_vecdb *vecdb, double n);

t_vec			create_vec(int x, int y);

void			give_vec_values(t_vec *vec, int x, int y);

void			vectorcpy(t_vec *one, const t_vec *two);

t_vec			vecdb_to_vec(t_vecdb vectordb);

t_vecdb			vec_to_vecdb(t_vec vector);

t_vecdb			rotate2d(t_vecdb vector, double angle);

t_vecdb			rotate2dcc(t_vecdb vector, double angle);

//double	dot_product(t_vecdb a, t_vecdb b);

t_vecdb			create_vecdb(double x, double y);

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

void			draw_border(SDL_Surface *surf, int color);

/*
** TEXT FUNCTIONS
*/

int				highlight_text(TTF_Font **font, SDL_Surface **surf, SDL_Color *color, char *text);

int				reset_text(TTF_Font **font, SDL_Surface **surf, SDL_Color *color, char *text);

/*
** FREE FUNCTIONS
*/
void			free_menu(t_menu *menu);

void			free_sdl(t_sdl *sdl);//SDL_Window **win);

int				free_sdl_quit(t_sdl *sdl);//SDL_Window **win);

/*
** PARSE FUNCTIONS
*/

int				parse_everything(t_wall *walls);

/*
** SDL_SUB_FUNCTIONS
*/

void			assign_sdlcolor(SDL_Color *color, Uint8 red, Uint8 green, Uint8 blue);

SDL_Rect		create_sdlrect(int x, int y, int w, int h);

void			assign_sdlrect(SDL_Rect *rect, t_vec origin, t_vec size);


/*
** MOVEMENT
*/

void			movement(t_player *player, t_vecdb move, t_wall *walls);

/*
** MENU FUNCTIONS
*/

int				menu_loop(SDL_Window **win, SDL_Surface **win_surf, int *menu_flag);

/*
** ERROR FUNCTIONS
*/

int				error_return(const char *error_msg, const char *sdl_error);


/*
** EDITOR FUNCTIONS
*/

void	editor(SDL_Window **win, SDL_Surface **win_surf, int *editor_flag, const Uint8 *keyboard_state);
#endif
