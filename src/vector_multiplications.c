/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_multiplications.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 20:08:45 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 20:09:11 by sluetzen         ###   ########.fr       */
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

t_vecdb	rotate2d(t_vecdb vector, double angle)
{
	t_vecdb newvector;

	newvector.x = vector.x * cos(angle) - vector.y * sin(angle);
	newvector.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (newvector);
}

double	get_point_distance(t_vecdb a, t_vecdb b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}
