/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/21 13:46:18 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_philo *philo, char *msg)
{
	long	time;

	time = ft_get_current_time(philo->data->start_time);
	pthread_mutex_lock(&philo->data->log_mutex);
	if (philo->data->someone_died == -1)
		printf("[%ld] %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->log_mutex);
}
