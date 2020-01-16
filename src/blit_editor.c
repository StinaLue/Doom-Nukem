/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:49:38 by sluetzen          #+#    #+#             */
/*   Updated: 2020/01/16 12:27:31 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	blit_instructs(t_editor *editor)
{
	int i;

	i = 0;
	if ((SDL_BlitSurface(editor->instruct_menu.title, NULL,
			editor->instruct_surf, &editor->instruct_menu.title_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	while (i < 5)
	{
		if ((SDL_BlitSurface(editor->instruct_menu.instructions[i], NULL,
			editor->instruct_surf, &editor->instruct_menu.instruct_rect[i])) < 0)
			return (error_return("BlitSurface error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

int	blit_options(t_editor *editor)
{
	int i;

	i = 0;
	if ((SDL_BlitSurface(editor->options_menu.title, NULL,
			editor->options_surf, &editor->options_menu.title_rect)) < 0)
		return (error_return("BlitSurface error = %s\n", SDL_GetError()));
	while (i < 5)
	{
		if ((SDL_BlitSurface(editor->options_menu.options[i], NULL,
			editor->options_surf, &editor->options_menu.options_rect[i])) < 0)
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
		draw_border_options(&editor->options_menu.texture_rect[i], editor->options_menu.border_color_text[i], editor->options_surf);
		if ((SDL_BlitScaled(editor->options_menu.wall_textures[i], NULL, // change this to "i" as soon as all textures are there 
			editor->options_surf, &editor->options_menu.texture_rect[i])) < 0)
		return (error_return("BlitScaled error = %s\n", SDL_GetError()));
		i++;
	}
	return (0);
}

int blit_height(t_editor *editor)
{
	int i;

	i = 0;
	while (i < 7)
	{
		draw_border_options(&editor->options_menu.height_rect[i], editor->options_menu.border_color_height[i], editor->options_surf);
		i++;
	}
	i = 0;
	while (i < 7)
	{
		if ((SDL_BlitScaled(editor->options_menu.wall_textures[0], NULL,
			editor->options_surf, &editor->options_menu.height_rect[i])) < 0)
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
	if ((SDL_BlitScaled(editor->instruct_surf, NULL,
			sdlmain->win_surf, &editor->instruct_rect)) < 0)
		return (error_return("SDL_BlitScaled error = %{r}s\n", SDL_GetError()));
	if ((SDL_UpdateWindowSurface(sdlmain->win)) < 0)
		return (error_return("SDL_UpdateWindowSurface error = %{r}s\n",
			SDL_GetError()));
	return (0);
}
