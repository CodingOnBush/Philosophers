/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 17:25:33 by momrane          ###   ########.fr       */
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
			if (pthread_mutex_destroy(&data->shared.forks[i]))
				printf("Error: pthread_mutex_destroy\n");
			i++;
		}
		free(data->shared.forks);
	}
	if (pthread_mutex_destroy(&data->shared.pencil))
		printf("Error: pthread_mutex_destroy\n");
	if (pthread_mutex_destroy(&data->shared.update_looping))
		printf("Error: pthread_mutex_destroy\n");
	if (data->philos)
		free(data->philos);
	if (data)
		free(data);
}
