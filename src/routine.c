/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 14:53:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->right->fork_mutex);
	ft_print_msg(philo->env, philo->id, "has taken a fork");
	ft_print_msg(philo->env, philo->id, "is eating");
	ft_wait(philo->env->time_to_eat);
	philo->last_meal = ft_get_current_time(philo->env->start_time);
	philo->meal_count++;
	philo->env->total_meals++;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->right->fork_mutex);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_wait(philo->env->time_to_eat);
	while (1)
	{
		ft_eat(philo);
		if (philo->meal_count == philo->env->meal_goal)
			break ;
		ft_print_msg(philo->env, philo->id, "is sleeping");
		ft_wait(philo->env->time_to_sleep);
		ft_print_msg(philo->env, philo->id, "is thinking");
	}
	if (philo->meal_count == philo->env->meal_goal)
		ft_print_msg(philo->env, philo->id, "has eaten ENOUGH");
	pthread_exit(&philo->thread);
	return (NULL);
}

void	*ft_boss_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_still_alive(philo) == 0)
		{
			philo->env->someone_died = 1;
			ft_print_msg(philo->env, philo->id, "died");
			break ;
		}
		if (philo->meal_count == philo->env->meal_goal)
		{
			ft_print_msg(philo->env, philo->id, "has eaten ENOUGH");
			break ;
		}
		philo = philo->right;
		ft_wait(10);
	}
	return (NULL);
}
