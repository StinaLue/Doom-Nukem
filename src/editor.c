/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:41:18 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 10:44:14 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

int		round_num(double num, int offset)
{
	double result;

	result = num / (double)offset;
	return (num < 0 ? result - 0.5 : result + 0.5);
}

void	draw_editor(SDL_Surface *editor_surf,
					t_editor *editor, t_sdlmain *sdlmain)
{
	int y;
	int x;
	int i;

	y = 0;
	i = 0;
	while (y < NBPOINTSROW * editor->offset)
	{
		y += editor->offset;
		x = 0;
		while (x < NBPOINTSROW * editor->offset)
		{
			x += editor->offset;
			fill_pix(editor_surf, x, y, 0x606060);
			editor->grid_values[i].x = x / editor->offset;
			editor->grid_values[i].y = y / editor->offset;
			i++;
		}
	}
	sdlmain->mouse_pos.y = sdlmain->mouse_pos.y == 0 ? 1 : sdlmain->mouse_pos.y;
	sdlmain->mouse_pos.x = sdlmain->mouse_pos.x == 0 ? 1 : sdlmain->mouse_pos.x;
	sdlmain->mouse_pos.y = y / editor->offset - sdlmain->mouse_pos.y + 1;
	sdlmain->mouse_pos.y = sdlmain->mouse_pos.y == 0 ? 1 : sdlmain->mouse_pos.y;
}

void	prepare_editor(t_sdlmain *sdlmain, t_editor *editor, int offset_border)
{
	assign_sdlrect(&editor->mouse_rect, create_vec(sdlmain->mouse_pos.x \
					- 15, sdlmain->mouse_pos.y - 15), create_vec(15, 15));
	sdlmain->mouse_pos.x = round_num(sdlmain->mouse_pos.x, editor->offset);
	sdlmain->mouse_pos.y = round_num(sdlmain->mouse_pos.y - offset_border \
									+ editor->offset, editor->offset);
	ft_bzero(editor->editor_surf->pixels, \
				editor->editor_surf->h * editor->editor_surf->pitch);
	ft_bzero(editor->opt_surf->pixels, \
				editor->opt_surf->h * editor->opt_surf->pitch);
	ft_bzero(editor->instr_surf->pixels, \
				editor->instr_surf->h * editor->instr_surf->pitch);
	draw_editor(editor->editor_surf, editor, sdlmain);
	draw_border(editor->editor_surf, 0xB12211);
	draw_border(editor->opt_surf, 0xB12211);
	draw_border(editor->instr_surf, 0xB12211);
	draw_lines_editor(editor, editor->editor_surf, sdlmain->mouse_pos);
}

int		editor_loop(t_doom *doom)
{
	t_editor	*editor;
	t_sdlmain	*sdlmain;
	int			offset_border;

	editor = &(doom->editor);
	sdlmain = &(doom->sdlmain);
	if (editor->editor_surf->w < editor->editor_surf->h)
		editor->offset = editor->editor_surf->w / NBPOINTSROW;
	else
		editor->offset = editor->editor_surf->h / NBPOINTSROW;
	offset_border = editor->editor_surf->h \
			- NBPOINTSROW * editor->offset;
	if (!is_buffer_playing(sdlmain->sound.source[0], sdlmain->sound.buffer[9]))
		play_editor_music(sdlmain, doom);
	while (doom->state == EDITOR_STATE)
	{
		while (SDL_PollEvent(&sdlmain->event) != 0)
			if (editor_events(doom, sdlmain) != 0)
				break ;
		SDL_GetMouseState(&sdlmain->mouse_pos.x, &sdlmain->mouse_pos.y);
		prepare_editor(sdlmain, editor, offset_border);
		if (blit_editor(editor, sdlmain) != 0)
			return (1);
	}
	return (0);
}
