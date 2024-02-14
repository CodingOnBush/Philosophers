/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/14 08:18:51 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	// if (philo->id % 2)
		// ft_wait(data->time_to_eat);
	data->start_time = ft_what_time_is_it();
	philo->last_meal = data->start_time;
	while (data->someone_died == -1 || data->meals_count < data->meals_goal
		|| philo->meal_count == data->meal_goal)
	{
		printf("someone_died: %d\n", data->someone_died);
		pthread_mutex_lock(&(data->forks[philo->id]));
		pthread_mutex_lock(&(data->forks[(philo->id + 1) % data->nb_philos]));
		ft_print_msg(philo, "has taken a fork");
		ft_print_msg(philo, "is eating");
		ft_wait(data->time_to_eat);
		philo->last_meal = ft_what_time_is_it();
		philo->meal_count++;
		data->meals_count++;
		pthread_mutex_unlock(&(data->forks[philo->id]));
		pthread_mutex_unlock(&(data->forks[(philo->id + 1) % data->nb_philos]));
		// ft_print_msg(philo, "has dropped a fork");
		ft_print_msg(philo, "is sleeping");
		ft_wait(data->time_to_sleep);
		ft_print_msg(philo, "is thinking");
		// ft_wait(10);
	}
	data->routine_count++;
	return (NULL);
}
