/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create_reset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 20:09:52 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 20:10:15 by sluetzen         ###   ########.fr       */
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

t_vecdb	create_vecdb(double x, double y)
{
	t_vecdb vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vec	reset_vec(t_vec *vector)
{
	vector->x = -1;
	vector->y = -1;
	return (*vector);
}

t_vecdb	reset_vecdb(t_vecdb *vector)
{
	vector->x = -1;
	vector->y = -1;
	return (*vector);
}
