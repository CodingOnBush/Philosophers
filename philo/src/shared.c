/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:29:40 by momrane           #+#    #+#             */
/*   Updated: 2024/02/26 13:34:43 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_init_shared(t_data *data)
{
	data->shared.looping = 1;
	data->shared.someone_died = 0;
	data->shared.forks = ft_create_forks(data->philo_nb);
	if (!data->shared.forks)
		return (0);
	data->shared.forks_status = malloc(sizeof(int) * data->philo_nb);
	if (!data->shared.forks_status)
		return (free(data->shared.forks), 0);
	memset(data->shared.forks_status, 0, sizeof(int) * data->philo_nb);
	if (pthread_mutex_init(&data->shared.finish, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.pencil, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.update_looping, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.philo_mutex, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.beginning_mutex, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.check_philo, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.last_meal_mutex, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.someone_died_mutex, NULL))
		return (free(data->shared.forks), 0);
	return (1);
}
