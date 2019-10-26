/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:00:17 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/26 12:23:47 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "doom.h"
#include <pthread.h>

void	multithread(t_doom *doom)
{
	t_doom		params[NB_THREADS];
	pthread_t	threads[NB_THREADS];
	int			i;

	i = 0;
	while (i < NB_THREADS)
	{
		ft_memcpy((void *)&params[i], (void *)doom, sizeof(t_doom));
		params[i].data.start_thread = (WIN_WIDTH / NB_THREADS) * i;
		params[i].data.end_thread = (WIN_WIDTH / NB_THREADS) * (i + 1);
		pthread_create(&threads[i], NULL, iterate_raycast, &params[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
}
