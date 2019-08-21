/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:40:11 by afonck            #+#    #+#             */
/*   Updated: 2018/11/14 16:58:51 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static int		is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static int		s1len(const char *s1)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	return (i);
}

static char		*sdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	if ((s2 = (char *)malloc(sizeof(char) * s1len(s1) + 1)) == NULL)
		return (NULL);
	while (i <= s1len(s1))
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char			*ft_strtrim(char const *s)
{
	size_t		i;
	char		*ptr;

	if (s == NULL)
		return (NULL);
	if (sdup(s) != NULL)
		ptr = sdup(s);
	else
		return (NULL);
	while (is_space(*ptr) == 1)
		ptr++;
	i = s1len(ptr) - 1;
	while (is_space(ptr[i]) == 1)
		i--;
	i++;
	ptr[i] = '\0';
	if (sdup(ptr) != NULL)
		return (sdup(ptr));
	else
		return (NULL);
}
