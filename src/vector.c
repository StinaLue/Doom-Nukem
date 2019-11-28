/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:06:54 by afonck            #+#    #+#             */
/*   Updated: 2019/11/28 18:06:55 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vec	create_vec(int x, int y)
{
	t_vec vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

void	give_vec_values(t_vec *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

void	vectorcpy(t_vec *one, const t_vec *two)
{
	one->x = two->x;
	one->y = two->y;
}

t_vecdb	multvec(t_vecdb vecdb, double n)
{
	vecdb.x *= n;
	vecdb.y *= n;
	return (vecdb);
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

t_vecdb	vec_to_vecdb(t_vec vector)
{
	t_vecdb vectordb;

	vectordb.x = vector.x;
	vectordb.y = vector.y;
	return (vectordb);
}
