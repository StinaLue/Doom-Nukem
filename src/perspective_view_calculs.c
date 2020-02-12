/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_view_calculs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:00:03 by sluetzen          #+#    #+#             */
/*   Updated: 2020/02/12 11:04:41 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

int				max(int a, int b)
{
	return (a > b ? a : b);
}

double			vxs(double xstart, double ystart, double xtwo, double ytwo)
{
	return (xstart * ytwo - ystart * xtwo);
}

t_vecdb			simple_intersect(t_vecdb start, t_vecdb end, t_vecdb cross)
{
	t_vecdb	intersection;
	double	tmp;
	double	vcp;

	tmp = 1;
	vcp = vxs(start.x - end.x, start.y - end.y, cross.x, cross.y);
	if (vcp != 0)
		tmp = cross_product(start, end) / vcp;
	intersection.x = tmp * cross.x;
	intersection.y = tmp * cross.y;
	return (intersection);
}
