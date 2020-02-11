/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:54 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 16:47:10 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "SDL.h"
# include "SDL_ttf.h"
# include "al.h"
# include "alc.h"
# define TITLE "DOOM"

# define SQRT2 1.4142135623730950488
# define PLAYER_RADIUS 0.5
# define NB_WALL_TEXTURES 9
# define NB_SOUND_SOURCES 3
# define NB_SOUND_BUFFERS 11
# define PLAYER_HEIGHT 18
# define KNEE_HEIGHT 8
# define RUN 0.03
# define WALK 0.01

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

# define FHD_W 1920
# define FHD_H 1080

# define QHD_W 2560
# define QHD_H 1440

# define OFFSET 20

/*
**	map has 50 * 50 points
**	- > nbpoints = npointsrow (points per row) * nbpointsrow
*/
# define NBPOINTS 2501
# define NBPOINTSROW 50
# define NBTEXTURES	9
# define NBOPTIONS 8
# define NBHOVEROPTIONS 5
# define NBINSTRUCTS 10
# define SIZEMAP 50
# define COLOR_HOVER 0x6C1413
# define COLOR_PRESSED 0x00cc00
# define COLOR_NORMAL 0xffff00

/*
** HUD FLAGS
*/
# define ROT_MAP_SHOW 1
# define FIX_MAP_SHOW 2
# define TEXFLAG 4
# define HEALTH_STATUS 8
# define FPS_SHOW 16

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

typedef	struct				s_segment
{
	t_vecdb					a;
	t_vecdb					b;
}							t_segment;

typedef struct				s_enemy_info
{
	t_vec					enemy_spawn;
	int						which_enemy;
}							t_enemy_info;

typedef struct				s_wall_node
{
	struct s_wall_node		*next;
	struct s_wall_node		*previous;
	t_vecdb					start;
	t_vecdb					end;
	int						color;
	int						tex_index;
	int						sector_index;
	int						wall_type;
	int						type_color;
	struct s_sector_node	*neighbor_sector;
	double					length;
}							t_wall_node;

typedef struct				s_sector_node
{
	struct s_sector_node	*next;
	t_wall_node				*wall_head;
	t_vecdb					sector_center;
	double					floor_height;
	double					ceiling_height;
	int						wall_num;
	int						is_goal;
}							t_sector_node;

typedef struct				s_display_wall
{
	t_segment				relative;
	t_segment				intersect;
	t_vec					top_left;
	t_vec					top_right;
	t_vec					bottom_left;
	t_vec					bottom_right;
	double					start_pos;
	double					end_pos;
	double					dist_left;
	double					dist_right;
	double					length;
	int						top_limit;
	int						bot_limit;
	double					fov_ratio;
	SDL_Surface				*texture;
}							t_display_wall;

typedef struct				s_sound
{
	ALCdevice				*device;
	ALCcontext				*context;
	ALuint					source[NB_SOUND_SOURCES];
	ALuint					buffer[NB_SOUND_BUFFERS];
	ALenum					error;
}							t_sound;

typedef struct				s_sdlmain
{
	SDL_Window				*win;
	SDL_Surface				*win_surf;
	SDL_Event				event;
	TTF_Font				*font;
	t_sound					sound;
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
	SDL_Surface				*game_over;
	SDL_Surface				*victory;
	SDL_Surface				*fps;
	SDL_Surface				*hud_weapons_surf[2];
	TTF_Font				*fps_font;
	char					*fps_text;
	SDL_Color				fps_color;

	SDL_Rect				weapons_rect;
	SDL_Rect				hud_faces_rect;
	SDL_Rect				dst_fps_rect;
	SDL_Rect				hud_weapons_rect[2];
	int						hud_weapons_color[2];
	int						current_frame;
	int						anim_timer;
	int						hud_timer;
}							t_gamesurfs;

typedef struct				s_data
{
	char					hud_flags;
}							t_data;

