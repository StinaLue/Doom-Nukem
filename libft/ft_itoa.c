/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:03:23 by afonck            #+#    #+#             */
/*   Updated: 2018/11/13 15:18:53 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	nbdigits(int n)
{
	int		nbdigits;

	nbdigits = 0;
	if (n == 0)
		return (1);
	if (n < nbdigits)
		nbdigits++;
	while (n != 0)
	{
		n = n / 10;
		nbdigits++;
	}
	return (nbdigits);
}

static int	s1len(const char *s1)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	return (i);
}

static char	*dup(char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	if ((s2 = (char *)malloc(sizeof(char) * s1len(s1) + 1)) == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char		*ft_itoa(int n)
{
	size_t		i;
	size_t		store;
	char		*p;

	i = 0;
	if (n == -2147483648)
		return (dup("-2147483648"));
	store = nbdigits(n);
	if ((p = (char *)malloc(sizeof(char) * (store + 1))) == NULL)
		return (NULL);
	p[store] = '\0';
	if (n < 0)
	{
		p[0] = '-';
		n *= -1;
		i++;
	}
	while (i < store--)
	{
		p[store] = (n % 10) + '0';
		n = n / 10;
	}
	return (p);
}
