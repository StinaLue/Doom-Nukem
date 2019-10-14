/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_chartab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:03:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/14 17:04:55 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

char	check_line(char *line)
{
	if (*line == '\0')
		return ('\0');
	while (*line != '\0')
	{
		if (*line != '0' && *line != '1' && *line != 'X')
			return (*line);
		line++;
	}
	return ('0');
}

void	copy_line(char *charline, char *line, int width)
{
	int i;

	i = 0;
	while (i < width)
	{
		charline[i] = line[i];
		i++;
	}
}

void	fill_chartab(char chartab[MAX_MAP][MAX_MAP], char *title, int *map_width, int *map_height)
{
	char	*line;
	int	ret;
	int	fd;
	int	w;

	*map_height = 0;
	ret = 0;
	w = 0;
	if ((fd = open(title, O_RDONLY | O_NOFOLLOW)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s could not be opened\n", title);
		exit(EXIT_FAILURE);
	}
	while ((ret = get_next_line(fd, &line)) > 0 && *map_height < MAX_MAP)
	{
		if (check_line(line) != '0')
		{
			ft_dprintf(STDERR_FILENO, "invalid character %{r}c in map\n", check_line(line));
			ft_memdel((void **)&line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		if (*map_height == 0)
			w = ft_strlen(line);
		*map_width = ft_strlen(line);
		if (*map_width != w)
		{
			ft_dprintf(STDERR_FILENO, "%{r}s is an uneven map, only rectangles or squares are allowed\n", title);
			ft_memdel((void **)&line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		if (*map_width > MAX_MAP)
		{
			ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX to %{b}d\n", title, *map_width);
			ft_memdel((void **)&line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		copy_line(chartab[*map_height], line, *map_width);
		ft_memdel((void **)&line);
		(*map_height)++;
	}
	ft_memdel((void **)&line);
	close(fd);
	if (*map_height >= MAX_MAP)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX to %{b}d\n", title, *map_height);
		exit(EXIT_FAILURE);
	}
}

void	fill_map(int (*map)[MAX_MAP][MAX_MAP], char *title, int *map_width, int *map_height)
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