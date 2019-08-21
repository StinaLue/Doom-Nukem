/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:51:07 by afonck            #+#    #+#             */
/*   Updated: 2018/11/11 15:17:35 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*p;

	i = 0;
	p = NULL;
	while (s[i])
		i++;
	while (i >= 0 && s[i] != (char)c)
		i--;
	if (s[i] == c)
	{
		p = &s[i];
		return ((char *)p);
	}
	return (NULL);
}
