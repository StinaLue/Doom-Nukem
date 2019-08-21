/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 08:54:56 by afonck            #+#    #+#             */
/*   Updated: 2018/11/13 13:46:31 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static size_t	countwords(char const *s, char c)
{
	size_t	i;
	size_t	nbwords;

	i = 0;
	nbwords = 0;
	if (s[i] == 0)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
			nbwords++;
		while (s[i + 1] && s[i] != c)
			i++;
		i++;
	}
	return (nbwords);
}

static size_t	countletters(char const *s, char c)
{
	size_t	wordlen;
	size_t	i;

	wordlen = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			i++;
			wordlen++;
		}
	}
	return (wordlen);
}

static char		**ft_tabdel(char **tab, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**tab;

	i = 0;
	k = 0;
	if (!s || !(tab = (char**)malloc(sizeof(char*) * (countwords(s, c) + 1))))
		return (NULL);
	while (i < countwords(s, c))
	{
		if (!(tab[i] = (char*)malloc(countletters(&s[k], c) + 1)))
			return (ft_tabdel(tab, countwords(s, c)));
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] && s[k] != c)
			tab[i][j++] = s[k++];
		tab[i][j] = '\0';
		i++;
	}
	tab[countwords(s, c)] = 0;
	return (tab);
}
