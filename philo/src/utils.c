/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/26 13:36:27 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_is_philo_alive(t_philo philo)
{
	long	current_time;
	long	diff;

	current_time = ft_what_time_is_it();
	if (current_time < 0)
		return (0);
	diff = current_time - philo.last_meal;
	if (diff >= philo.data->time_to_die)
		return (0);
	return (1);
}

int	ft_philo_is_dead(t_philo *philo)
{
	long	current_time;
	long	diff;

	pthread_mutex_lock(&philo->data->shared.last_meal_mutex);
	current_time = ft_what_time_is_it();
	if (current_time < 0)
		return (0);
	diff = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->data->shared.last_meal_mutex);
	if (diff >= philo->data->time_to_die)
	{
		// pthread_mutex_lock(&philo->data->shared.check_philo);
		philo->alive = 0;
		// pthread_mutex_unlock(&philo->data->shared.check_philo);
		return (1);
	}
	return (0);
}

int	ft_philo_is_full(t_philo philo)
{
	if (philo.data->meal_goal == -1)
		return (0);
	if (philo.meal_count >= philo.data->meal_goal)
		return (1);
	return (0);
}

// int	ft_check_looping(t_data *data)
// {
// 	if (pthread_mutex_lock(&data->shared.update_looping))
// 		return (0);
// 	if (data->shared.looping == 0)
// 	{
// 		pthread_mutex_unlock(&data->shared.update_looping);
// 		return (0);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(&data->shared.update_looping);
// 		return (1);
// 	}
// }

void	ft_set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->shared.beginning_mutex);
	pthread_mutex_lock(&philo->data->shared.last_meal_mutex);
	philo->last_meal = philo->data->beginning;
	pthread_mutex_unlock(&philo->data->shared.last_meal_mutex);
	pthread_mutex_unlock(&philo->data->shared.beginning_mutex);
}

void	ft_update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->shared.last_meal_mutex);
	philo->last_meal = philo->last_meal + philo->data->time_to_eat;
	pthread_mutex_unlock(&philo->data->shared.last_meal_mutex);
}
