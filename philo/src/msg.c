/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/26 12:07:04 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_data *data, int philo_id, char *msg)
{

	pthread_mutex_lock(&data->shared.pencil);
	pthread_mutex_lock(&data->shared.beginning_mutex);
	printf("%ld\t%d\t%s\n", ft_get_ms_since(data->beginning), philo_id, msg);
	pthread_mutex_unlock(&data->shared.beginning_mutex);
	pthread_mutex_unlock(&data->shared.pencil);


	// long	time;

	// pthread_mutex_lock(&data->shared.pencil);
	// time = ft_get_ms_since(data->beginning);
	// if (time < 0)
	// {
	// 	pthread_mutex_unlock(&data->shared.pencil);
	// 	return ;
	// }
	// printf("%ld\t%d\t%s\n", time, philo_id, msg);
	// pthread_mutex_unlock(&data->shared.pencil);
	

	
	// while (data->shared.update_looping.__align != 0)
	// 	ft_wait(1);
	// pthread_mutex_lock(&data->shared.update_looping);
	// time = ft_get_ms_since(data->beginning);
	// if (time < 0)
	// {
	// 	pthread_mutex_unlock(&data->shared.update_looping);
	// 	return ;
	// }
	// if (data->shared.looping)
	// 	printf("%ld\t%d\t%s\n", time, philo_id, msg);
	// pthread_mutex_unlock(&data->shared.update_looping);
}
