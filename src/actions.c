/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:01:46 by momrane           #+#    #+#             */
/*   Updated: 2024/02/05 17:32:59 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_philo_routine(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	if (args->philo->id % 2 == 0)
		ft_wait(args->env->time_to_eat);
	args->philo->routine_start = 1;
	while (args->philo->alive == 1)
	{
		ft_start_eating(*(args->env), args->philo);
		ft_start_sleeping(*(args->env), args->philo);
		ft_start_thinking(*(args->env), args->philo);
	}
	return (NULL);
}

static void	ft_grab_fork(t_env env, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->right->fork_mutex);
	printf("Philo %d has taken a fork\n", philo->id);
}

static void	ft_drop_fork(t_env env, t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->right->fork_mutex);
}

void	ft_start_eating(t_env env, t_philo *philo)
{
	ft_grab_fork(env, philo);
	if (ft_isphilo_dead(env, philo))
		return ;
	philo->status = 'e';
	printf("%ld Philo %d is eating\n", ft_get_current_time(env), philo->id);
	ft_wait(env.time_to_eat);
	philo->meal_count++;
	philo->last_meal = ft_get_current_time(env);
	ft_drop_fork(env, philo);
}

void	ft_start_sleeping(t_env env, t_philo *philo)
{
	philo->status = 's';
	printf("Philo %d is sleeping\n", philo->id + 1);
	ft_wait(env.time_to_sleep);
}

void	ft_start_thinking(t_env env, t_philo *philo)
{
	philo->status = 't';
	printf("Philo %d is thinking\n", philo->id + 1);
}
