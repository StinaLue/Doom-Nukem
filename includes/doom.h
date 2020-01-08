/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:54 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/08 14:32:19 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"
# define TITLE "DOOM"

# define NB_WALLS 4
# define SQRT2 1.4142135623730950488

/*
** MAIN LOOP STATES
*/

# define QUIT_STATE 0
# define GAME_STATE 1
# define MENU_STATE 2
# define EDITOR_STATE 3

/*
** DIMENSIONS
*/

# define HD_W 1280
# define HD_H 720

# define WSXGA_W 1680
# define WSXGA_H 1050

# define FHD_W 1920
# define FHD_H 1080

# define QHD_W 2560
# define QHD_H 1440

# define OFFSET 20

# define NBPOINTS 2501 // map has 50 * 50 points
# define NBPOINTSROW 50 // NBPOINTS = NBPOINTSROW * NBPOINTSROW
# define MAX_WALLS 50
# define MAX_SECTORS 10
/*
** HUD FLAGS
*/

# define ROT_MAP_SHOW 1//0x00000001
# define FIX_MAP_SHOW 2//0x00000010
# define COLORFLAG 4//0x00000100

/*
** MENU OPTIONS
*/

# define FIRST_OPTION_SELECT 1
# define SECOND_OPTION_SELECT 2
# define THIRD_OPTION_SELECT 3
# define FOURTH_OPTION_SELECT 4

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

typedef struct	s_sdlmain
{
	SDL_Window	*win;
	SDL_Surface	*win_surf;
	SDL_Event	event;
	Mix_Music	*music;
	int			win_w;
	int			win_h;
}				t_sdlmain;

typedef struct	s_gamesurfs
{
	SDL_Surface *fixed_mmap;
	SDL_Surface *rot_mmap;
	SDL_Surface *perspective_view;
}				t_gamesurfs;

typedef struct	s_data
{
	char		hud_flags;
}				t_data;

typedef	struct	s_wall
{
	t_vecdb		start_wall;
	t_vecdb 	end_wall;
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
	t_vecdb		fov;
	double		true_fov;
	int			helper;
}				t_player;

typedef struct	s_game
{
	t_gamesurfs	surfs;
	t_data		data;
	t_player	player;
}				t_game;

typedef struct s_editor_menu
{
	//The surfaces
	SDL_Surface *background;
	SDL_Surface *title;
	SDL_Surface *title_inst;
	SDL_Surface *first_option;
	//SDL_Surface *second_option;
	//SDL_Surface *third_option;
	//SDL_Surface *fourth_option;
	//SDL_Surface *fifth_option;

	//Clip rectangles
	SDL_Rect background_rect;
	SDL_Rect title_rect;
	SDL_Rect title_inst_rect;
	SDL_Rect first_option_rect;
	//SDL_Rect second_option_rect;
	//SDL_Rect third_option_rect;
	//SDL_Rect fourth_option_rect;

	//The font that's going to be used
	TTF_Font *font;

	//The color of the font
	SDL_Color textColor;
}				t_editor_menu;

typedef struct 	s_editor
{
	SDL_Surface *editor_surf;
	SDL_Surface *options_surf;
	SDL_Surface *instruct_surf;
	SDL_Rect	editor_rect;
	SDL_Rect	options_rect;
	SDL_Rect	instruct_rect;
    int         clicked;
	int			num_walls;
	int			num_sectors;
    int         offset;
    int         sectors[MAX_SECTORS];
	int			start_sector_reached;
	int 		color_change;
    t_wall      walls[MAX_WALLS];
	t_vec 		grid_values[NBPOINTS];
	t_vec       mouse_pos;
    t_vec       start_sector;
	t_editor_menu editor_menu;
}				t_editor;

typedef struct	s_menu
{
	//The surfaces
	SDL_Surface *background;
	SDL_Surface *menu_title;
	SDL_Surface *first_option;
	SDL_Surface *second_option;
	SDL_Surface *third_option;
	SDL_Surface *fourth_option;

	//Clip rectangles
	SDL_Rect background_rect;
	SDL_Rect menu_title_rect;
	SDL_Rect first_option_rect;
	SDL_Rect second_option_rect;
	SDL_Rect third_option_rect;
	SDL_Rect fourth_option_rect;

	//The font that's going to be used
	TTF_Font *font;

	//The color of the font
	SDL_Color textColor;
	int		current_option;
	int		previous_state;
}				t_menu;

typedef struct	s_doom
{
	t_game		game;
	t_menu		menu;
	t_editor	editor;
	t_sdlmain	sdlmain;
	int			state;
}				t_doom;

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

double			dot_product(t_vecdb a, t_vecdb b);

double			cross_product(t_vecdb a, t_vecdb b);

t_vecdb			create_vecdb(double x, double y);

/*
** INIT FUNCTIONS
*/

void			null_doom_pointers(t_doom *doom);

int				init_sdl_and_ttf();

int				init_game(t_game *game, t_sdlmain *sdlmain);

int				init_menu(t_menu *menu, t_sdlmain *sdlmain);

int				init_editor(t_editor *editor, t_sdlmain *sdlmain);

int				init_sdlmain(t_sdlmain *sdlmain);

int				init_editor_menu(t_editor *editor);

/*
** INIT STRUCT FUNCTIONS
*/
int				init_gamesurfs_struct(t_gamesurfs *gamesurfs, t_sdlmain *sdlmain);

void			init_data_struct(t_data *data);

void			init_player_struct(t_player *player);

/*
** POLL EVENT FUNCTIONS
*/
int				handle_events(t_doom *doom);

/*
** EVENT FUNCTIONS
*/
void			handle_keys(t_game *game, t_wall *walls, const Uint8 *keyboard_state);

/*
** PRINT MINIMAP FUNCTIONS
*/

int				draw_map(t_sdlmain *sdlmain, t_game *game, t_wall *walls, char *hud_flags);

int				draw_full_fixedmap(SDL_Surface *surf, t_player *player, t_wall *walls, SDL_Surface *winsurf);

int				draw_full_rotmap(SDL_Surface *surf, t_player *player, t_wall *walls, SDL_Surface *winsurf);

void			draw_perspective_view(SDL_Surface *surf, t_player *player, t_wall *walls);

/*
** DRAWING FUNCTIONS
*/

int				blit_in_rect(SDL_Surface *surf, SDL_Surface *winsurf, int whichsurf);

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

void			quit_sdl_and_ttf();

int				free_menu(t_menu *menu);

int				free_game(t_game *game);

int				free_editor(t_editor *editor);

int				free_sdlmain(t_sdlmain *sdlmain);

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


/*
** LOOPS
*/

int				game_loop(t_doom *doom);

int 			menu_loop(t_doom *doom);

int				editor_loop(t_doom *doom);

/*
** ERROR FUNCTIONS
*/

int				error_return(const char *error_msg, const char *sdl_error);


/*
** EDITOR FUNCTIONS
*/

#endif
