/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:07:53 by momrane           #+#    #+#             */
/*   Updated: 2024/02/25 15:05:15 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_launch_philosophers_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = data->philos;
	data->beginning = ft_what_time_is_it();
	while (i < data->philo_nb)
	{
		if (pthread_create(&philos[i].thrd, NULL, ft_routine, &philos[i]))
		{
			printf("Error: pthread_create\n");
			return ;
		}
		i += 2;
	}
	ft_wait(data->time_to_eat / 10);
	i = 1;
	while (i < data->philo_nb)
	{
		if (pthread_create(&philos[i].thrd, NULL, ft_routine, &philos[i]))
		{
			printf("Error: pthread_create\n");
			return ;
		}
		i += 2;
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
