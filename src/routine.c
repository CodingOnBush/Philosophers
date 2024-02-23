/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 10:56:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	if (data->someone_died != -1)
		return ;
	ft_print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nb_philos]);
	if (data->someone_died != -1)
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
	ft_print_msg(philo, "is eating");
	usleep(data->time_to_eat);
	philo->last_meal = ft_what_time_is_it();
	philo->meal_count++;
}

static void	ft_sleep_and_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_print_msg(philo, "is sleeping");
	usleep(data->time_to_sleep);
	ft_print_msg(philo, "is thinking");
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(10);
	while (data->someone_died == -1 && !ft_philo_is_full(philo))
	{
		ft_take_forks(philo);
		if (data->someone_died != -1)
			break ;
		ft_eat(philo);
		ft_drop_forks(philo);
		if (ft_philo_is_full(philo))
			break ;
		ft_sleep_and_think(philo);
	}
	return (NULL);
}
