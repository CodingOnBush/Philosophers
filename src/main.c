/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 07:55:35 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
