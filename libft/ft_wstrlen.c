/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:15:46 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/08 16:15:47 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wstrlen(wchar_t *wstr)
{
	int	full_len;

	full_len = 0;
	if (wstr == NULL)
		return (-1);
	while (*wstr)
	{
		full_len += ft_wcharlen(ft_nbits(*wstr));
		wstr++;
	}
	return (full_len);
}
