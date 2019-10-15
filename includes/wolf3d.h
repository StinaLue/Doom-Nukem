/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:54 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/15 16:58:12 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_3D
# define WOLF_3D

# include "SDL.h"
# include "SDL_ttf.h"
# define TITLE "WOLF3D"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define NB_THREADS 6
# define MAX_MAP 100
# define MAX_LOOK_DOWN -400
# define MAX_LOOK_UP 400

# define TEX_W 64
# define TEX_H 64

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
	SDL_Surface		*surf_message;
	SDL_Texture		*message;
	char			*fps;
	SDL_Color		color;
	SDL_Rect		rect;
}						t_ttf;

typedef struct			s_data
{
	int				texture[4][TEX_W * TEX_H];
	int				*img_ptr;
	int				(*map_ptr)[MAX_MAP][MAX_MAP];
	int				quit;
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
	double			cam_vector_x;
	double			cam_vector_y;
	double				crouch;
	int				up_and_down;
}						t_player;

typedef struct			s_raycast
{
	int				map_x;
	int				map_y;
	double			cam_x;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	int				height;
	int				start_line;
	int				end_line;
}						t_raycast;

typedef struct			s_wall_finding
{
	double			distance_x_side;
	double			distance_y_side;
	double			dist_x_to_x;
	double			dist_y_to_y;
	double			distance_wall;
	int				dir_step_x;
	int				dir_step_y;
	int				hit;
	int				side;
}						t_wall_finding;

typedef struct			s_wolf
{
	t_sdl			sdl;
	t_ttf			ttf;
	t_data			data;
	t_player		player;
	t_raycast		raycast;
	t_wall_finding			find_wall;
}						t_wolf;

void    init_wolf(t_wolf *wolf, char *title);

void				init_sdl_struct(t_sdl *sdl);
void	init_ttf_struct(t_ttf *ttf);
void	init_data_struct(t_data *data, char *title);
void		init_player_struct(t_player *player, int map[MAX_MAP][MAX_MAP], int map_width, int map_height);
void	init_raycast_struct(t_raycast *raycast, double x, double y);

void	fill_map(int (*map)[MAX_MAP][MAX_MAP], char *title, int *map_width, int *map_height);
void		find_player_pos(t_player *player, int map[MAX_MAP][MAX_MAP], int map_width, int map_height);
void    verify_bordermap(int const (*map)[MAX_MAP][MAX_MAP], char *title, int map_width, int map_height);

void	free_SDL(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex);
void	free_TTF(t_ttf *ttf);

void	ray_init(t_raycast *raycast, t_wall_finding *find_wall, t_player const *player, int x);
void	raycasting(t_player const *player, t_raycast *raycast, t_wall_finding *find_wall, t_data *data, int x);
void	*iterate_raycast(void *param);

void	find_wall_init(t_raycast const *raycast, t_wall_finding *find_wall);
void	find_wall_calculation(t_raycast *raycast, t_wall_finding *find_wall, t_data const *data);

void	height_calculation(t_raycast *raycast, t_wall_finding *find_wall, int updown, double crouch);
void	draw_vertical(int *pixels, int x, int y1, int y2, int color);

void	movement(t_player *player, t_data *data, const Uint8 *keyboard_state_array);

int	init_SDL(SDL_Window **win, SDL_Renderer **ren, SDL_Texture **tex);
int	init_TTF(t_ttf *ttf);

void	multithread(t_wolf *wolf);

void	fill_pix(int *pixels, int x, int y, int color);
void	draw_vertical(int *pixels, int x, int y1, int y2, int color);

void	fill_tex(int texture[4][TEX_W * TEX_H]);

#endif
