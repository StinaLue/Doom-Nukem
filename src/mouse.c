/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:08:27 by afonck            #+#    #+#             */
/*   Updated: 2020/01/08 13:29:05 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	is_mouse_collide(t_vec mouse_pos, SDL_Rect collide_rect)
{
	if ((mouse_pos.x >= collide_rect.x && mouse_pos.x <= collide_rect.x + collide_rect.w))
	{
		if ((mouse_pos.y >= collide_rect.y && mouse_pos.y <= collide_rect.y + collide_rect.h))
		{
			return (1);
		}
	}
	return (0);
}