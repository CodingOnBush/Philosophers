/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/22 13:40:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_philo	philos[200];
	t_data	data;

	if (!ft_init_data_and_philos(&data, philos, ac, av))
		return (-1);
	if (data.nb_philos == 1)
	{
		ft_wait(data.time_to_die);
		ft_print_msg(&philos[0], "died");
	}
	else
	{
		if (!ft_start_routines(philos, &data))
			return (-1);
		if (!ft_join_threads(philos, &data))
			return (-1);
	}
	ft_destroy_all_mutex(&data);
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