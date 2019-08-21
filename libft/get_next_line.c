/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:14:22 by afonck            #+#    #+#             */
/*   Updated: 2019/03/25 13:31:45 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_line_append(char *line, char *buf, size_t len)
{
	char	*newline;
	size_t	total_size;

	if (line == NULL || buf == NULL)
		return (NULL);
	total_size = ft_strlen(line) + len;
	if ((newline = ft_strnew(total_size)) == NULL)
		return (NULL);
	ft_strcpy(newline, line);
	ft_strncat(newline, buf, len);
	ft_strdel(&line);
	return (newline);
}

int			get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE + 1];
	char		*pos;
	int			ret;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0 || BUFF_SIZE < 1)
		return (-1);
	*line = ft_strnew(0);
	while (1)
	{
		pos = ft_strchr(buf, '\n');
		if (pos != NULL)
		{
			*line = ft_line_append(*line, buf, pos - buf);
			ft_strncpy(buf, buf + (pos - buf + 1), BUFF_SIZE - (pos - buf));
			return (1);
		}
		*line = ft_line_append(*line, buf, BUFF_SIZE);
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		if (ret == 0)
			return ((**line) ? 1 : 0);
	}
}
