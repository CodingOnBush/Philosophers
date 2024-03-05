/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 08:54:57 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 09:46:23 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_free_simul(t_simul *simul)
{
	// int	i;

	if (simul->forks)
	{
		// i = 0;
		// while (i < simul->infos.nb_of_philo)
		// {
		// 	pthread_mutex_destroy(&simul->forks[i]);
		// 	i++;
		// }
		free(simul->forks);
	}
	if (simul->philos)
		free(simul->philos);
	// pthread_mutex_destroy(&simul->pencil);
	// pthread_mutex_destroy(&simul->philo_mutex);
	// pthread_mutex_destroy(&simul->simul_mutex);
	free(simul);
	return (NULL);
}
