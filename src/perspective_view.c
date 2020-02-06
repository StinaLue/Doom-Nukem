/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 12:18:07 by phaydont         ###   ########.fr       */
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

	//check vxs != 0
	tmp = 1;
	vcp = vxs(start.x - end.x, start.y - end.y, cross.x, cross.y);
	if (vcp != 0)
		tmp = cross_product(start, end) / vcp;
	intersection.x = tmp * cross.x;
	intersection.y = tmp * cross.y;
	return (intersection);
}

int			intersect_view(t_wall *wall, t_view view)
{
	if (cross_product(wall->start, wall->end) > 0 || (wall->start.y <= 0 && wall->end.y <= 0))
		return (0);

	if (cross_product(wall->start, view.left) < 0)
	{
		if (cross_product(wall->end, view.left) < 0)
			return (0);
		wall->start = simple_intersect(wall->start, wall->end, view.left);
	}
	else if (wall->start.y <= 0)
		return (0);

	if (cross_product(wall->end, view.right) > 0)
	{
		if (cross_product(wall->start, view.right) > 0)
			return (0);
		wall->end = simple_intersect(wall->start, wall->end, view.right);
	}
	else if (wall->end.y <= 0)
		return (0);
	return (1);
}

t_wall3d	create_perspective_wall(t_wall wall, SDL_Surface *surf, t_player *player, t_sector_node *sector)
{
	double		fov_ratio;
	double		x;
	double		top;
	double		bot;
	t_wall3d	display_wall;

	fov_ratio = player->fov.y / player->fov.x / wall.start.y * surf->w;
	x = wall.start.x * fov_ratio;
	top = (sector->ceiling_height - (player->posz + player->height)) * fov_ratio;
	bot = (sector->floor_height - (player->posz + player->height)) * fov_ratio;

	display_wall.top_left.x = surf->w / 2 + x / 2;
	display_wall.top_left.y = surf->h / 2 + top / 2 - player->view_z;
	display_wall.bottom_left.x = display_wall.top_left.x;
	display_wall.bottom_left.y = surf->h / 2 + bot / 2 - player->view_z;

	fov_ratio = player->fov.y / player->fov.x / wall.end.y * surf->w;
	x = wall.end.x * fov_ratio;
	top = (sector->ceiling_height - (player->posz + player->height)) * fov_ratio;
	bot = (sector->floor_height - (player->posz + player->height)) * fov_ratio;

	display_wall.top_right.x = surf->w / 2 + x / 2;
	display_wall.top_right.y = surf->h / 2 + top / 2 - player->view_z;
	display_wall.bottom_right.x = display_wall.top_right.x;
	display_wall.bottom_right.y = surf->h / 2 + bot / 2 - player->view_z;

	display_wall.dist_left = wall.start.y;
	display_wall.dist_right = wall.end.y;
	display_wall.start_pos = 0;
	display_wall.end_pos = 1;

	//sector = NULL;
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

void		set_wall_cuts(t_wall wall, t_wall tmp_wall, t_wall3d *display_wall)
{
	if (tmp_wall.start.x != tmp_wall.end.x)
	{
		display_wall->start_pos = (wall.start.x - tmp_wall.start.x) / (tmp_wall.end.x - tmp_wall.start.x);
		display_wall->end_pos = (wall.end.x - tmp_wall.start.x) / (tmp_wall.end.x - tmp_wall.start.x);
	}
	else if (tmp_wall.start.y != tmp_wall.end.y)
	{
		display_wall->start_pos = (wall.start.y - tmp_wall.start.y) / (tmp_wall.end.y - tmp_wall.start.y);
		display_wall->end_pos = (wall.end.y - tmp_wall.start.y) / (tmp_wall.end.y - tmp_wall.start.y);
	}
}

void		draw_view_recursive(SDL_Surface *surf, SDL_Surface **wall_textures, t_view view, t_sector_node *sector, t_player *player)
{
	t_wall		wall;
	t_wall3d	display_wall;
	t_wall_node	*current_wall;
	t_wall		tmp_wall;
	t_view		new_view;

	/*if (player->helper)
	{
		new_view = view;
		new_view.right.x += surf->w / 2;
		draw_line(create_vec(surf->w / 2, 0), vecdb_to_vec(new_view.right), surf, 0x333333);
		new_view.left.x += surf->w / 2 - 0.5;
		new_view.left.y += 0.5;
		draw_line(create_vec(surf->w / 2 - 0.5, 0), vecdb_to_vec(new_view.left), surf, 0x444444);
	}
*/
	current_wall = sector->wall_head;
	while (current_wall != NULL)
	{
		init_rotate_wall(&wall, current_wall, player);
		tmp_wall.start = wall.start;
		tmp_wall.end = wall.end;
		if (intersect_view(&wall, view)) //wall is at least partly in front of us && crosses the field of view
		{
			if (current_wall->neighbor_sector != NULL && current_wall->neighbor_sector != sector)
			{
				new_view.left = wall.start;
				new_view.right = wall.end;
				draw_view_recursive(surf, wall_textures, new_view, current_wall->neighbor_sector, player);
			}
			else
			{
				display_wall = create_perspective_wall(wall, surf, player, sector);//ajouter sector pour les infos de hauteur
				display_wall.length = current_wall->length;
				set_wall_cuts(wall, tmp_wall, &display_wall);
				draw_3dwall(display_wall, surf, current_wall, wall_textures);
				/*if (player->helper)
				{
					wall.start.x += surf->w / 2;
					wall.end.x += surf->w / 2;
					draw_line(vecdb_to_vec(wall.start), vecdb_to_vec(wall.end), surf, 0xFF0000);
				}*/
			}
		}
		current_wall = current_wall->next;
	}
}