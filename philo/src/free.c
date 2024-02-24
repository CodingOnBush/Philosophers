/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 11:50:21 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free_data(t_data *data)
{
	int	i;

	if (data->shared.forks)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_destroy(&data->shared.forks[i]);
			i++;
		}
		free(data->shared.forks);
	}
	pthread_mutex_destroy(&data->shared.pencil);
	pthread_mutex_destroy(&data->shared.update_flags);
	if (data->philos)
		free(data->philos);
	if (data)
		free(data);
}
