/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/12 16:26:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_philo_routine2(void *arg)
{
	t_philo2	*philos;

	philos = (t_philo2 *)arg;
	pthread_mutex_lock(&philos->data->log_mutex);
	printf("I am in thread %d\n", philos->id);
	pthread_mutex_unlock(&philos->data->log_mutex);
	while (philos->data->someone_died == -1)
	{
		ft_wait(2000);
	}
	philos->is_dead = 1;
	pthread_mutex_lock(&philos->data->log_mutex);
	printf("Philosopher %d is dead\n", philos->id);
	pthread_mutex_unlock(&philos->data->log_mutex);
	pthread_exit(NULL);
	return (NULL);
}
