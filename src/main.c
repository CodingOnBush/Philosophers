/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/21 18:13:29 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_start_routines(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, ft_philo_routine,
			(void *)&philos[i]);
		i++;
	}
	i = 0;
	while (i < philos->data->nb_philos)
	{
		printf("joining thread %d\n", i);
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

static void	ft_destroy_forks_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	philos[200];
	t_data	data;
	int		iter;

	if (ft_init_data(&data, ac, av) < 0)
		return (-1);
	ft_init_philos(&data, philos);
	if (data.nb_philos > 1)
		ft_start_routines(philos);
	else
	{
		ft_wait(data.time_to_die);
		ft_print_msg(&philos[0], "is dead");
	}
	printf("exiting main\n");
	ft_destroy_forks_mutex(&data);
	if (data.someone_died > 0)
		ft_print_msg(&philos[data.someone_died], "died");
	if (data.meals_count == data.meals_goal && data.meals_goal > 0)
		printf("[%ld] everyone ate enough\n", ft_get_current_time(data.start_time));
	ft_wait(1000);
	pthread_mutex_destroy(&data.log_mutex);
	return (0);
}

/*
Do not test with more than 200 philosophers.
Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
Test 1 800 200 200. The philosopher should not eat and should die.
Test 5 800 200 200. No philosopher should die.
Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
Test 4 410 200 200. No philosopher should die.
Test 4 310 200 100. One philosopher should die.
Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
Test with any values of your choice to verify all the requirements.
Ensure philosophers die at the right time, that they don't steal forks,
	and so forth.
*/