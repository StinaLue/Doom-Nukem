/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextodeci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:33:18 by afonck            #+#    #+#             */
/*   Updated: 2019/10/18 12:02:24 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_hextodeci(const char *str, int len, int hexflag)
{
	int x;
	int i;
	int factor;

	x = 0;
	i = 0;
	factor = 1;
	if (hexflag == 1)
		i += 2;
	len -= 1;
	while (len >= i)
	{
		if (str[len] >= 97 && str[len] <= 122)
			x += (str[len] - 87) * factor;
		else if (str[len] >= 65 && str[len] <= 90)
			x += (str[len] - 55) * factor;
		else
			x += (str[len] - '0') * factor;
		factor *= 16;
		len--;
	}
	return (x);
}
