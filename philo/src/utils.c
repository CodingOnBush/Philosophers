/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:58:58 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 13:04:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_status(t_philo *philo, char *status)
{
	long	ms;

	ms = ft_get_simul_time(philo->simul);
	pthread_mutex_lock(&philo->simul->simul_mutex);
	if (philo->simul->state >= 0 || philo->simul->state == ALL_ATE)
	{
		pthread_mutex_unlock(&philo->simul->simul_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->simul->simul_mutex);
	pthread_mutex_lock(&philo->simul->pencil);
	printf("%ld %d %s\n", ms, philo->id, status);
	pthread_mutex_unlock(&philo->simul->pencil);
}

void	ft_update_last_meal(t_philo *philo, long new_last_meal)
{
	t_simul	*simul;

	simul = philo->simul;
	pthread_mutex_lock(&simul->philo_mutex);
	philo->last_meal = new_last_meal;
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
