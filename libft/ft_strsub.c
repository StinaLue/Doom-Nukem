/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:08:28 by afonck            #+#    #+#             */
/*   Updated: 2018/11/14 15:40:12 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*ptr;

	i = 0;
	j = 0;
	if ((ptr = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < start && s != NULL)
		i++;
	while (j < len && s != NULL)
	{
		ptr[j] = s[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