typedef struct				s_view
{
	t_segment				fov;
	int						top_limit;
	int						bot_limit;
}							t_view;

typedef struct				s_enemy
{
	t_vecdb					pos;
	SDL_Surface				*texture;
	SDL_Rect				clip_tex;
	double					angle;
	int						health;
	int						state;
	ALuint					sound_src;
	int						anim_timer;
	int						current_frame;
}							t_enemy;

typedef struct				s_player
{
	t_sector_node			*sector;
	t_vecdb					pos;
	t_vecdb					move;
	t_vecdb					inertia;
	double					zinertia;
	double					angle;
	double					posz;
	double					height;
	double					view_z;
	t_segment				view;
	double					true_fov;
	double					movespeed;
	int						health;
	int						is_moving;
	int						anim;
	int						current_weapon;
}							t_player;

typedef struct				s_game
{
	t_gamesurfs				surfs;
	t_data					data;
	t_player				player;
	t_enemy					*enemy;
	int						(*weapon_anim[2])(t_gamesurfs *gamesurfs, \
								SDL_Surface *dest, int *anim);
}							t_game;

typedef struct				s_instr_menu
{
	SDL_Surface				*title;
	SDL_Surface				*instructs[NBINSTRUCTS];

	SDL_Rect				title_rect;
	SDL_Rect				instr_rect[NBINSTRUCTS];

	TTF_Font				*font_title;
	TTF_Font				*font;

	SDL_Color				text_color;
}							t_instr_menu;

typedef struct				s_options_menu
{
	SDL_Surface				*title;
	SDL_Surface				*options[NBOPTIONS];
	SDL_Surface				*hover_options[NBHOVEROPTIONS];
	SDL_Surface				*height_surf[2];

	SDL_Rect				title_rect;
	SDL_Rect				options_rect[NBOPTIONS];
	SDL_Rect				hover_opt_rect[NBHOVEROPTIONS];
	SDL_Rect				text_rect[NBTEXTURES];
	SDL_Rect				height_rect[2];
	SDL_Rect				player_rect;
	SDL_Rect				weapon_rect[2];
	SDL_Rect				scaled_weapon_rect[2];

	TTF_Font				*font_title;
	TTF_Font				*font;

	SDL_Color				text_color;
	int						bord_color_text[NBTEXTURES];
	int						bord_color_height[2];
	int						bord_hover_color_opt[NBHOVEROPTIONS];
	int						bord_color_weapon[2];
	int						activ_tex;
	int						activ_music;
	int						activ_weapon;
	int						typing_filename;
	int						activ_height[2];
	double					height_ceiling;
	double					height_floor;
	char					file_name[16];
}							t_options_menu;

typedef struct				s_map
{
	char					name[16];
	t_sector_node			*sector_head;
	t_enemy_info			*enemy_info;
	t_vec					player_spawn;
	int						num_sectors;
	int						num_enemies;
	int						which_music;
	int						weapon_choice;
}							t_map;

