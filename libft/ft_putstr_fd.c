/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:44:20 by afonck            #+#    #+#             */
/*   Updated: 2018/11/14 17:06:06 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

static void	put_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putstr_fd(char const *s, int fd)
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
