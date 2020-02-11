/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_blit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:49:38 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 10:52:45 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int	blit_instructs(t_editor *editor)
{
	int i;

	i = 0;
	if ((SDL_BlitSurface(editor->instr_menu.title, NULL,
			editor->instr_surf, &editor->instr_menu.title_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	while (i < NBINSTRUCTS)
	{
		if ((SDL_BlitSurface(editor->instr_menu.instructs[i], NULL,
			editor->instr_surf, &editor->instr_menu.instr_rect[i])) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

int	blit_textures(t_editor *editor)
{
	int i;

	i = 0;
	while (i < NB_WALL_TEXTURES)
	{
		draw_border_options(&editor->opt_menu.text_rect[i], \
				editor->opt_menu.bord_color_text[i], editor->opt_surf);
		if ((SDL_BlitScaled(editor->wall_textures[i], NULL, \
			editor->opt_surf, &editor->opt_menu.text_rect[i])) < 0)
			return (error_return("BlitScaled error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

int	blit_player_face(t_editor *editor)
{
	SDL_Rect	face_rect;

	if (editor->edit_map.player_spawn.x != -1 \
			&& editor->edit_map.player_spawn.y != -1)
	{
		face_rect = create_sdlrect(editor->edit_map.player_spawn.x \
					* editor->offset / SIZEMAP - 10, \
					editor->editor_surf->h - editor->edit_map.player_spawn.y \
					* editor->offset / SIZEMAP - 10, 20, 20);
		if (SDL_BlitScaled(editor->player_face_surf, &editor->player_face_rec, \
							editor->editor_surf, &face_rect) < 0)
			return (1);
	}
	return (0);
}

int	blit_enemy(t_editor *editor, t_map *map, int offset)
{
	int				i;
	SDL_Rect		enemy_rect;
	t_enemy_info	*info;

	i = 0;
	info = map->enemy_info;
	while (i < map->num_enemies && info != NULL)
	{
		enemy_rect = \
			create_sdlrect(info[i].enemy_spawn.x \
			* offset / SIZEMAP - 40, editor->editor_surf->h \
			- info[i].enemy_spawn.y * offset / SIZEMAP - 40, 80, 80);
		if (SDL_BlitScaled(editor->enemy_textures[info[i].which_enemy], \
			&editor->enemy_rect[info[i].which_enemy], \
			editor->editor_surf, &enemy_rect) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	blit_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	if (blit_player_face(editor) != 0)
		return (1);
	if (blit_enemy(editor, &editor->edit_map, editor->offset) != 0)
		return (1);
	if (blit_instructs(editor) != 0)
		return (1);
	if (blit_options(editor) != 0)
		return (1);
	if (blit_textures(editor) != 0)
		return (1);
	if (blit_height(editor) != 0)
		return (1);
	if (blit_alert(editor) != 0)
		return (1);
	if (editor_blit_weapons(editor, &editor->opt_menu) != 0)
		return (1);
	if (blit_editor_surf(editor, sdlmain) != 0)
		return (1);
	if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		return (error_return("SDL_UpdateWindowSurface error = %{r}s\n",
			SDL_GetError()));
		return (0);
}
