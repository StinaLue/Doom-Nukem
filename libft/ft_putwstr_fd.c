/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:15:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/08 16:15:35 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putwstr_fd(wchar_t *str, int fd)
{
	int	full_len;

	full_len = 0;
	if (str == NULL)
		return (-1);
	while (*str)
	{
		full_len += ft_putwchar_fd(*str, fd);
		str++;
	}
	return (full_len);
}
