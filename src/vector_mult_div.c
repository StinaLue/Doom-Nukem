/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mult_div.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:58:46 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/11 20:00:16 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vecdb	multvecdb(t_vecdb vecdb, double mult)
{
	vecdb.x *= mult;
	vecdb.y *= mult;
	return (vecdb);
}

t_vec	multvec(t_vec vec, int mult)
{
	vec.x *= mult;
	vec.y *= mult;
	return (vec);
}

t_vecdb	divvecdb(t_vecdb vecdb, double div)
{
	vecdb.x /= div;
	vecdb.y /= div;
	return (vecdb);
}
