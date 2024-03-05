/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:05:07 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 09:47:42 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_start_simulation(t_simul *simul)
{
	t_philo	*philos;
	int		i;

	philos = simul->philos;
	simul->begin = ft_get_time();
	if (pthread_create(&simul->supervisor, NULL, ft_supervisor, simul))
		return (FAIL);
	i = 0;
	while (i < simul->infos.nb_of_philo)
	{
		if (pthread_create(&philos[i].thrd, NULL, ft_routine, &philos[i]))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	ft_wait_threads(t_simul *simul)
{
	int	i;

	pthread_join(simul->supervisor, NULL);
	i = 0;
	while (i < simul->infos.nb_of_philo)
	{
		pthread_join(simul->philos[i].thrd, NULL);
		i++;
	}
}
