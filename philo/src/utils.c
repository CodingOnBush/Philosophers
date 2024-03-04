/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:58:58 by momrane           #+#    #+#             */
/*   Updated: 2024/03/04 23:39:00 by allblue          ###   ########.fr       */
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

void	ft_update_last_meal(t_philo *philo, long new_last_meal)
{
	t_simul	*simul;

	simul = philo->simul;
	pthread_mutex_lock(&simul->philo_mutex);
	// printf("[%d]Previous last_meal at : %ld\n", philo->id, philo->last_meal - simul->begin);
	philo->last_meal = new_last_meal;
	// printf("[%d]New last_meal at : %ld\n", philo->id, philo->last_meal - simul->begin);
	pthread_mutex_unlock(&simul->philo_mutex);
}
