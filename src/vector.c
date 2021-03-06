/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:06:54 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 20:10:57 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vecdb	vecdb_diff(t_vecdb a, t_vecdb b)
{
	t_vecdb vector;

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
