/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:01:46 by momrane           #+#    #+#             */
/*   Updated: 2024/02/05 19:42:43 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	philo->routine_start = 1;
	while (philo->alive == 1 && philo->meal_count < philo->meal_goal)
	{
		ft_start_eating(philo);
		ft_start_sleeping(philo);
		ft_start_thinking(philo);
	}
	return (NULL);
}

static void	ft_grab_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->right->fork_mutex);
}

static void	ft_drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->right->fork_mutex);
}

void	ft_start_eating(t_philo *philo)
{
	long	time;

	// printf("Philo %d want to eat\n", philo->id);
	ft_grab_fork(philo);
	if (ft_isphilo_dead(philo))
	{
		philo->alive = 0;
		philo->env->end_flag = 1;
		printf("%ld | %d is DEAD\n", ft_get_current_time(philo->start_time), philo->id);
		return ;
	}
	philo->status = 'e';
	time = ft_get_current_time(philo->start_time);
	printf("%ld | %d is eating\n", time, philo->id);
	ft_usleep(philo->time_to_eat);
	philo->meal_count++;
	philo->last_meal = ft_get_current_time(philo->start_time);
	ft_drop_fork(philo);
}

void	ft_start_sleeping(t_philo *philo)
{
	philo->status = 's';
	printf("%ld | %d is sleeping\n", ft_get_current_time(philo->start_time), philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	ft_start_thinking(t_philo *philo)
{
	philo->status = 't';
	printf("%ld | %d is thinking\n", ft_get_current_time(philo->start_time), philo->id);
}
