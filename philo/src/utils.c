/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:58:58 by momrane           #+#    #+#             */
/*   Updated: 2024/03/03 20:04:43 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_status(t_philo *philo, char *status)
{
	long	ms;

	ms = ft_get_time() - philo->simul->begin;
	pthread_mutex_lock(&philo->simul->print_mutex);
	// (void)ms;
	// (void)status;
	// pthread_mutex_lock(&philo->simul->simul_mutex);
	// if (print)
	printf("%ld %d %s\n", ms, philo->id, status);
	// pthread_mutex_unlock(&philo->simul->simul_mutex);
	
	pthread_mutex_unlock(&philo->simul->print_mutex);
}
