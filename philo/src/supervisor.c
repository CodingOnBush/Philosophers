/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:53:30 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 09:51:37 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_supervisor(void *arg)
{
	t_philo	*philos;
	t_simul	*simul;
	long	diff;
	int		i;
	int		all_ate;

	simul = (t_simul *)arg;
	philos = simul->philos;
	i = 0;
	all_ate = 1;
	while (i < simul->infos.nb_of_philo)
	{	
		pthread_mutex_lock(&simul->simul_mutex);
		if (simul->state == ALL_ATE)
		{
			pthread_mutex_lock(&simul->pencil);
			printf("All philosophers ate enough (at least %d times)\n", simul->infos.meal_goal);
			pthread_mutex_unlock(&simul->pencil);
			pthread_mutex_unlock(&simul->simul_mutex);
			break;
		}
		if (simul->state >= 0)
		{
			pthread_mutex_lock(&simul->pencil);
			printf("%ld %d %s\n", ft_get_time() - simul->begin, philos[i].id, DEAD);
			pthread_mutex_unlock(&simul->pencil);
			// ft_print_status(&philos[i], DEAD);
			pthread_mutex_unlock(&simul->simul_mutex);
			break;
		}
		diff = ft_get_time();
		pthread_mutex_lock(&simul->philo_mutex);
		if (simul->infos.meal_goal == NO_MEAL_GOAL || philos[i].meal_count < simul->infos.meal_goal)
			all_ate = 0;
		diff = diff - philos[i].last_meal;
		pthread_mutex_unlock(&simul->philo_mutex);
		if (diff >= simul->infos.time_to_die)
		{
			// pthread_mutex_lock(&simul->pencil);
			// printf("%ld %d %s\n", ft_get_time() - simul->begin, philos[i].id, DEAD);
			// pthread_mutex_unlock(&simul->pencil);
			simul->state = i;
			// pthread_mutex_unlock(&simul->simul_mutex);
			// break;
		}
		pthread_mutex_unlock(&simul->simul_mutex);
		i++;
		if (i == simul->infos.nb_of_philo)
		{
			i = 0;
			if (all_ate == 1)
			{
				pthread_mutex_lock(&simul->simul_mutex);
				simul->state = ALL_ATE;
				pthread_mutex_unlock(&simul->simul_mutex);
			}
			all_ate = 1;
			usleep(100);
		}
	}
	return (NULL);
}
