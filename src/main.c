/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/13 11:02:03 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_start_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, ft_philo_routine,
				(void *)&philos[i]) < 0)
			return (-1);
		if (pthread_detach(philos[i].thread) < 0)
			return (-1);
		i++;
	}
	return (0);
}

void	*ft_run_loop(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		i;

	philos = (t_philo *)arg;
	data = philos->data;
	if (ft_start_threads(philos) < 0)
		pthread_exit(NULL);
	while (data->someone_died == -1)
	{
		ft_check_philos(philos);
		ft_wait(10);
	}
	i = 0;
	while (i < data->nb_philos)
	{
		printf("cancel thread %d\n", i);
		pthread_cancel(philos[i].thread);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_exit(NULL);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	main_thread;

	if (ft_init_everything(&data, ac, av) < 0)
		return (-1);
	philos = ft_create_philos(&data);
	if (!philos)
		return (-1);
	pthread_create(&main_thread, NULL, ft_run_loop, (void *)philos);
	pthread_join(main_thread, NULL);
	
	free(philos);
	free(data.forks);
	return (0);
}
