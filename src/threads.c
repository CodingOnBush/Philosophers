/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:07:53 by momrane           #+#    #+#             */
/*   Updated: 2024/02/22 17:21:08 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_start_routines(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, ft_routine,
			(void *)&philos[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_join_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}
