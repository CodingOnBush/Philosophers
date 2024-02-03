/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:01:46 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 12:29:43 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("Philo %d is waiting for a fork\n", philo->id + 1);
	pthread_mutex_unlock(&philo->mutex);
}

void	ft_render_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("Philo %d has taken a fork\n", philo->id + 1);
	pthread_mutex_unlock(&philo->mutex);
}

void	ft_start_eating(t_env env, t_philo *philo)
{
	philo->status = 'e';
	philo->last_meal = 0;
	philo->eat_count++;
	printf("Philo %d is eating\n", philo->id + 1);
	usleep(env.eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
}

void	ft_start_sleeping(t_env env, t_philo *philo)
{
	philo->status = 's';
	printf("Philo %d is sleeping\n", philo->id + 1);
	usleep(env.sleep * 1000);
}

void	ft_start_thinking(t_env env, t_philo *philo)
{
	(void)env;
	philo->status = 't';
	printf("Philo %d is thinking\n", philo->id + 1);
}
