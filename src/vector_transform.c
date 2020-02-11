/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 20:05:40 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 20:07:09 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void	give_vec_values(t_vec *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

void	set_vecdb_values(t_vecdb *src, t_vecdb *dst)
{
	dst->x = src->x;
	dst->y = src->y;
}

void	vectorcpy(t_vec *one, const t_vec *two)
{
	one->x = two->x;
	one->y = two->y;
}
