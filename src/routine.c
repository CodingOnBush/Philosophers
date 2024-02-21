/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/21 14:44:57 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_checker_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (data->loop_flag)
	{
		if (data->someone_died > -1 || data->meals_count == data->meals_goal)
		{
			data->loop_flag = 0;
			break ;
		}
		if (ft_get_current_time(philo->last_meal) > philo->data->time_to_die)
		{
			ft_print_msg(philo, "died");
			philo->data->someone_died = philo->id;
			data->loop_flag = 0;
			break ;
		}
	}
	
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	printf("[%ld] hi from thread %d\n", ft_get_current_time(data->start_time), philo->id);
	if (philo->id % 2 == 1)
		ft_wait(data->time_to_eat);
	while (data->someone_died < 0 && data->meals_count != data->meals_goal)
	{
		pthread_mutex_lock(&(data->forks[philo->id]));
		if (data->someone_died > -1)
			break ;
		ft_print_msg(philo, "has taken a fork");
		pthread_mutex_lock(&(data->forks[(philo->id + 1) % data->nb_philos]));
		if (data->someone_died > -1)
			break ;
		ft_print_msg(philo, "has taken a fork");
		ft_print_msg(philo, "is eating");
		ft_wait(data->time_to_eat);
		philo->last_meal = ft_get_current_time(data->start_time);
		philo->meal_count++;
		data->meals_count++;
		pthread_mutex_unlock(&(data->forks[philo->id]));
		pthread_mutex_unlock(&(data->forks[(philo->id + 1) % data->nb_philos]));
		ft_print_msg(philo, "is sleeping");
		ft_wait(data->time_to_sleep);
		ft_print_msg(philo, "is thinking");
		ft_wait(1000);
	}
	return (NULL);
}
