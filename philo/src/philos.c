/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:29:37 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 14:14:04 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*ft_create_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	if (!philos)
		return (NULL);
	memset(philos, 0, sizeof(t_philo) * data->philo_nb);
	i = 0;
	while (i < data->philo_nb)
	{
		philos[i].thrd = 0;
		philos[i].id = i;
		philos[i].meal_count = 0;
		// philos[i].fork = malloc(sizeof(pthread_mutex_t));
		// if (!philos[i].fork)
		// 	return (NULL);
		pthread_mutex_init(&(philos[i].fork), NULL);
		pthread_mutex_init(&(philos[i].last_meal_mutex), NULL);
		pthread_mutex_init(&(philos[i].meal_count_mutex), NULL);
		philos[i].last_meal = 0;
		philos[i].data = data;
		i++;
	}
	return (philos);
}
