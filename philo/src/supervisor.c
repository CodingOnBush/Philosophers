/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:53:30 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 12:53:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_update_vars(t_simul *simul, t_philo *philo, int *all_ate)
{
	long	diff;

	diff = ft_get_time();
	pthread_mutex_lock(&simul->philo_mutex);
	if (simul->infos.meal_goal == NO_MEAL_GOAL)
		*all_ate = 0;
	if (philo->meal_count < simul->infos.meal_goal)
		*all_ate = 0;
	diff = diff - philo->last_meal;
	pthread_mutex_unlock(&simul->philo_mutex);
	pthread_mutex_lock(&simul->simul_mutex);
	if (diff >= simul->infos.time_to_die)
		simul->state = philo->id;
	pthread_mutex_unlock(&simul->simul_mutex);
}

static int	ft_check_philo(t_simul *simul, t_philo *philo, int *all_ate)
{
	pthread_mutex_lock(&simul->simul_mutex);
	if (simul->state == ALL_ATE)
	{
		pthread_mutex_unlock(&simul->simul_mutex);
		return (STOP);
	}
	if (simul->state >= 0)
	{
		pthread_mutex_lock(&simul->pencil);
		printf("%ld %d %s\n", ft_get_time() - simul->begin, philo->id, DEAD);
		pthread_mutex_unlock(&simul->pencil);
		pthread_mutex_unlock(&simul->simul_mutex);
		return (STOP);
	}
	pthread_mutex_unlock(&simul->simul_mutex);
	ft_update_vars(simul, philo, all_ate);
	return (CONTINUE);
}

void	*ft_supervisor(void *arg)
{
	t_simul	*simul;
	int		i;
	int		all_ate;

	simul = (t_simul *)arg;
	while (1)
	{
		i = 0;
		all_ate = 1;
		while (i < simul->infos.nb_of_philo)
		{
			if (ft_check_philo(simul, &simul->philos[i], &all_ate) == STOP)
				return (NULL);
			i++;
			usleep(10);
		}
		if (all_ate == 1)
		{
			pthread_mutex_lock(&simul->simul_mutex);
			simul->state = ALL_ATE;
			pthread_mutex_unlock(&simul->simul_mutex);
		}
	}
	return (NULL);
}
