/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 20:02:31 by afonck            #+#    #+#             */
/*   Updated: 2020/02/11 16:12:11 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "errno.h"

int		error_return(const char *error_msg, const char *sdl_error)
{
	if (sdl_error != NULL)
		ft_dprintf(STDERR_FILENO, error_msg, sdl_error);
	else
		ft_dprintf(STDERR_FILENO, error_msg);
	return (1);
}

int		error_return_wav(char *s1, char *s2, int fd)
{
	if (fd != -1)
	{
		if (close(fd) != 0)
			ft_dprintf(STDERR_FILENO, "error while closing file\n");
	}
	if (s1 && s2)
		ft_dprintf(STDERR_FILENO, s1, s2);
	else
		ft_dprintf(STDERR_FILENO, s1);
	return (1);
}

int		error_return_map(const char *error_msg, const char *errstr, int fd)
{
	if (fd != -1)
	{
		if (close(fd) != 0)
			ft_dprintf(STDERR_FILENO, "error during close: %{r}s\n", \
			strerror(errno));
	}
	if (errstr != NULL)
		ft_dprintf(STDERR_FILENO, error_msg, errstr);
	else
		ft_dprintf(STDERR_FILENO, error_msg);
	return (1);
}
