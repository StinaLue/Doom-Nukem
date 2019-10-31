/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 02:43:20 by afonck            #+#    #+#             */
/*   Updated: 2019/10/31 18:20:59 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	fill_chartab(char chartab[MAX_MAP][MAX_MAP], char *title,
			int *map_height, int *map_width)
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
		//w = (*map_width == 0 ? ft_strlen(line) : *map_width);
		if (*map_height == 0)
			w = ft_strlen(line);
		*map_width = ft_strlen(line);
		check_badwidth_map(*map_width, w, (void **)&line, fd);
		copy_line(chartab[*map_height], line, *map_width);
	ft_printf("chartab[*map_height]%s\n", chartab[*map_height]);
		ft_memdel((void **)&line);
		(*map_height)++;
	}
	if (ret < 0)
		exit(EXIT_FAILURE);
	ft_memdel((void **)&line);
	check_badheight_map(*map_height, fd, title);
	printf("height: %d, width: %d\n", *map_height, *map_width);
	printf("w: %d\n", w);
}

void	fill_map(int (*map)[MAX_MAP][MAX_MAP], char *title,
			int *map_height, int *map_width)
{
	char	chartab[MAX_MAP][MAX_MAP];
	int		i;
	int		j;
	int		found_player;

	i = 0;
	found_player = 0;
	fill_chartab(chartab, title, map_height, map_width);
	while (i < *map_width)
	{
		j = 0;
		while (j < *map_height)
		{
			if (chartab[i][j] == 'X' && found_player == 0)
			{
				(*map)[i][j] = 'X';
				found_player = 1;
			}
			else
				(*map)[i][j] = (chartab[i][j] == 'X' ? 0 : chartab[i][j] - '0');
			j++;
		}
		i++;
	}
}
