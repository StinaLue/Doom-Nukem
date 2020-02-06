/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 17:15:38 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

double		vxs(double xstart, double ystart, double xtwo, double ytwo)
{
	return (xstart * ytwo - ystart * xtwo);
}

t_vecdb		intersect(t_vecdb start, t_vecdb end, t_vecdb origin, t_vecdb cross)
{
	t_vecdb intersection;
	intersection.x = vxs(vxs(start.x, start.y, end.x, end.y), start.x - end.x, vxs(origin.x, origin.y, cross.x, cross.y), origin.x - cross.x) / vxs(start.x - end.x, start.y - end.y, origin.x - cross.x, origin.y - cross.y);
	intersection.y = vxs(vxs(start.x, start.y, end.x, end.y), start.y - end.y, vxs(origin.x, origin.y, cross.x, cross.y), origin.y - cross.y) / vxs(start.x - end.x, start.y - end.y, origin.x - cross.x, origin.y - cross.y);
	return (intersection);
}

t_vecdb		simple_intersect(t_vecdb start, t_vecdb end, t_vecdb cross)
{
	t_vecdb	intersection;
	double	tmp;
	double	vcp;

	tmp = 1;
	vcp = vxs(start.x - end.x, start.y - end.y, cross.x, cross.y);
	if (vcp != 0)
		tmp = cross_product(start, end) / vcp;
	intersection.x = tmp * cross.x;
	intersection.y = tmp * cross.y;
	return (intersection);
}

int			intersect_view(t_segment *wall, t_segment view)
{
	if (cross_product(wall->a, wall->b) > 0 || (wall->a.y <= 0 && wall->b.y <= 0))
		return (0);

	if (cross_product(wall->a, view.a) < 0)
	{
		if (cross_product(wall->b, view.a) < 0)
			return (0);
		wall->a = simple_intersect(wall->a, wall->b, view.a);
	}
	else if (wall->a.y <= 0)
		return (0);

	if (cross_product(wall->b, view.b) > 0)
	{
		if (cross_product(wall->a, view.b) > 0)
			return (0);
		wall->b = simple_intersect(wall->a, wall->b, view.b);
	}
	else if (wall->b.y <= 0)
		return (0);
	return (1);
}

t_wall3d	create_perspective_wall(t_segment wall, SDL_Surface *surf, t_player *player, t_sector_node *sector)
{
	double		fov_ratio;
	double		x;
	double		top;
	double		bot;
	t_wall3d	display_wall;

	fov_ratio = player->view.b.y / player->view.b.x / wall.a.y * surf->w;
	x = wall.a.x * fov_ratio;
	top = (sector->ceiling_height - (player->posz + player->height)) * fov_ratio;
	bot = (sector->floor_height - (player->posz + player->height)) * fov_ratio;

	display_wall.top_left.x = (surf->w + x) / 2;
	display_wall.top_left.y = (surf->h + top) / 2 - player->view_z;
	display_wall.bottom_left.x = display_wall.top_left.x;
	display_wall.bottom_left.y = (surf->h + bot) / 2 - player->view_z;

	fov_ratio = player->view.b.y / player->view.b.x / wall.b.y * surf->w;
	x = wall.b.x * fov_ratio;
	top = (sector->ceiling_height - (player->posz + player->height)) * fov_ratio;
	bot = (sector->floor_height - (player->posz + player->height)) * fov_ratio;

	display_wall.top_right.x = (surf->w + x) / 2;
	display_wall.top_right.y = (surf->h + top) / 2 - player->view_z;
	display_wall.bottom_right.x = display_wall.top_right.x;
	display_wall.bottom_right.y = (surf->h + bot) / 2 - player->view_z;

	display_wall.dist_left = wall.a.y;
	display_wall.dist_right = wall.b.y;
	display_wall.start_pos = 0;
	display_wall.end_pos = 1;

	return (display_wall);
}

void	draw_3dwall(t_wall3d display_wall, SDL_Surface *surf, const t_wall_node *wall, SDL_Surface **wall_textures)
{
	if (ft_strncmp(surf->userdata, "yescolor", 8) != 0)
	{
		draw_line(display_wall.top_left, display_wall.top_right, surf, wall->color);
		draw_line(display_wall.top_right, display_wall.bottom_right, surf, wall->color);
		draw_line(display_wall.bottom_right, display_wall.bottom_left, surf, wall->color);
		draw_line(display_wall.bottom_left, display_wall.top_left, surf, wall->color);
	}
	else
		draw_texture(surf, wall_textures[wall->tex_index], &display_wall);
}

void		set_wall_cuts(t_segment wall, t_segment tmp_wall, t_wall3d *display_wall)
{
	if (fabs(tmp_wall.a.x - tmp_wall.b.x) > 0.001)
	{
		display_wall->start_pos = (wall.a.x - tmp_wall.a.x) / (tmp_wall.b.x - tmp_wall.a.x);
		display_wall->end_pos = (wall.b.x - tmp_wall.a.x) / (tmp_wall.b.x - tmp_wall.a.x);
	}
	else if (fabs(tmp_wall.a.y - tmp_wall.b.y) > 0.001)
	{
		display_wall->start_pos = (wall.a.y - tmp_wall.a.y) / (tmp_wall.b.y - tmp_wall.a.y);
		display_wall->end_pos = (wall.b.y - tmp_wall.a.y) / (tmp_wall.b.y - tmp_wall.a.y);
	}
}

void		draw_view_recursive(SDL_Surface *surf, SDL_Surface **wall_textures, t_segment view, t_sector_node *sector, t_player *player)
{
	t_segment		wall;
	t_wall3d		display_wall;
	t_wall_node		*current_wall;
	t_segment		tmp_wall;

	current_wall = sector->wall_head;
	while (current_wall != NULL)
	{
		wall = rotate_wall_relative(current_wall, player);
		tmp_wall.a = wall.a;
		tmp_wall.b = wall.b;
		if (intersect_view(&wall, view))//wall is in field of view
		{
			display_wall = create_perspective_wall(wall, surf, player, sector);//ajouter sector pour les infos de hauteur
			display_wall.length = current_wall->length;
			set_wall_cuts(wall, tmp_wall, &display_wall);
			if (current_wall->neighbor_sector != NULL && current_wall->neighbor_sector != sector)
			{
				draw_view_recursive(surf, wall_textures, wall, current_wall->neighbor_sector, player);
				//draw top and bottom of wall
			}
			else
				draw_3dwall(display_wall, surf, current_wall, wall_textures);
		}
		current_wall = current_wall->next;
	}
}