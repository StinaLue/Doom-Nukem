/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:06:54 by afonck            #+#    #+#             */
/*   Updated: 2020/01/08 15:18:54 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	dot_product(t_vecdb a, t_vecdb b)
{
	return (a.x * b.x + a.y * b.y);
}

double	cross_product(t_vecdb a, t_vecdb b)
{
	return (a.x * b.y - a.y * b.x);
}

double	get_magnitude(t_vecdb a, t_vecdb b)
{
	double dx;
	double dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrt(dx * dx + dy * dy));
}

t_vec	create_vec(int x, int y)
{
	t_vec vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vecdb	create_vecdb(double x, double y)
{
	t_vecdb vec;

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

void	multvec(t_vecdb *vecdb, double n)
{
	vecdb->x *= n;
	vecdb->y *= n;
}

t_vecdb	rotate2dcc(t_vecdb vector, double angle)
{
	t_vecdb newvector;

	newvector.x = vector.x * cos(angle) + vector.y * sin(angle);
	newvector.y = vector.y * cos(angle) - vector.x * sin(angle);
	return (newvector);
}

t_vecdb	rotate2d(t_vecdb vector, double angle)
{
	t_vecdb newvector;

	newvector.x = vector.x * cos(angle) - vector.y * sin(angle);
	newvector.y = vector.x * sin(angle) + vector.y * cos(angle);
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

double	get_point_distance(t_vecdb a, t_vecdb b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
