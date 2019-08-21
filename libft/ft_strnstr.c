/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:16:13 by afonck            #+#    #+#             */
/*   Updated: 2018/11/15 13:27:22 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*haystack1;
	const char	*needle1;
	size_t		lensave;

	haystack1 = haystack;
	needle1 = needle;
	lensave = len;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len)
	{
		while (*haystack == *needle && *needle && len--)
		{
			haystack++;
			needle++;
		}
		if (*needle == '\0')
			return ((char *)haystack1);
		haystack1++;
		haystack = haystack1;
		needle = needle1;
		lensave--;
		len = lensave;
	}
	return (NULL);
}
