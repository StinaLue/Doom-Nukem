/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:43:20 by afonck            #+#    #+#             */
/*   Updated: 2019/10/19 16:51:17 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void	fill_chartab(char chartab[MAX_MAP][MAX_MAP], char *title,
			int *map_width, int *map_height)
{
	char	*line;
	int		ret;
	int		fd;
	int		w;

	*map_height = 0;
	ret = 0;
	w = 0;
	if ((fd = open(title, O_RDONLY | O_NOFOLLOW)) == -1)
		open_error(title);
	while ((ret = get_next_line(fd, &line)) > 0 && *map_height < MAX_MAP)
	{
		if (check_line(line) != '0')
			invalid_char_error(check_line(line), (void **)&line, fd);
		//w = (*map_height == 0 ? ft_strlen(line) : *map_height);
		if (*map_height == 0)
			w = ft_strlen(line);
		*map_width = ft_strlen(line);
		check_badwidth_map(*map_width, w, (void **)&line, fd);
		copy_line(chartab[*map_height], line, *map_width);
		ft_memdel((void **)&line);
		(*map_height)++;
	}
	if (ret < 0)
		exit(EXIT_FAILURE);
	ft_memdel((void **)&line);
	check_badheight_map(*map_height, fd, title);
}

void	fill_map(int (*map)[MAX_MAP][MAX_MAP], char *title,
			int *map_width, int *map_height)
{
	char	chartab[MAX_MAP][MAX_MAP];
	int		i;
	int		j;

	i = 0;
	fill_chartab(chartab, title, map_width, map_height);
	while (i < *map_height)
	{
		j = 0;
		while (j < *map_width)
		{
			if (chartab[i][j] == 'X')
				(*map)[i][j] = 'X';
			else
				(*map)[i][j] = chartab[i][j] - '0';
			j++;
		}
		i++;
	}
}
