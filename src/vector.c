/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:06:54 by afonck            #+#    #+#             */
/*   Updated: 2019/11/17 14:08:15 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	assign_vec(t_vec *one, const t_vec *two)
{
	one->x = two->x;
	one->y = two->y;
}

t_vecdb	rotate2d(t_vecdb vector, double angle)
{
	t_vecdb newvector;

	newvector.x = vector.x * cos(angle) + vector.y * sin(angle);
	newvector.y = vector.x * sin(angle) - vector.y * cos(angle);
	return (newvector);
}

t_vec	vecdb_to_vec(t_vecdb vectordb)
{
	t_vec vector;

	vector.x = (int)vectordb.x;
	vector.y = (int)vectordb.y;
	return (vector);
}
