/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_blit_alerts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:32:59 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 10:35:26 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
