/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:58:11 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/10 17:59:23 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		free_fonts(t_editor *editor)
{
	TTF_CloseFont(editor->opt_menu.font);
	editor->opt_menu.font = NULL;
	TTF_CloseFont(editor->opt_menu.font_title);
	editor->opt_menu.font_title = NULL;
	TTF_CloseFont(editor->instr_menu.font);
	editor->instr_menu.font = NULL;
	TTF_CloseFont(editor->instr_menu.font_title);
	editor->instr_menu.font_title = NULL;
	return (EXIT_FAILURE);
}

int		free_fonts_surf(t_editor *editor)
{
	int i;

	i = 0;
	free_and_null_surf(editor->instr_menu.title);
	free_and_null_surf(editor->opt_menu.title);
	while (i < NBOPTIONS)
	{
		free_and_null_surf(editor->opt_menu.options[i]);
		i++;
	}
	i = 0;
	while (i < NBHOVEROPTIONS)
	{
		free_and_null_surf(editor->opt_menu.hover_options[i]);
		i++;
	}
	i = 0;
	while (i < NBINSTRUCTS)
	{
		free_and_null_surf(editor->instr_menu.instructs[i]);
		i++;
	}
	return (EXIT_FAILURE);
}

int		free_editor(t_editor *editor)
{
	free_and_null_surf(editor->editor_surf);
	free_and_null_surf(editor->instr_surf);
	free_and_null_surf(editor->opt_surf);
	free_and_null_surf(editor->alert_convex_surf);
	free_and_null_surf(editor->alert_loading_surf);
	free_and_null_surf(editor->loading_success_surf);
	free_and_null_surf(editor->opt_menu.height_surf[0]);
	free_and_null_surf(editor->opt_menu.height_surf[1]);
	free_fonts_surf(editor);
	free_fonts(editor);
	return (EXIT_FAILURE);
}
