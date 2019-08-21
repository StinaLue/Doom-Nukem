/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:38:24 by afonck            #+#    #+#             */
/*   Updated: 2018/11/13 11:07:47 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	s1len(const char *s1)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	return (i);
}

char		*ft_strdup(const char *s1)
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
