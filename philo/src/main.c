/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 14:49:20 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Hello from thrd %d and wait...\n", philo->id);
	ft_wait(3000);
	printf("thrd %d finished\n", philo->id);
	return (NULL);
}

static void	ft_watching_philosophers(t_data *data)
{
	int		philos_full;
	t_philo	*philos;
	int		i;

	philos_full = 0;
	philos = data->philos;
	i = 0;
	while (i < data->philo_nb)
	{
		if (!ft_is_philo_alive(philos[i]))
		{
			printf("Philosopher %d died\n", philos[i].id);
			break;
		}
		if (ft_philo_is_full(philos[i]))
			philos_full++;
		if (i == data->philo_nb - 1)
		{
			i = 0;
			if (philos_full == data->philo_nb)
				break ;
			philos_full = 0;
		}
		else
			i++;
	}
	pthread_mutex_lock(&data->shared.update_flags);
	data->shared.looping = 0;
	if (philos_full == data->philo_nb)
		data->shared.philo_full = 1;
	else
		data->shared.someone_died = 1;
	pthread_mutex_unlock(&data->shared.update_flags);
}


int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_create_data(ac, av);
	if (!data)
		return (1);
	ft_launch_philosophers_threads(data);
	ft_watching_philosophers(data);
	ft_wait_for_threads(data);
	printf("data->shared.looping : %d\n", data->shared.looping);
	printf("data->shared.someone_died : %d\n", data->shared.someone_died);
	printf("data->shared.philo_full : %d\n", data->shared.philo_full);
	printf("Simulation finished\n");
	ft_free_data(data);
	return (0);
}

/*
./philo 2 100 5000 200
./philo 198 210 100 100
./philo 200 210 100 100
./philo 2 210 100 100
Ensure the code of philo complies with the following requirements and ask for explanations.
Check there is one thrd per philosopher.
Check there is only one fork per philosopher.
Check if there is a mutex per fork and that it's used to check the fork value and/or change it.
Check the outputs are never mixed up.
Check how the death of a philosopher is verified and if there is a mutex to prevent a philosopher from dying and starting eating at the same time.
philo testing
Do not test with more than 200 philosophers.
Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
Test 1 800 200 200. The philosopher should not eat and should die.
Test 5 800 200 200. No philosopher should die.
Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
Test 4 410 200 200. No philosopher should die.
Test 4 310 200 100. One philosopher should die.
Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time,
	that they don't steal forks, and so forth.

*/