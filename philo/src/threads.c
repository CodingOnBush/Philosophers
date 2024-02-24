/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:07:53 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 11:06:34 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_start_routines(t_philo *philos, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&philos[i].thread, NULL, ft_routine, (void *)&philos[i]) != 0)
		{
			printf("Error: can't create thread\n");
			return (0);
		}
		usleep(10);// 100
		i++;
	}
	return (1);
}

int	ft_join_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
