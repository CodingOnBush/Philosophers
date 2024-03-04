/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:53:30 by momrane           #+#    #+#             */
/*   Updated: 2024/03/04 16:35:02 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_supervisor(void *arg)
{
	t_philo	*philos;
	t_simul	*simul;
	long	diff;
	int		i;
	int		meal_count;
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
			// printf("ooooohhh ALL PHILOS ATE ENOUGH\n");
			pthread_mutex_unlock(&simul->simul_mutex);
			break;
		}
		if (simul->state >= 0)
		{
			ft_print_status(&philos[i], DEAD);
			pthread_mutex_unlock(&simul->simul_mutex);
			break;
		}
		
		diff = ft_get_time();
		pthread_mutex_lock(&simul->philo_mutex);
		diff = diff - philos[i].last_meal;
		meal_count = philos[i].meal_count;
		pthread_mutex_unlock(&simul->philo_mutex);
		
		if (simul->infos.meal_goal == NO_MEAL_GOAL || meal_count < simul->infos.meal_goal)
			all_ate = 0;

		if (diff >= simul->infos.time_to_die)
		{
			ft_print_status(&philos[i], DEAD);
			// printf("[%d]last meal %ld\n", i + 1, diff);
			
			simul->state = i;
			pthread_mutex_unlock(&simul->simul_mutex);
			break;
		}
		pthread_mutex_unlock(&simul->simul_mutex);
		i++;
		if (i == simul->infos.nb_of_philo)
		{
			i = 0;
			if (all_ate == 1)
			{
				printf("HEY ALL PHILOS ATE ENOUGH\n");
				pthread_mutex_lock(&simul->simul_mutex);
				simul->state = ALL_ATE;
				pthread_mutex_unlock(&simul->simul_mutex);
				break;
			}
			all_ate = 1;
			usleep(100);
		}
	}
	// printf("bye bye from supervisor\n");
	return (NULL);
}
