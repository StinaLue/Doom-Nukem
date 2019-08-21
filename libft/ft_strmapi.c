/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:17:22 by afonck            #+#    #+#             */
/*   Updated: 2018/11/14 15:41:46 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static size_t	slen(char const *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*freshstring;
	size_t	i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	if ((freshstring = (char *)malloc(sizeof(char) * (slen(s) + 1))) == NULL)
		return (NULL);
	while (i < slen(s))
	{
		freshstring[i] = (*f)(i, s[i]);
		i++;
	}
	freshstring[i] = '\0';
	return (freshstring);
}
