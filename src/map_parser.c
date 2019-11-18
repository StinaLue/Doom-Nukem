/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:02:54 by phaydont          #+#    #+#             */
/*   Updated: 2019/11/18 15:47:51 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "doom.h"

#include <stdio.h>

int		write_map_header(int fd)
{
	int header;

	header = 7778;
	if (fd == -1)
		return (1);
	write(fd, &header, sizeof(int));
	return (0);
}

int		read_map_header(int fd)
{
	int	n;
	int	header;

	header = 7778;
	if (fd == -1)
		return (1);
	read(fd, &n, sizeof(int));
	if (n != header)
		return (1);
	return (0);
}

//index = number of walls (hardcoded but shouldnt be)
int		write_map_walls(int fd, t_wall *walls, int index)//can be remade to work with chained list
{
	int	total;

	if (fd < 3)
		return (1);
	total = write(fd, &index, sizeof(index));
	while (index-- > 0)
	{
		total += write(fd, &(walls[index].start_wall.x), sizeof(walls[index].start_wall.x));
		total += write(fd, &(walls[index].start_wall.y), sizeof(walls[index].start_wall.y));
		total += write(fd, &(walls[index].end_wall.x), sizeof(walls[index].end_wall.x));
		total += write(fd, &(walls[index].end_wall.y), sizeof(walls[index].end_wall.y));
		total += write(fd, &(walls[index].color), sizeof(walls[index].color));
	}
	printf("wall write: %d\n", total);
	return (0);
}

int		read_map_walls(int fd, t_wall *walls)
{
	int	total;
	int	index;
	int	wall_number;

	if (fd == -1)
		return (1);
	index = 0;
	total = read(fd, &wall_number, sizeof(wall_number));
	while (index < wall_number)
	{
		total += read(fd, &(walls[index].start_wall.x), sizeof(walls[index].start_wall.x));
		total += read(fd, &(walls[index].start_wall.y), sizeof(walls[index].start_wall.y));
		total += read(fd, &(walls[index].end_wall.x), sizeof(walls[index].end_wall.x));
		total += read(fd, &(walls[index].end_wall.y), sizeof(walls[index].end_wall.y));
		total += read(fd, &(walls[index].color), sizeof(walls[index].color));
		index++;
	}
	printf("wall read: %d\n", total);
	return (0);
}

int		parse_everything(t_wall *walls)
{
	int	fd;

	fd = creat("mapfile.DOOM", 0666);
	if (fd < 3)
		return (1);
	write_map_header(fd);
	write_map_walls(fd, walls, NB_WALLS);
	close(fd);
	fd = open("mapfile.DOOM", O_RDONLY);
	if (fd < 3)
		return (1);
	if (read_map_header(fd) == 0)
	{
		if (read_map_walls(fd, walls) == 1)
			return (1);
	}
	else
		return (1);
	return (0);
}
