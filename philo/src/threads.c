/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:07:53 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 17:16:17 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_launch_philosophers_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = data->philos;
	while (i < data->philo_nb)
	{
		if (pthread_create(&philos[i].thrd, NULL, ft_routine, &philos[i]))
		{
			printf("Error: pthread_create\n");
			return ;
		}
		i++;
	}
}

void	ft_wait_for_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = data->philos;
	while (i < data->philo_nb)
	{
		if (pthread_join(philos[i].thrd, NULL))
		{
			printf("Error: pthread_join\n");
			return ;
		}
		i++;
	}
}
