/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:08:27 by afonck            #+#    #+#             */
/*   Updated: 2020/02/07 18:00:12 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	is_mouse_collide(t_vec mouse_pos, SDL_Rect collide_rect)
{
	if ((mouse_pos.x >= collide_rect.x \
			&& mouse_pos.x <= collide_rect.x + collide_rect.w))
	{
		if ((mouse_pos.y >= collide_rect.y \
				&& mouse_pos.y <= collide_rect.y + collide_rect.h))
		{
			return (1);
		}
	}
	return (0);
}
