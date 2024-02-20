/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/20 13:53:47 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 1)
		ft_wait(data->time_to_eat);
	while (data->routine_flag)
	{
		pthread_mutex_lock(&(data->forks[philo->id]));
		pthread_mutex_lock(&(data->forks[(philo->id + 1) % data->nb_philos]));
		if (!data->routine_flag)
			break ;
		ft_print_msg(philo, "has taken a fork");
		ft_print_msg(philo, "is eating");
		ft_wait(data->time_to_eat);
		philo->last_meal += data->time_to_eat;
		philo->meal_count++;
		data->meals_count++;
		pthread_mutex_unlock(&(data->forks[philo->id]));
		pthread_mutex_unlock(&(data->forks[(philo->id + 1) % data->nb_philos]));
		ft_print_msg(philo, "has dropped a fork");
		ft_print_msg(philo, "is sleeping");
		ft_wait(data->time_to_sleep);
		ft_print_msg(philo, "is thinking");
		ft_wait(10);
	}
	return (NULL);
}
