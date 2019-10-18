/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 04:39:08 by afonck            #+#    #+#             */
/*   Updated: 2019/10/18 04:39:49 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

int		init_fps_surf(t_ttf *ttf, int current_fps, int *start_clock)
{
	*start_clock = SDL_GetTicks();
	ttf->fps = translate_fps(current_fps);
	if ((ttf->surf_message = TTF_RenderText_Solid(ttf->font, ttf->fps, ttf->color)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "TTF_RenderText_Solid error = %{r}s\n", TTF_GetError());
		return (-1);
	}
	return (0);
}

void	update_fps(int *delta_clock, int *start_clock, int *current_fps, int *wolf_fps)
{
	*delta_clock = SDL_GetTicks() - *start_clock;
	if (*delta_clock != 0)
		*current_fps = 1000 / *delta_clock;
	*wolf_fps = *current_fps;
}