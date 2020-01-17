/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:49:38 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/17 17:06:52 by sluetzen         ###   ########.fr       */
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
			editor->options_surf, &editor->opt_menu.title_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	while (i < NBOPTIONS)
	{
		if ((SDL_BlitSurface(editor->opt_menu.options[i], NULL,
			editor->options_surf, &editor->opt_menu.options_rect[i])) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

int blit_textures(t_editor *editor)
{
	int i;

	i = 0;
	while (i < 9)
	{
		draw_border_options(&editor->opt_menu.text_rect[i], editor->opt_menu.bord_color_text[i], editor->options_surf);
		if ((SDL_BlitScaled(editor->wall_textures[i], NULL, \
			editor->options_surf, &editor->opt_menu.text_rect[i])) < 0)
		return (error_return("BlitScaled error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

int blit_height(t_editor *editor)
{
	int i;

	i = 0;
	while (i < NBHEIGHTS)
	{
		draw_border_options(&editor->opt_menu.h_rect[i], editor->opt_menu.bord_color_h[i], editor->options_surf);
		i++;
	}
	i = 0;
	while (i < NBHEIGHTS)
	{
		if ((SDL_BlitScaled(editor->wall_textures[editor->opt_menu.activ_text], NULL,
			editor->options_surf, &editor->opt_menu.h_rect[i])) < 0)
		return (error_return("BlitScaled error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

/* int highlight_texture(t_editor *editor)
{
	if (editor->current_option == 0)
	{
		if (highlight_text(&sdlmain->font, &menu->options[0], &menu->text_color, "/ editor \\") == -1)
			return (1);
	}
	return (0);
} */

int	blit_editor(t_editor *editor, t_sdlmain *sdlmain)
{
	if (blit_instructs(editor) != 0)
		return (1);
	if (blit_options(editor) != 0)
		return (1);
	if (blit_textures(editor) != 0)
		return (1);
	if (blit_height(editor) != 0)
		return (1);
	//if (highlight_texture(editor, sdlmain) != 0)
	//	return (error_return("Error in highlight selection function\n", NULL));
	if ((SDL_BlitScaled(editor->editor_surf, NULL,
			sdlmain->win_surf, &editor->editor_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n",
				SDL_GetError()));
	if ((SDL_BlitScaled(editor->options_surf, NULL,
			sdlmain->win_surf, &editor->options_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n",
					SDL_GetError()));
	if ((SDL_BlitScaled(editor->instr_surf, NULL,
			sdlmain->win_surf, &editor->instr_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if ((SDL_BlitScaled(editor->wall_textures[editor->opt_menu.activ_text], NULL,
			sdlmain->win_surf, &editor->mouse_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		return (error_return("SDL_UpdateWindowSurface error = %{r}s\n",
			SDL_GetError()));
	return (0);
}
