/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:29:54 by afonck            #+#    #+#             */
/*   Updated: 2019/10/26 12:22:23 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"

void	check_title(char *title)
{
	int len;
	int bad_title;

	bad_title = 0;
	len = ft_strlen(title);
	len -= 1;
	if (len < 4)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s is not a valid map name\n", title);
		exit(EXIT_FAILURE);
	}
	if (title[len--] != 'd')
		bad_title = 1;
	if (title[len--] != '3')
		bad_title = 1;
	if (title[len--] != 'w')
		bad_title = 1;
	if (title[len] != '.')
		bad_title = 1;
	if (bad_title == 1)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s is not a valid map name\n", title);
		exit(EXIT_FAILURE);
	}
}

void	check_badwidth_map(int width, int mapwidth, void **line, int fd)
{
	if (width != mapwidth)
	{
		ft_dprintf(STDERR_FILENO, "your map is uneven, only rectangles or \
			squares are allowed\n");
		ft_memdel(line);
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (width >= MAX_MAP)
	{
		ft_dprintf(STDERR_FILENO, "your map is too big, please modify MAP_MAX \
			to %{b}d\n", width);
		ft_memdel(line);
		close(fd);
		exit(EXIT_FAILURE);
	}
}

void	check_badheight_map(int height, int fd, char *title)
{
	if ((close(fd)) == -1)
		ft_dprintf(STDERR_FILENO, "Error while closing %{r}s\n", title);
	if (height >= MAX_MAP)
	{
		ft_dprintf(STDERR_FILENO, "%{r}s is too big, please modify MAP_MAX \
			to %{b}d\n", title, height);
		exit(EXIT_FAILURE);
	}
}

char	check_line(char *line)
{
	if (*line == '\0')
		return ('\0');
	while (*line != '\0')
	{
		if (*line != '0' && *line != '1' && *line != '2' && *line != 'X')
			return (*line);
		line++;
	}
	return ('0');
}

void	verify_bordermap(int const (*map)[MAX_MAP][MAX_MAP],
			char *title, int map_width, int map_height)
{
	int i;
	int j;
	int k;
	int l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	while (is_valid_wall((*map)[0][i]) == 1 && i < map_width)
		i++;
	while (is_valid_wall((*map)[map_height - 1][j]) == 1 && j < map_width)
		j++;
	while (is_valid_wall((*map)[k][0]) == 1 && k < map_height)
		k++;
	while (is_valid_wall((*map)[l][map_width - 1]) == 1 && l < map_height)
		l++;
	if (i != map_width || j != map_width || k != map_height || l != map_height)
	{
		ft_dprintf(STDERR_FILENO, "map %{r}s is not surrounded by walls \
			(1 / 2), exiting...\n", title);
		exit(EXIT_FAILURE);
	}
}
