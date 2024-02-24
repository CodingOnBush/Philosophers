/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 14:48:58 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(100);
	while (data->shared.looping)
	{
		pthread_mutex_lock(&data->shared.update_meal_count);
		if (!data->shared.looping)
		{
			pthread_mutex_unlock(&data->shared.update_meal_count);
			break ;
		}
		printf("I am philo %d and I took the update flag first\n", philo->id);
		philo->meal_count = data->meal_goal;
		printf("and here my meal count is %d\n", philo->meal_count);
		pthread_mutex_unlock(&data->shared.update_meal_count);
		usleep(10);
	}
	return (NULL);
}
