/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:30:20 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 15:30:51 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atol(const char *str)
{
	int					i;
	int					n;
	unsigned long long	result;

	i = 0;
	result = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = 1;
		i++;
	}
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + str[i] - '0';
		i++;
		if (result > 9223372036854775807)
			return ((n == 1) ? 0 : -1);
	}
	result = (n == 1) ? (result * -1) : result;
	return (result);
}