typedef struct				s_editor
{
	SDL_Surface				*editor_surf;
	SDL_Surface				*opt_surf;
	SDL_Surface				*instr_surf;
	SDL_Surface				*mouse_surf;
	SDL_Surface				**wall_textures;
	SDL_Surface				**enemy_textures;
	SDL_Surface				*alert_convex_surf;
	SDL_Surface				*alert_loading_surf;
	SDL_Surface				*loading_success_surf;
	SDL_Surface				*player_face_surf;
	SDL_Surface				*weapon_texture;

	SDL_Rect				editor_rect;
	SDL_Rect				options_rect;
	SDL_Rect				instr_rect;
	SDL_Rect				mouse_rect;
	SDL_Rect				player_face_rec;
	SDL_Rect				alert_convex_rect;
	SDL_Rect				alert_loading_rect;
	SDL_Rect				loading_success_rect;
	SDL_Rect				enemy_rect[2];

	t_sector_node			*current_sector;
	t_sector_node			*selected_sector;
	t_wall_node				*current_wall;

	int						offset;
	int						start_sector_reached;
	int						color_change;
	int						show_convex_alert;
	int						show_loading_alert;
	int						loading_success;
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

void						soft_reset_player(t_player *player, t_map *map);

int							load_wav(char *file, ALuint buffer);

int							is_mouse_collide(t_vec mouse_pos, \
												SDL_Rect collide_rect);

int							check_collision(double pos_x, double pos_y, \
											t_segment *walls);

int							blit(SDL_Surface *src, SDL_Rect *src_rect, \
									SDL_Surface *dst, SDL_Rect *dst_rect);

t_segment					rotate_wall_relative(const t_wall_node \
								*current_wall, const t_player *player);

int							is_in_map(t_vecdb *player);

SDL_Surface					*load_opti_bmp(char *file, SDL_Surface *dst_surf, \
											Uint32 colorkey);

int							copy_map(const t_map *srcmap, t_map *dstmap);

/*
** MAP PARSING FUNCTIONS
*/
int							write_map(t_map *map);

int							write_sectors(int fd, \
							t_sector_node *sector_head, int num_sectors_file);

int							read_map(const char *path, t_map *map);

int							read_sectors(int fd, \
							t_sector_node **sector_head, int num_sectors_file);

/*
** MAP FUNCTIONS
*/
int							add_enemy_info(t_map *map, t_vec newspawn, \
											int new_which_enem);

int							is_sector_occupied(t_sector_node *sector, \
												t_map *map);

int							delete_enemy_info(t_map *map, t_vec delspawn);
/*
** VECTOR FUNCTIONS
*/
double						get_magnitude(t_vecdb a, t_vecdb b);

t_vecdb						multvecdb(t_vecdb vecdb, double mult);

t_vec						multvec(t_vec vec, int mult);

t_vecdb						divvecdb(t_vecdb vecdb, double div);

t_vec						divvec(t_vec vec, int div);

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

void						set_vec_values(t_vec *src, t_vec *dst);

void						set_vecdb_values(t_vecdb *src, t_vecdb *dst);

t_vecdb						vecdb_diff(t_vecdb a, t_vecdb b);

t_vec						vec_diff(t_vec a, t_vec b);

t_vecdb						vecdb_mult(t_vecdb a, t_vecdb b);

t_vec						vec_mult(t_vec a, t_vec b);

t_vecdb						vecdb_add(t_vecdb a, t_vecdb b);

t_vec						vec_add(t_vec a, t_vec b);

t_vec						reset_vec(t_vec *vector);

t_vecdb						reset_vecdb(t_vecdb *vector);

int							compare_vec(t_vec *vector1, t_vec *vector2);

/*
** INIT FUNCTIONS
*/
int							init_doom(t_doom *doom);

int							init_sdl_and_ttf();

int							init_game(t_game *game, \
										t_sdlmain *sdlmain, t_map *map);

int							init_menu(t_menu *menu, t_sdlmain *sdlmain);

int							init_editor(t_editor *editor, t_sdlmain *sdlmain);

int							init_sdlmain(t_sdlmain *sdlmain);

int							init_editor_menu(t_editor *editor);

int							init_wall_textures(SDL_Surface **wall_textures, \
												SDL_Surface *winsurf);

void						init_source(ALuint src, ALfloat pitch, \
											ALfloat gain, int loop);

t_view						init_view(t_player *player, SDL_Surface *surf);

/*
** INIT STRUCT FUNCTIONS
*/
int							init_gamesurfs_struct(t_gamesurfs *gamesurfs, \
													t_sdlmain *sdlmain);

void						init_data_struct(t_data *data);

void						init_player_struct(t_player *player, t_map *map);

int							init_enemies(t_game *game, t_map *map);

/*
** POLL EVENT FUNCTIONS
*/
int							handle_events(t_doom *doom);

void						check_quit(SDL_Event *event, int *state);

void						check_menu(SDL_Event *event, \
							int *state, int *prev_state_ptr, int prev_state);

/*
** EVENT FUNCTIONS
*/
void						handle_keys(t_doom *doom, \
										const Uint8 *keyboard_state);

int							editor_events(t_doom *doom, t_sdlmain *sdlmain);

void						set_height(t_options_menu *menu, SDL_Surface *surf);

/*
**	GAME FUNCTIONS
*/
int							player_hurt_anim(int health, SDL_Rect *surf_rect);
SDL_Rect					find_srcrect_enemy(t_enemy *enemy);

SDL_Rect					find_dstrect_enemy(t_enemy *enemy, \
									t_player *player, SDL_Surface *dest);

int							create_game_surfaces(t_gamesurfs *gamesurfs, \
									t_sdlmain *sdlmain);

int							load_game_textures(t_gamesurfs *gamesurfs);
/*
** PRINT MINIMAP FUNCTIONS
*/
int							draw_map(t_sdlmain *sdlmain, t_game *game, \
									const t_map *map, char *hud_flags);

int							draw_full_fixedmap(SDL_Surface *surf, \
									t_player *player, const t_map *map, \
									SDL_Surface *winsurf);

int							draw_full_rotmap(SDL_Surface *surf, \
										t_player *player, const t_map *map, \
										SDL_Surface *winsurf);

void						draw_perspective_view(SDL_Surface *surf, \
								t_player *player, SDL_Surface **wall_textures);

void						draw_view_recursive(SDL_Surface *surf, \
									SDL_Surface **wall_textures, t_view view, \
									t_sector_node *sector, t_player *player);
/*
** DRAWING FUNCTIONS
*/
void						fill_pix(SDL_Surface *surf, int x, \
										int y, int color);

void						draw_line(const t_vec a, \
							const t_vec b, SDL_Surface *surf, int color);

void						draw_border(SDL_Surface *surf, int color);

void						draw_border_options(SDL_Rect *rec, \
									int color, SDL_Surface *surf);

void						draw_lines_editor(t_editor *editor, \
								SDL_Surface *editor_surf, t_vec mouse);

/*
**	BLIT FUNCTIONS
*/
int							blit_editor(t_editor *editor, t_sdlmain *sdlmain);

int							blit_in_rect(SDL_Surface *surf, \
									SDL_Surface *winsurf, int whichsurf);

int							blit_katana(t_gamesurfs *gamesurfs, \
									SDL_Surface *dest, int *anim);

int							blit_uzi(t_gamesurfs *gamesurfs, \
									SDL_Surface *dest, int *anim);
int							blit_loading_alert(t_editor *editor);

int							blit_alert(t_editor *editor);

int							blit_editor_surf(t_editor *editor, \
											t_sdlmain *sdlmain);

int							editor_blit_weapons(t_editor *editor, \
											t_options_menu *menu);

int							blit_options(t_editor *editor);

int							blit_height(t_editor *editor);

int							game_blit_hud(t_map *map, t_game *game, \
									int itt, Uint32 startclock);

int							blit_enemies(t_game *game, SDL_Surface *dest, \
											t_map *map);

int							blit_weapon(t_game *game, SDL_Surface *dest, \
										int weapon, int available_weapons);
/*
** TEXT FUNCTIONS
*/
int							highlight_text(TTF_Font **font, \
							SDL_Surface **surf, SDL_Color *color, char *text);

int							reset_text(TTF_Font **font, SDL_Surface **surf, \
											SDL_Color *color, char *text);

void						prepend_str(const char *to_prepend, \
							const char *str, char *new_str, int full_size);

/*
** NULL INIT FUNCTIONS
*/
void						null_doom_pointers(t_doom *doom);

void						null_game_pointers(t_game *game);

void						null_menu_pointers(t_menu *menu);

void						null_editor_pointers(t_editor *editor);

void						null_sdlmain_pointers(t_sdlmain *sdlmain);

void						null_map_pointers(t_map *map);

void						null_walltextures_pointers(SDL_Surface \
														**wall_textures);

void						null_instr_pointers(t_editor *editor);

/*
** FREE FUNCTIONS
*/
void						quit_sdl_and_ttf();

int							free_menu(t_menu *menu);

int							free_game(t_game *game, t_map *map);

int							free_editor(t_editor *editor);

int							free_sdlmain(t_sdlmain *sdlmain);

int							free_wall_textures(SDL_Surface **wall_textures);

int							free_map(t_map *map);

void						free_enemies(t_game *game, int num_enemies);

void						free_and_null_surf(SDL_Surface *surf);

int							free_height(t_editor *editor);

/*
** SDL_SUB_FUNCTIONS
*/
void						assign_sdlcolor(SDL_Color *color, \
									Uint8 red, Uint8 green, Uint8 blue);

SDL_Rect					create_sdlrect(int x, int y, int w, int h);

void						assign_sdlrect(SDL_Rect *rect, \
										t_vec origin, t_vec size);

void						assign_sdlrect_invert(SDL_Rect *rect, \
											t_vec origin, t_vec size);

/*
** MOVEMENT
*/
void						movement(t_player *player, t_vecdb move);

void						mouse_movement(SDL_MouseMotionEvent event, \
											t_doom *doom);

void						update_player(t_player *player);

void						jump(t_player *player);
/*
** MENU FUNCTIONS
*/

/*
** CREATE SURFACES
*/
int							create_surfaces_editor(t_editor *editor, \
													t_sdlmain *sdlmain);

/*
** LOOPS
*/
int							game_loop(t_doom *doom);

int							menu_loop(t_doom *doom);

int							editor_loop(t_doom *doom);

/*
** ERROR FUNCTIONS
*/
int							error_return(const char *error_msg, \
										const char *sdl_error);

int							error_return_map(const char *error_msg, \
									const char *errstr, int fd);

/*
** EDITOR FUNCTIONS
*/
int							reset_init_editor(t_editor *editor, \
											t_sdlmain *sdlmain);

void						event_mouse(t_editor *editor, t_sdlmain *sdlmain);

void						event_keydown(t_editor *editor, \
									t_doom *doom, t_sdlmain *sdlmain);

void						event_keydown_a_to_l(t_doom *doom, \
								t_editor *editor, SDL_Keycode key);

void						event_keydown_m_to_q(t_doom *doom, \
								t_editor *editor, SDL_Keycode key);

void						event_keydown_r_to_u(t_doom *doom, \
								t_editor *editor, SDL_Keycode key, \
								Uint8 repeat);

int							copy_enemy_info(const t_enemy_info *src, \
									t_enemy_info **dst, int num_enemies);

void						get_enemysprite_rect(SDL_Rect *rect, \
									int which_enemy, SDL_Surface *sprite_sheet);

void						remove_highlight_sector(t_sector_node *sector);

int							create_ceiling_height(t_editor *editor);

int							create_floor_height(t_editor *editor);

int							create_hover_opt(t_editor *editor, t_vec origin, \
											int i, const char *str);

int							create_opt_str(t_editor *editor, t_vec origin, \
											int i, const char *str);

int							create_instruct_str(t_editor *editor, \
										t_vec origin, int i, const char *str);

int							init_options_menu(t_editor *editor);

int							init_instr_menu(t_editor *editor, \
												SDL_Surface *surf);

void						event_handle_input(t_editor *editor, Uint32 type, \
								SDL_Keycode key, char *text);

void						key_event_height(t_editor *editor, SDL_Event ev, \
										t_options_menu *menu);

void						mouse_collide1(t_sdlmain *sdlmain, \
										t_editor *editor, t_options_menu *menu);
void						mouse_collide2(t_sdlmain *sdlmain, \
							t_editor *editor,t_options_menu *menu, Uint8 button);

void						create_walls_on_map(t_vec mouse, t_editor *editor, \
													t_wall_node *wall);

void						base_color_rect_options(t_options_menu *menu);
/*
** LINKED LIST FUNCTIONS
*/

/*
** SECTORS NODE FUNCTIONS
*/
t_sector_node				*add_sector_node(t_sector_node **sector_head);

void						set_sector_position(t_sector_node *sector_list);

t_sector_node				*get_sector_by_pos(t_sector_node *sector_head, \
													t_vecdb point);

t_sector_node				*get_sector_by_index(t_sector_node *sector_list, \
												unsigned int index);

void						delete_sector(t_sector_node **node);

void						delete_sector_by_index(t_sector_node \
									**sector_list, unsigned int index);

void						delete_sector_by_address(t_sector_node \
									**sector_list, t_sector_node *node);

t_sector_node				*get_last_sector(t_sector_node *node);

t_sector_node				*get_previous_sector(t_sector_node *list, \
													t_sector_node *node);

int							copy_sector_list(t_sector_node *sector_list, \
												t_sector_node **new_list);

int							count_sectors(t_sector_node *sector_list);

void						itt_sector_wall_heads(t_sector_node *sector_node, \
											void (*f)(t_wall_node *wall_node));

int							itt_sectors_true(t_sector_node *sector_node, \
											int (*f)(t_sector_node *));

void						free_sector_list(t_sector_node **sector_list);

void						set_sectors_clockwise(t_sector_node *sector_head);

void						flip_walls(t_sector_node *sector);

/*
** WALL NODE FUNCTIONS
*/
t_wall_node					*add_wall_node(t_wall_node **wall_head, \
											const t_wall_node *node);

t_wall_node					*create_wall_node(t_wall_node **wall_head, \
										t_vecdb a, t_vecdb b, int tex_index);

void						free_wall_list(t_wall_node **wall_list);

t_vecdb						point_average_position(t_wall_node *wall_head);

t_wall_node					*delete_last_wall(t_wall_node **wall_list);

t_wall_node					*get_last_wall_node(t_wall_node *wall_list);

t_wall_node					*undo_wall(t_sector_node *node);

t_wall_node					*insert_wall_node(t_wall_node **wall_list);

t_wall_node					*copy_wall_node(t_wall_node **wall_head, \
												const t_wall_node *node);

int							copy_wall_list(t_wall_node *wall_list, \
											t_wall_node **new_list);

/*
** DEBUG FUNCTIONS
*/
void						print_map_contents(const t_map *map);

void						print_vec(const t_vec *vec, const char *name);

void						print_vecdb(const t_vecdb *vecdb, const char *name);

/*
** EDITOR CHECK FUNCTIONS
*/
int							check_convex_sector(t_sector_node *sector);

int							check_clockwise_sector(t_sector_node *sector);

/*
** TEXTURE MAPPING
*/
void						draw_texture(SDL_Surface *surf, SDL_Surface *tex, \
											t_display_wall *dsp, int type);

/*
** SOUND FUNCTIONS
*/
void						stop_enem_soundsources(t_enemy *enemies, \
													int nb_enemies);

int							is_buffer_playing(ALuint src, ALuint buffer);

void						init_source(ALuint src, ALfloat pitch, \
											ALfloat gain, int loop);

int							is_source_playing(ALuint source);

int							play_sound(t_game *game, t_sdlmain *sdlmain, \
												t_map *map);

/*
** MUSIC FUNCTIONS
*/
void						play_win_music(t_game *game, \
								t_sdlmain *sdlmain, t_doom *doom);

void						play_gameover_music(t_game *game, \
								t_sdlmain *sdlmain, t_doom *doom);

void						play_game_music(t_game *game, \
								t_sdlmain *sdlmain, t_doom *doom);

void						play_editor_music(t_sdlmain *sdlmain, t_doom *doom);

/*
** END LEVEL LOOPS FUNCTIONS
*/

void						game_over_loop(t_doom *doom);

void						win_loop(t_doom *doom);

#endif
