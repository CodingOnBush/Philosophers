/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/25 17:48:13 by momrane          ###   ########.fr       */
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
	{
		// printf("Last meal: %ld\n", philo.last_meal);
		// printf("Current time: %ld\n", current_time);
		// printf("Diff: %ld\n", diff);
		return (0);
	}
	return (1);
}

int	ft_philo_is_dead(long last_meal, t_data *data)
{
	long	current_time;
	long	diff;

	current_time = ft_what_time_is_it();
	if (current_time < 0)
		return (0);
	diff = current_time - last_meal;
	if (diff >= data->time_to_die)
		return (1);
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

int	ft_check_looping(t_data *data)
{
	if (pthread_mutex_lock(&data->shared.update_looping))
		return (0);
	if (data->shared.looping == 0)
	{
		pthread_mutex_unlock(&data->shared.update_looping);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&data->shared.update_looping);
		return (1);
	}
}
