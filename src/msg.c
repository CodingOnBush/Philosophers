/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/10 14:46:15 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_data *data, int philo_id, char *msg)
{
	long	time;

	time = ft_get_current_time(data->start_time);
	pthread_mutex_lock(&data->log_mutex);
	printf("%ld %d %s\n", time, philo_id + 1, msg);
	pthread_mutex_unlock(&data->log_mutex);
}
