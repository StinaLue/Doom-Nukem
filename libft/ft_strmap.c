/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:53:02 by afonck            #+#    #+#             */
/*   Updated: 2018/11/15 14:09:50 by afonck           ###   ########.fr       */
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

char			*ft_strmap(char const *s, char (*f)(char))
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
		freshstring[i] = (*f)(s[i]);
		i++;
	}
	freshstring[i] = '\0';
	return (freshstring);
}
