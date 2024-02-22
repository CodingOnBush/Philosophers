/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/22 17:55:20 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_philo *philo, char *msg)
{
	long	time;

	time = ft_get_current_time(philo->data->start_time);
	pthread_mutex_lock(&philo->data->pencil);
	if (philo->data->someone_died == -1)
		printf("%ld\t%d\t%s\n", time, (philo->id + 1), msg);
	pthread_mutex_unlock(&philo->data->pencil);
}
