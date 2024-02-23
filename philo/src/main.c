/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 17:08:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	if (!ft_init_data(data, ac, av))
		return (-1);
	philos = ft_create_philos(data);
	if (!philos)
		return (-1);
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].thread = i;
		philos[i].id = i;
		philos[i].meal_count = 0;
		philos[i].last_meal = data->start_time;
		philos[i].data = data;
		i++;
	}
	if (!ft_start_routines(philos, data))
		return (-1);
	ft_check_philos_dead(philos);
	if (!ft_join_threads(philos, data))
		return (-1);
	// ft_destroy_all_mutex(&data);
	// free(philos);
	// free(data.forks);
	return (0);
}

/*
./philo 2 100 5000 200
./philo 198 210 100 100
./philo 200 210 100 100
./philo 2 210 100 100


Ensure the code of philo complies with the following requirements and ask for explanations.
Check there is one thread per philosopher.
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
Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, and so forth.

*/