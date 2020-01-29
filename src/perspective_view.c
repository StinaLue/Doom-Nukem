/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:29:58 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/28 11:28:41 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

double vxs(double xstart, double ystart, double xtwo, double ytwo)
{
	return (xstart * ytwo - ystart * xtwo);
}

t_vecdb intersect(t_vecdb start, t_vecdb end, t_vecdb origin, t_vecdb cross)
{
	t_vecdb intersection;
	intersection.x = vxs(vxs(start.x, start.y, end.x, end.y), start.x - end.x, vxs(origin.x, origin.y, cross.x, cross.y), origin.x - cross.x) / vxs(start.x - end.x, start.y - end.y, origin.x - cross.x, origin.y - cross.y);
	intersection.y = vxs(vxs(start.x, start.y, end.x, end.y), start.y - end.y, vxs(origin.x, origin.y, cross.x, cross.y), origin.y - cross.y) / vxs(start.x - end.x, start.y - end.y, origin.x - cross.x, origin.y - cross.y);
	return (intersection);
}

t_vecdb simple_intersect(t_vecdb start, t_vecdb end, t_vecdb cross)
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

int	limit_value(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}
/*
t_vecdb	interpolate_tex(int tex_size, t_vec current_pos)
{
	t_vecdb newvecdb;
		// Find X val code of texture to use
	int CurrentXValOfWall = CurrentXValOfWall * ((WallLineTextureLength * WallInFOVRatio) / WallWidth);  // Find the ratio of how much of the wall texture to use based on how much of the wall is in the FOV compared to the total width of the wall being drawn.
	const float CurrentXValOfWallTexture = (CurrentXValOfWall + CurrentXValOfWallStart) % tex_size; // Find the X value to use to draw the wall in texture space.  Modulo so we tile texture horizontally across the entire wall every time we get to the end of the WallTexture

// Find Y value code of texture to use
	const int TotalWallVlineHeight = WallDrawBottom - WallDrawTop; // Total height of the column being drawn.
	const float WallTextureVlineMinValue = (TrimmedTop / ( TotalWallVlineHeight + TrimmedTop + TrimmedBottom)) * tex_size; // Used to set a minimum y value in texture space if the wall is getting clipped due to being above the FOV
	const float WallTextureVlineMaxValueRatio = ((TrimmedTop + TotalWallVlineHeight) / (TotalWallVlineHeight + TrimmedTop + TrimmedBottom)); // Used to find the ratio used to set a maximum y value in texture space if the wall is getting clipped due to being below the FOV
	float VLineToTextureSizeRatio = (float)tex_size / (float)(TotalWallVlineHeight + TrimmedTop + TrimmedBottom); // Used to find the ratio between the Wall Texture Size & the total height of the wall.
	VLineToTextureSizeRatio *= WallTextureVlineMaxValueRatio; // Used to both limit the maximum value (in texture space) of the y co-ord of the wall being drawn in addition to squashing all 
}
*/

void draw_vertical(t_vec top, t_vec bottom, SDL_Surface *surf, int color)
{
	top.y = limit_value(top.y, 0, surf->h - 1);
	bottom.y = limit_value(bottom.y, 0, surf->h - 1);
	while (top.y >= bottom.y)
	{
		fill_pix(surf, top.x, top.y, color);
		top.y--;
	}
}

void	fill_wall_color(SDL_Surface *surf, const t_wall3d *display_wall, int color)
{
	double x;
	t_vec current_top;
	t_vec current_bottom;

	if (display_wall->top_right.x > display_wall->top_left.x)
	{
		x = display_wall->top_right.x;
		while (x > display_wall->top_left.x)
		{
			current_top.y = display_wall->top_right.y + (x - display_wall->top_right.x) * (long)(display_wall->top_left.y - display_wall->top_right.y) / (abs(display_wall->top_left.x - display_wall->top_right.x) == 0 ? 1 : (display_wall->top_left.x - display_wall->top_right.x));
			current_bottom.y = display_wall->bottom_right.y + (x - display_wall->top_right.x) * (long)(display_wall->bottom_left.y - display_wall->bottom_right.y) / (abs(display_wall->top_left.x - display_wall->top_right.x) ==0 ? 1 : (display_wall->top_left.x - display_wall->top_right.x));
			current_top.x = x;
			current_bottom.x = x;
			draw_vertical(current_top, current_bottom, surf, color);
			x--;
		}
	}
}

int		intersect_fov(t_wall *wall, t_vecdb fov)
{
	if (cross_product(wall->end, fov) > 0)
	{
		if (cross_product(wall->start, fov) > 0)
			return (0);
		wall->end = simple_intersect(wall->start, wall->end, fov);
	}
	else if (wall->end.y < 0)
		return (0);

	fov.x *= -1;
	if (cross_product(wall->start, fov) < 0)
	{
		if (cross_product(wall->end, fov) < 0)
			return (0);
		wall->start = simple_intersect(wall->start, wall->end, fov);
	}
	else if (wall->start.y < 0)
		return (0);

	return (1);
}


