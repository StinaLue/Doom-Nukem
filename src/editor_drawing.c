/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:42:45 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 10:44:14 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_area(SDL_Surface *surf, t_wall_node *wall, t_editor *editor)
{
	t_vec	tmp_wall;
	int		j;
	int		color;
	int		i;

	color = (editor->start_sector.x == wall->start.x \
			&& editor->start_sector.y == wall->start.y) ? 0X00FF00 : 0XB11226;
	j = 0;
	tmp_wall.x = wall->start.x / SIZEMAP * editor->offset;
	tmp_wall.y = wall->start.y / SIZEMAP * editor->offset;
	while (j < 4)
	{
		i = 0;
		while (i < 2)
		{
			fill_pix(surf, tmp_wall.x + j, tmp_wall.y, color);
			fill_pix(surf, tmp_wall.x, tmp_wall.y + j, color);
			fill_pix(surf, tmp_wall.x + j, tmp_wall.y - j, color);
			fill_pix(surf, tmp_wall.x + j, tmp_wall.y + j, color);
			j = -j;
			i++;
		}
		j++;
	}
}

void	draw_lines_editor(t_editor *editor, SDL_Surface *editor_surf, \
					t_vec mouse)
{
	t_sector_node	*tmp_sect;
	t_wall_node		*tmp_wall;

	if (editor->edit_map.sector_head == NULL)
		return ;
	tmp_sect = editor->edit_map.sector_head;
	if (editor->start_sector_reached == 0)
		draw_line(multvec(mouse, editor->offset), \
		multvec(vecdb_to_vec(divvecdb(editor->wall_tmp.end, SIZEMAP)), \
			editor->offset), editor_surf, editor->wall_tmp.type_color);
	fill_area(editor_surf, &editor->wall_tmp, editor);
	while (tmp_sect != NULL)
	{
		tmp_wall = tmp_sect->wall_head;
		while (tmp_wall != NULL)
		{
			fill_area(editor_surf, tmp_wall, editor);
			draw_line(multvec(vecdb_to_vec(divvecdb(tmp_wall->end, SIZEMAP)), \
			editor->offset), multvec(vecdb_to_vec(divvecdb(tmp_wall->start, \
				SIZEMAP)), editor->offset), editor_surf, tmp_wall->type_color);
			tmp_wall = tmp_wall->next;
		}
		tmp_sect = tmp_sect->next;
	}
}
