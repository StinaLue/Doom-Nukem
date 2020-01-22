/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:54 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/22 10:25:11 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"
# define TITLE "DOOM"

# define SQRT2 1.4142135623730950488
# define PLAYER_RADIUS 0.8

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
# define NBTEXTURES	12
# define NBHEIGHTS 7
# define NBOPTIONS 5
# define NBINSTRUCTS 5
# define COLOR_HOVER 0x6C1413
# define COLOR_PRESSED 0xffff00
# define COLOR_NORMAL 0xff0000

/*
** HUD FLAGS
*/

# define ROT_MAP_SHOW 1//0x00000001
# define FIX_MAP_SHOW 2//0x00000010
# define COLORFLAG 4//0x00000100
# define HEALTH_STATUS 8//0x00001000

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

struct s_sector_node;
struct s_wall_node;

typedef struct				s_vec
{
	int						x;
	int						y;
}							t_vec;

typedef struct				s_vecdb
{
	double					x;
	double					y;
}							t_vecdb;

typedef struct				s_wall_node
{
	struct s_wall_node		*next;
	struct s_wall_node		*previous;
	t_vecdb					start;
	t_vecdb					end;
	int						color;
	int						tex_index;
	int						sector_index;
	int 					wall_type; // for editor
	int	 					type_color;
	struct s_sector_node	*neighbor_sector;
	double					length;
}							t_wall_node;

typedef struct				s_sector_node
{
	struct s_sector_node	*next;
	t_wall_node				*wall_head;
	int						wall_num;
	t_vecdb					sector_center;
}							t_sector_node;

typedef struct				s_wall3d
{
	t_vec					top_left;
	t_vec					top_right;
	t_vec					bottom_left;
	t_vec					bottom_right;
	double					start_pos;
	double					end_pos;
}							t_wall3d;

typedef struct				s_sdlmain
{
	SDL_Window				*win;
	SDL_Surface				*win_surf;
	SDL_Event				event;
	TTF_Font				*font;
	Mix_Music				*music;
	t_vec					mouse_pos;
	int						win_w;
	int						win_h;
}							t_sdlmain;

typedef struct				s_gamesurfs
{
	SDL_Surface				*fixed_mmap;
	SDL_Surface				*rot_mmap;
	SDL_Surface				*perspective_view;
	SDL_Surface				*weapons;
	SDL_Surface				*hud_faces_surf;
	SDL_Surface				*enemy_texture[2];

	SDL_Rect				katana[4];
	SDL_Rect				hud_faces_rect;
	int						current_frame;
	int						anim_timer;
	int						hud_timer;
}							t_gamesurfs;

typedef struct				s_data
{
	char					hud_flags;
}							t_data;

typedef	struct				s_wall
{
	t_vecdb					start;
	t_vecdb					end;
}							t_wall;

typedef struct				s_view
{
	t_vecdb					left;
	t_vecdb					right;
	t_vecdb					origin;
}							t_view;

typedef struct				s_enemy
{
	t_vecdb					pos;
	SDL_Surface				*texture;
	SDL_Rect				clip_tex;
	int						health;
	int						state;
}							t_enemy;

typedef struct				s_player
{
	t_vecdb					pos;
	t_sector_node			*sector;
	t_vecdb					direc;
	t_vecdb					inertia;
	double					angle;
	double					view_z;
	t_vecdb					fov;
	double					true_fov;
	int						helper;
	int						health;
}							t_player;

typedef struct				s_game
{
	t_gamesurfs				surfs;
	t_data					data;
	t_player				player;
	int						(*weapon_anim[4])(t_gamesurfs *gamesurfs, SDL_Surface *dest, int *anim);
	int						anim;
}							t_game;

typedef struct				s_instr_menu
{
	SDL_Surface				*title;
	SDL_Surface				*instructs[5];

	SDL_Rect				title_rect;
	SDL_Rect				instr_rect[5];

	TTF_Font				*font_title;
	TTF_Font				*font;

	SDL_Color				text_color;
}							t_instr_menu;

typedef struct				s_options_menu
{
	SDL_Surface				*title;
	SDL_Surface				*options[5];

	SDL_Rect				title_rect;
	SDL_Rect				options_rect[5];
	SDL_Rect				text_rect[NBTEXTURES];
	SDL_Rect				h_rect[NBHEIGHTS];

	TTF_Font				*font_title;
	TTF_Font				*font;

	SDL_Color				text_color;
	int						bord_color_text[NBTEXTURES];
	int						bord_color_h[NBHEIGHTS];
	int						activ_tex;
	int						activ_h;
}							t_options_menu;

typedef struct				s_map
{
	t_sector_node			*sector_head;
	int						num_sectors;
}							t_map;

