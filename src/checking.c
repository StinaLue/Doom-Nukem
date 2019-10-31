/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:29:54 by afonck            #+#    #+#             */
/*   Updated: 2019/10/31 18:27:38 by sluetzen         ###   ########.fr       */
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
			char *title, int map_height, int map_width)
{
	int i;
	int j;
	int k;
	int l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	while (is_valid_wall((*map)[i][0]) == 1 && i < map_width)
	{
		printf("map[i = %d][0]: %d\n", i, (*map)[i][0]);
		i++;
	}
	//printf("\n\ni: %d, width: %d\n", i, map_width);
	while (is_valid_wall((*map)[j][map_height - 1]) == 1 && j < map_width)
	{
		printf("map[j = %d][%d]: %d\n", j, map_height - 1, (*map)[j][map_height - 1]);
		j++;
		printf("map[j = %d][%d]: %d\n", j, map_height - 1, (*map)[j][map_height - 1]);
	}
	while (is_valid_wall((*map)[0][k]) == 1 && k < map_height)
	{
		printf("map[0][k = %d]: %d\n", k, (*map)[0][k]);
		k++;
	}
	while (is_valid_wall((*map)[map_width - 1][l]) == 1 && l < map_height)
	{
		printf("map[%d][l = %d]: %d\n", map_width - 1, l, (*map)[map_width - 1][l]);
		l++;
	}
	if (i != map_width || j != map_width || k != map_height || l != map_height)
	{
		ft_dprintf(STDERR_FILENO, "map %{r}s is not surrounded by walls \
(1 / 2), exiting...\n", title);
		exit(EXIT_FAILURE);
	}
}
