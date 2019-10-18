/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:26:24 by afonck            #+#    #+#             */
/*   Updated: 2019/10/18 13:13:01 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void	open_error(char *title)
{
	ft_dprintf(STDERR_FILENO, "%{r}s could not be opened\n", title);
	exit(EXIT_FAILURE);
}

void	invalid_char_error(char badchar, void **line, int fd)
{
	ft_dprintf(STDERR_FILENO, "invalid character %{r}c in map\n", badchar);
	ft_memdel(line);
	close(fd);
	exit(EXIT_FAILURE);
}

int		argc_error(void)
{
	ft_dprintf(STDERR_FILENO, "usage: ./wolf3d %{g}s\n", "[valid .w3d map]");
	return (EXIT_FAILURE);
}

int		size_error(void)
{
	ft_dprintf(STDERR_FILENO, "max/min size of map = %{b}s, you chose %{r}d / \
		max/min screen size = %{b}s, you chose %{r}d x %{r}d\n", "100/10", \
		MAX_MAP, "1920 x 1080/100 x 100", WIN_WIDTH, WIN_HEIGHT);
	return (EXIT_FAILURE);
}

int		nbthreads_error(void)
{
	ft_printf("max nb of threads = %{r}s, you chose %{r}d\n", "10", NB_THREADS);
	return (EXIT_FAILURE);
}
