/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 11:08:55 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	data;

	if (!ft_init_data(&data, ac, av))
		return (-1);
	philos = ft_create_philos(&data);
	if (!philos)
		return (-1);
	if (!ft_start_routines(philos, &data))
		return (-1);
	ft_check_philos_dead(philos);
	if (!ft_join_threads(philos, &data))
		return (-1);
	ft_destroy_all_mutex(&data);
	free(philos);
	free(data.forks);
	return (0);
}

/*
./philo 2 100 5000 200
./philo 198 210 100 100
./philo 200 210 100 100
./philo 2 210 100 100
*/