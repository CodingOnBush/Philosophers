/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:54:57 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 12:29:35 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_free_simul(t_simul *simul)
{
	int	i;

	i = 0;
	if (simul->philos)
	{
		while (i < simul->infos.nb_of_philo)
		{
			pthread_mutex_destroy(&simul->forks[i]);
			i++;
		}
	}
	if (simul->forks)
		free(simul->forks);
	pthread_mutex_destroy(&simul->pencil);
	pthread_mutex_destroy(&simul->simul_mutex);
	pthread_mutex_destroy(&simul->philo_mutex);
	if (simul->philos)
		free(simul->philos);
	free(simul);
	return (NULL);
}