typedef struct				s_editor
{
	SDL_Surface				*editor_surf;
	SDL_Surface				*options_surf;
	SDL_Surface				*instr_surf;
	SDL_Surface				*mouse_surf;
	SDL_Surface				**wall_textures;

	SDL_Rect				editor_rect;
	SDL_Rect				options_rect;
	SDL_Rect				instr_rect;
	SDL_Rect 				mouse_rect;

	t_sector_node			*current_sector;
	t_wall_node				*current_wall;

	int						clicked;
	int						num_sectors;
	int						offset;
	int						start_sector_reached;
	int						color_change;
	t_vec					grid_values[NBPOINTS];
	t_vec					start_sector;
	t_wall_node				wall_tmp;
	t_instr_menu			instr_menu;
	t_options_menu			opt_menu;
	t_map					edit_map;
}							t_editor;

typedef struct				s_menu
{
	SDL_Surface				*background;
	SDL_Surface				*menu_title;
	SDL_Surface				*options[4];

	SDL_Rect				background_rect;
	SDL_Rect				menu_title_rect;
	SDL_Rect				options_rects[4];

	SDL_Color				text_color;
	int						current_option;
	int						prev_option;
	int						previous_state;
}							t_menu;

typedef struct				s_doom
{
	t_game					game;
	t_menu					menu;
	t_editor				editor;
	t_sdlmain				sdlmain;
	t_map					map;
	SDL_Surface				*wall_textures[10];
	int						state;
}							t_doom;



int							is_mouse_collide(t_vec mouse_pos, SDL_Rect collide_rect);

int 						check_collision(double pos_x, double pos_y, t_wall *walls);

int							blit(SDL_Surface *src, SDL_Rect *src_rect, SDL_Surface *dst, SDL_Rect *dst_rect);

void						init_rotate_wall(t_wall *new_wall, const t_wall_node *current_wall, const t_player *player);

int							is_in_map(t_vecdb *player);

SDL_Surface					*load_opti_bmp(char *file, SDL_Surface *dst_surf, Uint32 colorkey);
/*
** VECTOR FUNCTIONS
*/
double						get_magnitude(t_vecdb a, t_vecdb b);

void						multvec(t_vecdb *vecdb, double n);

t_vec						mult_vec(t_vec vec, int mult);

t_vec						create_vec(int x, int y);

void						give_vec_values(t_vec *vec, int x, int y);

void						vectorcpy(t_vec *one, const t_vec *two);

t_vec						vecdb_to_vec(t_vecdb vectordb);

t_vecdb						vec_to_vecdb(t_vec vector);

t_vecdb						rotate2d(t_vecdb vector, double angle);

t_vecdb						rotate2dcc(t_vecdb vector, double angle);

double						dot_product(t_vecdb a, t_vecdb b);

double						cross_product(t_vecdb a, t_vecdb b);

t_vecdb						create_vecdb(double x, double y);

double						cross_product_len(t_vec a, t_vec b, t_vec c);

double						get_point_distance(t_vecdb a, t_vecdb b);

/*
** INIT FUNCTIONS
*/
int							init_doom(t_doom *doom);

int							init_sdl_and_ttf();

int							init_game(t_game *game, t_sdlmain *sdlmain);

int							init_menu(t_menu *menu, t_sdlmain *sdlmain);

int							init_editor(t_editor *editor, t_sdlmain *sdlmain);

int							init_sdlmain(t_sdlmain *sdlmain);

int							init_editor_menu(t_editor *editor);

int							init_map(t_map *map);

int							init_wall_textures(SDL_Surface **wall_textures, SDL_Surface *winsurf);


/*
** INIT STRUCT FUNCTIONS
*/
int							init_gamesurfs_struct(t_gamesurfs *gamesurfs, t_sdlmain *sdlmain);

void						init_data_struct(t_data *data);

void						init_player_struct(t_player *player);

/*
** POLL EVENT FUNCTIONS
*/
int							handle_events(t_doom *doom);

void						check_quit(SDL_Event *event, int *state);

void						check_menu(SDL_Event *event, int *state, int *prev_state_ptr, int prev_state);

/*
** EVENT FUNCTIONS
*/

void						handle_keys(t_game *game, const Uint8 *keyboard_state);

int							editor_events(t_doom *doom);
/*
** PRINT MINIMAP FUNCTIONS
*/

int							draw_map(t_sdlmain *sdlmain, t_game *game, const t_map *map, char *hud_flags);

int							draw_full_fixedmap(SDL_Surface *surf, t_player *player, const t_map *map, SDL_Surface *winsurf);

int							draw_full_rotmap(SDL_Surface *surf, t_player *player, const t_map *map, SDL_Surface *winsurf);

void						draw_perspective_view(SDL_Surface *surf, t_player *player, SDL_Surface **wall_textures);

