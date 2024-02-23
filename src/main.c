/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 07:52:46 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_check_philos_dead(t_philo *philos)
{
	t_data	*data;
	int		nb_philos;
	int		i;

	data = philos->data;
	nb_philos = data->nb_philos;
	i = 0;
	while (data->someone_died == -1 && !ft_all_philos_are_full(philos))
	{
		if (!ft_is_philo_alive(&philos[i]))
		{
			ft_print_msg(&philos[i], "died");
			data->someone_died = i;
			break ;
		}
		if (i == nb_philos - 1)
			i = 0;
		else
			i++;
		usleep(1);
	}
	if (ft_all_philos_are_full(philos))
		ft_print_msg(&philos[i], "All philosophers are full");
	pthread_mutex_unlock(&data->pencil);
	ft_unlock_and_destroy_forks(data);
}

int	main(int ac, char **av)
{
	t_philo	philos[200];
	t_data	data;

	if (!ft_init_data_and_philos(&data, philos, ac, av))
		return (-1);
	if (!ft_start_routines(philos, &data))
		return (-1);
	ft_check_philos_dead(philos);
	if (!ft_join_threads(philos, &data))
		return (-1);
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