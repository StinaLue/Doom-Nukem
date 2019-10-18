/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:31:56 by afonck            #+#    #+#             */
/*   Updated: 2019/10/18 13:07:06 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

char	*translate_fps(int fps)
{
	static char charfps[11];
	int			i;

	i = 10;
	if (fps <= 0)
		return ("0");
	ft_bzero(charfps, 11);
	charfps[i] = '\0';
	i--;
	while (fps && i)
	{
		charfps[i] = (fps % 10) + '0';
		fps /= 10;
		i--;
	}
	return (&charfps[i + 1]);
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

int		is_valid_wall(int wall)
{
	if (wall == 1 || wall == 2)
		return (1);
	return (0);
}

void	print_map(int map[MAX_MAP][MAX_MAP], int width,
					int height, t_player *player)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if ((int)player->x == j && (int)player->y == i)
				ft_printf(". ");
			else
				ft_printf("%d ", map[i][j]);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}
