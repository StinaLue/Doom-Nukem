/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wav_parse_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:58:08 by afonck            #+#    #+#             */
/*   Updated: 2020/02/12 11:08:03 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_wav(char *file)
{
	int	len;

	len = 0;
	while (file[len])
		len++;
	len -= 1;
	if (len < 4)
		return (0);
	if (file[len--] != 'v')
		return (0);
	if (file[len--] != 'a')
		return (0);
	if (file[len--] != 'w')
		return (0);
	if (file[len] != '.')
		return (0);
	return (1);
}
