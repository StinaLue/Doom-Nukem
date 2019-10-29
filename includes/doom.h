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
	int			texture[8][TEX_W * TEX_H];
	Uint32		*img_ptr;
	int			(*map_ptr)[MAX_MAP][MAX_MAP];
	long long	tex_y;
	int			quit;
	int			map_width;
	int			map_height;
	int			start_thread;
	int			end_thread;
	int			tex_x;
	int			tex_num;
	int			color;
	int			fps;
}				t_data;

typedef struct	s_player
{
	double		x;
	double		y;
	double		x_dir;
	double		y_dir;
	double		fov_x;
	double		fov_y;
	double		crouch;
	int			up_and_down;
}				t_player;

typedef struct	s_raycast
{
	int			map_x;
	int			map_y;
	double		camera;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	int			height;
	int			start_line;
	int			end_line;
	int			current_x;
}				t_raycast;

typedef struct	s_wall_finding
{
	double		distance_x_side;
	double		distance_y_side;
	double		dist_x_to_x;
	double		dist_y_to_y;
	double		distance_wall;
	double		wall_x;
	int			dir_step_x;
	int			dir_step_y;
	int			hit;
	int			side;
}				t_wall_find;

typedef struct	s_doom
{
	t_sdl		sdl;
	t_ttf		ttf;
	t_data		data;
	t_player	player;
	t_raycast	raycast;
	t_wall_find	find_wall;
}				t_doom;

void			init_doom(t_doom *doom, char *title);

void			init_sdl_struct(t_sdl *sdl);
void			init_ttf_struct(t_ttf *ttf);
void			init_data_struct(t_data *data, char *title);
void			init_player_struct(t_player *player, int map[MAX_MAP][MAX_MAP],
					int map_width, int map_height);
void			init_raycast_struct(t_raycast *raycast, double x, double y);

void			fill_map(int (*map)[MAX_MAP][MAX_MAP], char *title,
					int *map_width, int *map_height);
void			find_player_pos(t_player *player, int map[MAX_MAP][MAX_MAP],
					int map_width, int map_height);
void			verify_bordermap(int const (*map)[MAX_MAP][MAX_MAP],
					char *title, int map_width, int map_height);

void			free_sdl(SDL_Window **win);
void			free_ttf(t_ttf *ttf);
int				free_sdl_quit(SDL_Window **win);
int				free_sdl_ttf_quit(SDL_Window **win, t_ttf *ttf);

void			ray_init(t_raycast *raycast, t_player const *player);
void			raycasting(t_player const *player, t_raycast *raycast,
					t_wall_find *find_wall, t_data *data);
void			*iterate_raycast(void *param);

void			find_wall_init(t_raycast const *raycast,
					t_wall_find *find_wall);
void			find_wall_calculation(t_raycast *raycast,
					t_wall_find *find_wall, t_data const *data);

void			height_calculation(t_raycast *raycast, t_wall_find *find_wall,
					int updown, double crouch);

void			movement(t_player *player, t_data *data,
					const Uint8 *keyboard_state);

int				init_sdl(SDL_Window **win, SDL_Surface **surf);
int				init_ttf(t_ttf *ttf);

void			multithread(t_doom *doom);

void			fill_pix(Uint32 *pixels, int x, int y, int color);
void			draw_wall_and_floor(Uint32 *pixels, t_raycast *raycast);
void			draw_tex(t_player const *player, t_wall_find *find_wall,
					t_raycast *raycast, t_data *data);
void			draw_floor(t_player const *player, t_wall_find *find_wall,
					t_raycast *raycast, t_data *data);

void			fill_tex(int texture[8][TEX_W * TEX_H]);


int				is_valid_wall(int wall);

char			check_line(char *line);
void			check_title(char *title);
void			check_badwidth_map(int width, int mapwidth,
					void **line, int fd);
void			check_badheight_map(int height, int fd, char *title);

void			copy_line(char *charline, char *line, int width);

void			open_error(char *title);
void			invalid_char_error(char badchar, void **line, int fd);
int				argc_error(void);
int				size_error(void);
int				nbthreads_error(void);

char			*translate_fps(int fps);
int				init_fps_surf(t_ttf *ttf, int current_fps, int *start_clock);
void			update_fps(int *delta_clock, int *start_clock,
					int *current_fps, int *doom_fps);

#endif
