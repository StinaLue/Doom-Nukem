/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:06:54 by afonck            #+#    #+#             */
/*   Updated: 2020/02/04 16:46:34 by phaydont         ###   ########.fr       */
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

double	cross_product_len(t_vec a, t_vec b, t_vec c)
{
	double bax;
	double bay;
	double bcx;
	double bcy;

	bax = a.x - b.x;
	bay = a.y - b.y;
	bcx = c.x - b.x;
	bcy = c.y - b.y;
	// Got the vectors' coordinates.
	// calculate the Z coordinate of the cross product.
	return (bax * bcy - bay * bcx);
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

void	set_vec_values(t_vec *src, t_vec *dst)
{
	dst->x = src->x;
	dst->y = src->y;
}

void	vectorcpy(t_vec *one, const t_vec *two)
{
	one->x = two->x;
	one->y = two->y;
}

t_vecdb	multvecdb(t_vecdb vecdb, double n)
{
	vecdb.x *= n;
	vecdb.y *= n;
	return (vecdb);
}

t_vec	multvec(t_vec vec, int mult)
{
	vec.x *= mult;
	vec.y *= mult;
	return (vec);
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

t_vecdb	vecdb_diff(t_vecdb a, t_vecdb b)
{
	t_vecdb vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	return (vector);
}

t_vec	vec_diff(t_vec a, t_vec b)
{
	t_vec vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	return (vector);
}

t_vecdb	vecdb_add(t_vecdb a, t_vecdb b)
{
	t_vecdb vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	return (vector);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	return (vector);
}


t_vecdb	vecdb_mult(t_vecdb a, t_vecdb b)
{
	t_vecdb vector;

	vector.x = a.x * b.x;
	vector.y = a.y * b.y;
	return (vector);
}


t_vec	vec_mult(t_vec a, t_vec b)
{
	t_vec vector;

	vector.x = a.x * b.x;
	vector.y = a.y * b.y;
	return (vector);
}
