/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:03:54 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 11:07:08 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_init_mutex(t_data *data)
{
	int	i;
	int	size;

	size = data->philo_nb * sizeof(pthread_mutex_t);
	data->shared.forks = (pthread_mutex_t *)malloc(size);
	if (!data->shared.forks)
		return (0);
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->shared.forks[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->shared.pencil, NULL))
		return (0);
	if (pthread_mutex_init(&data->shared.update_flags, NULL))
		return (0);
	return (1);
}
