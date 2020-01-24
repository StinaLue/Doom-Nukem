/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:49:38 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/22 17:50:24 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	return (0);
}

int	blit_textures(t_editor *editor)
{
	int i;

	i = 0;
	while (i < 9)
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

int blit_test_height(t_editor *editor)
{
	draw_border_options(&editor->opt_menu.h_rect_ceiling[1], \
				editor->opt_menu.bord_color_h[1], editor->opt_surf);
	draw_border_options(&editor->opt_menu.h_rect_floor[1], \
				editor->opt_menu.bord_color_h[1], editor->opt_surf);
	/* draw_border_options(&editor->opt_menu.h_rect_ceiling, \
				editor->opt_menu.bord_color_h[1], editor->opt_surf); */
	if ((SDL_BlitScaled(editor->wall_textures[editor->opt_menu.activ_tex], \
			NULL, editor->opt_surf, &editor->opt_menu.h_rect_ceiling[0])) < 0)
			return (error_return("BlitScaled error = %s\n", SDL_GetError()));

	/* draw_border_options(&editor->opt_menu.h_rect_floor[0], \
				editor->opt_menu.bord_color_h[1], editor->opt_surf); */
	if ((SDL_BlitScaled(editor->wall_textures[editor->opt_menu.activ_tex], \
			NULL, editor->opt_surf, &editor->opt_menu.h_rect_floor[0])) < 0)
			return (error_return("BlitScaled error = %s\n", SDL_GetError()));
	return (0);
}

int	blit_height(t_editor *editor)
{
	int i;

	i = 0;
	while (i < NBHEIGHTS)
	{
		draw_border_options(&editor->opt_menu.h_rect[i], \
				editor->opt_menu.bord_color_h[i], editor->opt_surf);
		i++;
	}
	i = 0;
	while (i < NBHEIGHTS)
	{
		if ((SDL_BlitScaled(editor->wall_textures[editor->opt_menu.activ_tex], \
			NULL, editor->opt_surf, &editor->opt_menu.h_rect[i])) < 0)
			return (error_return("BlitScaled error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

int	blit_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	if (blit_instructs(editor) != 0)
		return (1);
	if (blit_options(editor) != 0)
		return (1);
	if (blit_textures(editor) != 0)
		return (1);
	if (blit_test_height(editor) != 0)
		return (1);/* 
	if (blit_height(editor) != 0)
		return (1); */
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
	if ((SDL_BlitScaled(editor->wall_textures[editor->opt_menu.activ_tex], NULL,
			sdlmain->win_surf, &editor->mouse_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		return (error_return("SDL_UpdateWindowSurface error = %{r}s\n",
			SDL_GetError()));
		return (0);
}
