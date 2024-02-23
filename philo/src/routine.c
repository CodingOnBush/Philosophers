/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 14:54:45 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	if (data->someone_died)
		return ;
	ft_print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nb_philos]);
	if (data->someone_died)
		return ;
	ft_print_msg(philo, "has taken a fork");
}

static void	ft_drop_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->nb_philos]);
}

static void	ft_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->someone_died)
		return ;
	ft_print_msg(philo, "is eating");
	ft_wait(data->time_to_eat);
	philo->last_meal = ft_what_time_is_it();
	if (data->someone_died)
		return ;
}

static void	ft_sleep_and_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->someone_died)
		return ;
	ft_print_msg(philo, "is sleeping");
	ft_wait(data->time_to_sleep);
	if (data->someone_died)
		return ;
	ft_print_msg(philo, "is thinking");
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_wait(data->time_to_eat);
	while (!data->someone_died && !ft_philo_is_full(philo))
	{
		// ft_print_msg(philo, "trying to take forks");
		ft_take_forks(philo);
		if (data->someone_died)
			break ;
		ft_eat(philo);
		ft_drop_forks(philo);
		if (ft_philo_is_full(philo))
			break ;
		philo->meal_count++;
		ft_sleep_and_think(philo);
	}
	return (NULL);
}
