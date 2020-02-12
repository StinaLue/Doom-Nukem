/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:04:50 by phaydont          #+#    #+#             */
/*   Updated: 2020/02/12 11:06:17 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_ceiling(SDL_Surface *surf, t_vec win, int top_limit, int type)
{
	if (type == 2)
		return ;
	while (win.y++ < top_limit)
	{
		fill_pix(surf, win.x, win.y, 0x999999);
	}
}

void	fill_floor(SDL_Surface *surf, t_vec win, int bot_limit, int type)
{
	if (type == 1)
		return ;
	while (win.y > bot_limit)
	{
		fill_pix(surf, win.x, win.y--, 0x666666);
	}
}
