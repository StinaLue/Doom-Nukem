/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_create_surfaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:04:04 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/10 16:07:12 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int	create_instruct_str(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->instr_menu.instructs[i] = \
		TTF_RenderText_Solid(editor->instr_menu.font, \
		str, editor->instr_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->instr_menu.instr_rect[i], origin, \
						create_vec(0, 0));
	return (0);
}

int	create_opt_str(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->opt_menu.options[i] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		str, editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->opt_menu.options_rect[i], origin, \
					create_vec(0, 0));
	return (0);
}

int	create_hover_opt(t_editor *editor, t_vec origin, int i, const char *str)
{
	if ((editor->opt_menu.hover_options[i] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		str, editor->opt_menu.text_color)) == NULL)
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
		assign_sdlrect(&editor->opt_menu.hover_opt_rect[i], origin, \
					create_vec(0, 0));
	return (0);
}

int	create_floor_height(t_editor *editor)
{
	int			i;
	const char	*num;

	i = (int)editor->opt_menu.height_floor;
	if ((num = ft_itoa(i)) == NULL)
		return (1);
	if ((editor->opt_menu.height_surf[1] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		num, editor->opt_menu.text_color)) == NULL)
	{
		ft_memdel((void **)&num);
		return (error_return("TTF_RenderText_Solid error = %s\n", \
					TTF_GetError()));
	}
	else
		ft_memdel((void **)&num);
	return (0);
}

int	create_ceiling_height(t_editor *editor)
{
	int			i;
	const char	*num;

	i = (int)editor->opt_menu.height_ceiling;
	if ((num = ft_itoa(i)) == NULL)
		return (1);
	if ((editor->opt_menu.height_surf[0] = \
		TTF_RenderText_Solid(editor->opt_menu.font, \
		num, editor->opt_menu.text_color)) == NULL)
	{
		ft_memdel((void **)&num);
		return (error_return("TTF_RenderText_Solid error = %s\n", \
				TTF_GetError()));
	}
	else
		ft_memdel((void **)&num);
	return (0);
}
