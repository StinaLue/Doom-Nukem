/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:49:21 by afonck            #+#    #+#             */
/*   Updated: 2018/11/14 17:05:42 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

static void	put_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	putstr_fd(char const *s, int fd)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			put_fd(s[i], fd);
			i++;
		}
	}
}

void		ft_putendl_fd(char const *s, int fd)
{
	if (s != NULL)
	{
		putstr_fd(s, fd);
		put_fd('\n', fd);
	}
}
