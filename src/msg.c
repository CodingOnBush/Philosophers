/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/20 21:11:45 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_philo *philo, char *msg)
{
	long	time;

	if (philo->data->someone_died == -1)
	{
		time = ft_get_current_time(philo->data->start_time);
		pthread_mutex_lock(&philo->data->log_mutex);
		printf("[%ld] %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->log_mutex);
	}
}
