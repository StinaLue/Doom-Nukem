/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:27:56 by afonck            #+#    #+#             */
/*   Updated: 2018/11/14 17:06:33 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

static void	putchr(char c)
{
	write(1, &c, 1);
}

static void	putstr(char const *s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			putchr(s[i]);
			i++;
		}
	}
}

void		ft_putendl(char const *s)
{
	if (s != NULL)
	{
		putstr(s);
		putchr('\n');
	}
}
