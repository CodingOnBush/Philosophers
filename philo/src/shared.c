/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:29:40 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 12:35:27 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_init_shared(t_data *data)
{
	data->loop = -42;
	data->shared.forks = ft_create_forks(data->philo_nb);
	if (!data->shared.forks)
		return (0);
	if (pthread_mutex_init(&data->shared.pencil, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->loop_mutex, NULL))
		return (free(data->shared.forks), 0);
		// return (0);
	return (1);
}