void							draw_view_recursive(SDL_Surface *surf, SDL_Surface **wall_textures, t_view view, t_sector_node *sector, t_player *player);
/*
** DRAWING FUNCTIONS
*/

void						fill_pix(SDL_Surface *surf, int x, int y, int color);

void						draw_line(const t_vec a, const t_vec b, SDL_Surface *surf, int color);

void						draw_border(SDL_Surface *surf, int color);

void						draw_border_options(SDL_Rect *rect, int color, SDL_Surface *surf);

/*
**	BLIT FUNCTIONS
*/

int							blit_editor(t_editor *editor, t_sdlmain *sdlmain);

int							blit_in_rect(SDL_Surface *surf, SDL_Surface *winsurf, int whichsurf);

int							blit_katana(t_gamesurfs *gamesurfs, SDL_Surface *dest, int *anim);

/*
** TEXT FUNCTIONS
*/

int							highlight_text(TTF_Font **font, SDL_Surface **surf, SDL_Color *color, char *text);

int							reset_text(TTF_Font **font, SDL_Surface **surf, SDL_Color *color, char *text);

/*
** NULL INIT FUNCTIONS
*/

void						null_doom_pointers(t_doom *doom);

void						null_game_pointers(t_game *game);

void						null_menu_pointers(t_menu *menu);

void						null_editor_pointers(t_editor *editor);

void						null_sdlmain_pointers(t_sdlmain *sdlmain);

void						null_map_pointers(t_map *map);

/*
** FREE FUNCTIONS
*/

void						quit_sdl_and_ttf();

int							free_menu(t_menu *menu);

int							free_game(t_game *game);

int							free_editor(t_editor *editor);

int							free_sdlmain(t_sdlmain *sdlmain);

int							free_wall_textures(SDL_Surface **wall_textures);

/*
** PARSE FUNCTIONS
*/

//int				parse_everything(t_wall *walls);

/*
** SDL_SUB_FUNCTIONS
*/

void						assign_sdlcolor(SDL_Color *color, Uint8 red, Uint8 green, Uint8 blue);

SDL_Rect					create_sdlrect(int x, int y, int w, int h);

void						assign_sdlrect(SDL_Rect *rect, t_vec origin, t_vec size);


/*
** MOVEMENT
*/

void						movement(t_player *player, t_vecdb move);

/*
** MENU FUNCTIONS
*/

/*
** CREATE SURFACES
*/

int							create_surfaces_editor(t_editor *editor, t_sdlmain *sdlmain);

/*
** LOOPS
*/

int							game_loop(t_doom *doom);

int 						menu_loop(t_doom *doom);

int							editor_loop(t_doom *doom);

/*
** ERROR FUNCTIONS
*/

int							error_return(const char *error_msg, const char *sdl_error);


/*
** EDITOR FUNCTIONS
*/

/*
** LINKED LIST FUNCTIONS
*/

/*
** SECTORS NODE FUNCTIONS
*/

t_sector_node				*add_sector_node(t_sector_node **sector_head);

void						set_sector_position(t_sector_node *sector_list);

t_sector_node				*get_sector_by_index(t_sector_node *sector_list, unsigned int index);

void						delete_sector(t_sector_node **node);

void						delete_sector_by_index(t_sector_node **sector_list,unsigned int index);

t_sector_node				*get_last_sector(t_sector_node *node);

int							copy_sector_list(t_sector_node *sector_list, t_sector_node **new_list);

int							count_sectors(t_sector_node *sector_list);

void						itt_sector_wall_heads(t_sector_node *sector_node, void (*f)(t_wall_node *wall_node));

void						free_sector_list(t_sector_node **sector_list);

/*
** WALL NODE FUNCTIONS
*/

t_wall_node					*add_wall_node(t_wall_node **wall_head, const t_wall_node *node);

t_wall_node					*create_wall_node(t_wall_node **wall_head, t_vecdb a, t_vecdb b, int tex_index);

void						free_wall_list(t_wall_node **wall_list);

t_vecdb						point_average_position(t_wall_node *wall_head);

t_wall_node					*delete_last_wall(t_wall_node **wall_list);

t_wall_node					*get_last_wall_node(t_wall_node *wall_list);

t_wall_node					*undo_wall(t_sector_node *node);

t_wall_node					*copy_wall_node(t_wall_node **wall_head, const t_wall_node *node);

/*
** DEBUG FUNCTIONS
*/

void						print_map_contents(const t_map *map);

int							copy_wall_list(t_wall_node *wall_list, t_wall_node **new_list);

int							wall_loop(t_wall_node *node);

int							count_walls(t_wall_node *wall_list);

void						set_wall_length(t_wall_node *head);
#endif
