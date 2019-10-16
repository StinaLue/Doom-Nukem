/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:00:17 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/16 13:46:56 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include <pthread.h>

void	multithread(t_wolf *wolf)
{
	t_wolf		params[NB_THREADS];
	pthread_t	threads[NB_THREADS];
	int			i;

	i = 0;
	while (i < NB_THREADS)
	{
		ft_memcpy((void *)&params[i], (void *)wolf, sizeof(t_wolf));
		params[i].data.start_thread = (WIN_WIDTH / NB_THREADS) * i;
		params[i].data.end_thread = (WIN_WIDTH / NB_THREADS) * (i + 1);
		pthread_create(&threads[i], NULL, iterate_raycast, &params[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
}
