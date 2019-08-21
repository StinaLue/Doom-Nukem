/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:43:02 by afonck            #+#    #+#             */
/*   Updated: 2018/11/10 18:33:17 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*haystack1;
	const char	*needle1;

	haystack1 = haystack;
	needle1 = needle;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		while (*haystack == *needle && *needle)
		{
			haystack++;
			needle++;
		}
		if (*needle == '\0')
			return ((char *)haystack1);
		haystack1++;
		haystack = haystack1;
		needle = needle1;
	}
	return (NULL);
}
