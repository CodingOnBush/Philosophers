/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:11:02 by momrane           #+#    #+#             */
/*   Updated: 2024/03/03 20:10:09 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*ft_supervisor(void *arg)
{
	t_simul	*simul;
	t_philo	*philos;
	int		i;
	long	last_meal;
	long	diff;

	simul = (t_simul *)arg;
	philos = simul->philos;
	i = 0;
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
		
		pthread_mutex_lock(&simul->philo_mutex);
		last_meal = philos[i].last_meal;
		pthread_mutex_unlock(&simul->philo_mutex);
		
		diff = ft_get_time() - last_meal;
		if (diff >= simul->infos.time_to_die)
		{
			ft_print_status(&philos[i], DEAD);
			printf("last meal %ld\n", diff);
			
			simul->state = i;
			pthread_mutex_unlock(&simul->simul_mutex);
			break;
		}
		pthread_mutex_unlock(&simul->simul_mutex);
		i++;
		if (i == simul->infos.nb_of_philo)
			i = 0;
		ft_usleep(10);
	}
	// printf("bye bye from supervisor\n");
	return (NULL);
}

int	main(int ac, char **av)
{
	t_simul		*simul;
	pthread_t	supervisor;

	simul = ft_create_simul(ac, av);
	if (!simul)
		return (1);
	pthread_create(&supervisor, NULL, ft_supervisor, simul);
	ft_start_simulation(simul);
	pthread_join(supervisor, NULL);
	ft_free_simul(simul);
	return (0);
}
