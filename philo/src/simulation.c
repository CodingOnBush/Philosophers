/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:05:07 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 10:42:27 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_start_odd_philos(t_simul *simul)
{
	t_philo	*philos;
	int		i;

	philos = simul->philos;
	i = 0;
	while (i < simul->infos.nb_of_philo)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&philos[i].thrd, NULL, ft_routine, &philos[i]))
				return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

static int	ft_start_even_philos(t_simul *simul)
{
	t_philo	*philos;
	int		i;

	philos = simul->philos;
	i = 0;
	while (i < simul->infos.nb_of_philo)
	{
		if (i % 2 != 0)
		{
			if (pthread_create(&philos[i].thrd, NULL, ft_routine, &philos[i]))
				return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_start_simulation(t_simul *simul)
{
	t_philo	*philos;

	philos = simul->philos;
	simul->begin = ft_get_time();
	if (pthread_create(&simul->supervisor, NULL, ft_supervisor, simul))
		return (FAIL);
	if (ft_start_odd_philos(simul) == FAIL)
		return (FAIL);
	usleep(100);
	if (ft_start_even_philos(simul) == FAIL)
		return (FAIL);
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
