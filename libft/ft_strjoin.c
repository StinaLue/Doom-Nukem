/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:20:41 by afonck            #+#    #+#             */
/*   Updated: 2018/11/14 15:44:22 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static size_t	len(char const *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((ptr = (char *)malloc(sizeof(char) * (len(s1) + len(s2) + 1))) == NULL)
		return (NULL);
	while (i < len(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	while (j < len(s2))
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}
