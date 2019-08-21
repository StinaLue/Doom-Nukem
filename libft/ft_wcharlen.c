/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 09:18:54 by afonck            #+#    #+#             */
/*   Updated: 2019/07/05 09:19:16 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_wcharlen(int nbbits)
{
	if (nbbits <= 7)
		return (1);
	else if (nbbits > 7 && nbbits <= 11)
		return (2);
	else if (nbbits > 11 && nbbits <= 16)
		return (3);
	else if (nbbits > 16)
		return (4);
	else
		return (-1);
}
