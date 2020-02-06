/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:49:38 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/06 15:43:58 by sluetzen         ###   ########.fr       */
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

int	blit_hover_options(t_editor *editor)
{
	int i;

	i = 0;
	while (i < NBHOVEROPTIONS)
	{
		if ((SDL_BlitSurface(editor->opt_menu.hover_options[i], NULL,
			editor->opt_surf, &editor->opt_menu.hover_opt_rect[i])) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		draw_border_options(&editor->opt_menu.hover_opt_rect[i], \
					editor->opt_menu.bord_hover_color_opt[i], editor->opt_surf);
		i++;
	}
	SDL_FreeSurface(editor->opt_menu.hover_options[0]);
	editor->opt_menu.hover_options[0] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		editor->opt_menu.file_name, editor->opt_menu.text_color);
	return (0);
}

int	blit_options(t_editor *editor)
{
	int i;

	i = 0;
	if ((SDL_BlitSurface(editor->opt_menu.title, NULL,
			editor->opt_surf, &editor->opt_menu.title_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	while (i < NBOPTIONS)
	{
		if ((SDL_BlitSurface(editor->opt_menu.options[i], NULL,
			editor->opt_surf, &editor->opt_menu.options_rect[i])) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		i++;
	}
	if (blit_hover_options(editor) != 0)
		return (1);
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

int	blit_music_weapon(t_editor *editor)
{
	int i;

	i = 0;
	while (i < 2)
	{
		draw_border_options(&editor->opt_menu.weapon_rect[i], \
				editor->opt_menu.bord_color_weapon[i], editor->opt_surf);
		if ((SDL_BlitScaled(editor->wall_textures[i], NULL, \
			editor->opt_surf, &editor->opt_menu.weapon_rect[i])) < 0)
			return (error_return("BlitScaled error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

int	free_height(t_editor *editor)
{
	const char *num_ceil;
	const char *num_floor;

	SDL_FreeSurface(editor->opt_menu.height_surf[0]);
	SDL_FreeSurface(editor->opt_menu.height_surf[1]);
	if ((num_floor = ft_itoa((int)editor->opt_menu.height_floor)) == NULL)
		return (1);
	if ((num_ceil = ft_itoa((int)editor->opt_menu.height_ceiling)) == NULL)
		return (1);
	if ((editor->opt_menu.height_surf[0] = \
		TTF_RenderText_Solid(editor->opt_menu.font, num_ceil, \
							editor->opt_menu.text_color)) == NULL)
		return (1);
	if ((editor->opt_menu.height_surf[1] = \
		TTF_RenderText_Solid(editor->opt_menu.font, num_floor, \
							editor->opt_menu.text_color)) == NULL)
		return (1);
	ft_memdel((void **)&num_floor);
	ft_memdel((void **)&num_ceil);
	return (0);
}

int	blit_height(t_editor *editor)
{
	if ((SDL_BlitSurface(editor->opt_menu.height_surf[0], \
			NULL, editor->opt_surf, &editor->opt_menu.height_rect[0])) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	if ((SDL_BlitSurface(editor->opt_menu.height_surf[1], \
			NULL, editor->opt_surf, &editor->opt_menu.height_rect[1])) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	draw_border_options(&editor->opt_menu.height_rect[0], \
				editor->opt_menu.bord_color_opt[0], editor->opt_surf);
	draw_border_options(&editor->opt_menu.height_rect[1], \
				editor->opt_menu.bord_color_opt[1], editor->opt_surf);
	if (free_height(editor) != 0)
		return (1);
	return (0);
}

int	blit_loading_alert(t_editor *editor)
{
	if (editor->show_convex_alert == 1)
	{
		if ((SDL_BlitSurface(editor->alert_convex_surf, NULL,
			editor->editor_surf, &editor->alert_convex_rect)) < 0)
			return (error_return("SDL_BlitSurface error = %{r}s\n",
				SDL_GetError()));
			editor->show_loading_alert = 0;
		editor->loading_success = 0;
	}
	else if (editor->show_loading_alert == 1)
	{
		if ((SDL_BlitSurface(editor->alert_loading_surf, NULL,
			editor->editor_surf, &editor->alert_loading_rect)) < 0)
			return (error_return("SDL_BlitSurface error = %{r}s\n",
				SDL_GetError()));
			editor->show_convex_alert = 0;
		editor->loading_success = 0;
	}
	return (0);
}

int	blit_alert(t_editor *editor)
{
	if (blit_loading_alert(editor) != 0)
		return (1);
	if (editor->loading_success == 1)
	{
		if ((SDL_BlitSurface(editor->loading_success_surf, NULL,
			editor->editor_surf, &editor->loading_success_rect)) < 0)
			return (error_return("SDL_BlitSurface error = %{r}s\n",
				SDL_GetError()));
			editor->show_convex_alert = 0;
		editor->show_loading_alert = 0;
	}
	return (0);
}

int	blit_editor_surf(t_editor *editor, t_sdlmain *sdlmain)
{
	if ((SDL_BlitScaled(editor->editor_surf, NULL,
			sdlmain->win_surf, &editor->editor_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n",
				SDL_GetError()));
		if ((SDL_BlitScaled(editor->opt_surf, NULL,
		sdlmain->win_surf, &editor->options_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n",
				SDL_GetError()));
		if ((SDL_BlitScaled(editor->instr_surf, NULL,
		sdlmain->win_surf, &editor->instr_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if (sdlmain->mouse_pos.x * editor->offset < editor->editor_surf->w)
	{
		if ((SDL_BlitScaled(editor->wall_textures[editor->opt_menu.activ_tex], \
				NULL, sdlmain->win_surf, &editor->mouse_rect)) < 0)
			return (error_return("SDL_BlitScaled error = %{r}s\n", \
					SDL_GetError()));
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
					* editor->offset / MAPMULTIPLIER - 10, \
					editor->editor_surf->h - editor->edit_map.player_spawn.y \
					* editor->offset / MAPMULTIPLIER - 10, 20, 20);
		if (SDL_BlitScaled(editor->player_face_surf, &editor->player_face_rec, \
							editor->editor_surf, &face_rect) < 0)
			return (1);
	}
	return (0);
}

int	blit_enemy(t_editor *editor)
{
	int			i;
	SDL_Rect	enemy_rect;

	i = 0;
	while (i < editor->edit_map.num_enemies \
			&& editor->edit_map.enemy_info != NULL)
	{
		enemy_rect = \
			create_sdlrect(editor->edit_map.enemy_info[i].enemy_spawn.x \
			* editor->offset / MAPMULTIPLIER - 40, editor->editor_surf->h \
			- editor->edit_map.enemy_info[i].enemy_spawn.y * editor->offset \
			/ MAPMULTIPLIER - 40, 80, 80);
		if (SDL_BlitScaled(editor->enemy_textures\
			[editor->edit_map.enemy_info[i].which_enemy], \
			&editor->enemy_rect[editor->edit_map.enemy_info\
			[i].which_enemy], editor->editor_surf, &enemy_rect) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	blit_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	if (blit_player_face(editor) != 0)
		return (1);
	if (blit_enemy(editor) != 0)
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
	if (blit_music_weapon(editor) != 0)
		return (1);
	if (blit_editor_surf(editor, sdlmain) != 0)
		return (1);
	if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		return (error_return("SDL_UpdateWindowSurface error = %{r}s\n",
			SDL_GetError()));
		return (0);
}