int		intersect_view(t_wall *wall, t_view view)
{
	if (cross_product(wall->start, wall->end) > 0)
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

t_wall3d	create_perspective_wall(t_wall wall, SDL_Surface *surf, t_player *player)
{
	double		fov_ratio;
	int			x;
	int			y;
	double		surf_center;
	t_wall3d	display_wall;

	surf_center = ((double)surf->w - 1) / 2;

	fov_ratio = player->fov.y / player->fov.x / wall.start.y;
	x = surf->w / 2 + wall.start.x * fov_ratio * surf_center;
	y = fov_ratio * surf->w;

	display_wall.top_left.x = x;
	display_wall.top_left.y = surf->h / 2 - player->view_z + y;
	display_wall.bottom_left.x = display_wall.top_left.x;
	display_wall.bottom_left.y = surf->h / 2 - player->view_z - y;

	fov_ratio = player->fov.y / player->fov.x / wall.end.y;
	x = surf->w / 2 + wall.end.x * fov_ratio * surf_center;
	y = fov_ratio * surf->w;

	display_wall.top_right.x = x;
	display_wall.top_right.y = surf->h / 2 - player->view_z + y;
	display_wall.bottom_right.x = display_wall.top_right.x;
	display_wall.bottom_right.y = surf->h / 2 - player->view_z - y;

	return (display_wall);
}

void	draw_3dwall(t_wall3d display_wall, SDL_Surface *surf, const t_wall_node *wall, SDL_Surface **wall_textures)
{
	if (ft_strncmp(surf->userdata, "yescolor", 8) == 0)
	{
		//fill_wall_texture(surf, &display_wall, wall_textures[wall->tex_index]);
		draw_texture(surf, wall_textures[wall->tex_index], &display_wall);
	}
	else
	{
		draw_line(display_wall.top_left, display_wall.top_right, surf, wall->color); // drawing a line for each line around wall
		draw_line(display_wall.top_right, display_wall.bottom_right, surf, wall->color);
		draw_line(display_wall.bottom_right, display_wall.bottom_left, surf, wall->color);
		draw_line(display_wall.bottom_left, display_wall.top_left, surf, wall->color);
	}
}

void	draw_view_recursive(SDL_Surface *surf, SDL_Surface **wall_textures, t_view view, t_sector_node *sector, t_player *player)
{
	t_wall		wall;
	t_wall3d	display_wall;
	t_wall_node	*current_wall;
	t_vecdb		tmp_wall;
	t_view		new_view;
	current_wall = sector->wall_head;

	if (player->helper)
	{
		new_view = view;
		new_view.right.x += surf->w / 2;
		draw_line(create_vec(surf->w / 2, 0), vecdb_to_vec(new_view.right), surf, 0x333333);
		new_view.left.x += surf->w / 2 - 0.5;
		new_view.left.y += 0.5;
		draw_line(create_vec(surf->w / 2 - 0.5, 0), vecdb_to_vec(new_view.left), surf, 0x444444);
	}

	while (current_wall != NULL)
	{
		init_rotate_wall(&wall, current_wall, player);
		tmp_wall.x = wall.start.x;
		tmp_wall.y = wall.end.x;
		if (current_wall->neighbor_sector != NULL)
		{
			new_view.left.x = 1; //debug purposes
		}
		if ((wall.start.y > 0 || wall.end.y > 0) && intersect_view(&wall, view)) //wall is at least partly in front of us && crosses the field of view
		{
			if (current_wall->neighbor_sector != NULL && current_wall->neighbor_sector != sector)
			{
				new_view.left = wall.start;
				new_view.right = wall.end;
				draw_view_recursive(surf, wall_textures, new_view, current_wall->neighbor_sector, player);
			}
			else
			{
				display_wall = create_perspective_wall(wall, surf, player);//ajouter sector pour les infos de hauteur
				if ((tmp_wall.y - tmp_wall.x) == 0)
				{
					display_wall.start_pos = 0;
					display_wall.end_pos = 1;
				}
				else
				{
					display_wall.start_pos = (wall.start.x - tmp_wall.x) / (tmp_wall.y - tmp_wall.x);
					//printf("start_pos = %f\n", display_wall.start_pos);
					display_wall.end_pos = 1 - (wall.end.x - tmp_wall.x) / (tmp_wall.y - tmp_wall.x);
				}
				
				draw_3dwall(display_wall, surf, current_wall, wall_textures);

				if (player->helper)
				{
					wall.start.x += surf->w / 2;
					wall.end.x += surf->w / 2;
					draw_line(vecdb_to_vec(wall.start), vecdb_to_vec(wall.end), surf, 0xFF0000);
				}
			}
		}
		current_wall = current_wall->next;
	}
}