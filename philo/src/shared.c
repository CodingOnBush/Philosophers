/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:29:40 by momrane           #+#    #+#             */
/*   Updated: 2024/02/25 17:24:59 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_init_shared(t_data *data)
{
	data->shared.looping = 1;
	data->shared.forks = ft_create_forks(data->philo_nb);
	if (!data->shared.forks)
		return (0);
	if (pthread_mutex_init(&data->shared.pencil, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.finish, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.philo_mutex, NULL))
		return (free(data->shared.forks), 0);
	return (1);
}
