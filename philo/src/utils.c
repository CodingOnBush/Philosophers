/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:58:58 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 09:52:46 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_status(t_philo *philo, char *status)
{
	long	ms;

	ms = ft_get_time() - philo->simul->begin;
	pthread_mutex_lock(&philo->simul->simul_mutex);
	pthread_mutex_lock(&philo->simul->pencil);
	if (philo->simul->state < 0 || philo->simul->state != ALL_ATE)
		printf("%ld %d %s\n", ms, philo->id, status);
	pthread_mutex_unlock(&philo->simul->pencil);
	pthread_mutex_unlock(&philo->simul->simul_mutex);
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

int	ft_get_simul_state(t_simul *simul)
{
	int	state;

	pthread_mutex_lock(&simul->simul_mutex);
	state = simul->state;
	pthread_mutex_unlock(&simul->simul_mutex);
	return (state);
}

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
