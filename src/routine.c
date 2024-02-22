/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/22 13:39:33 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	if (!ft_is_philo_alive(philo))
		return ;
	ft_print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nb_philos]);
	if (!ft_is_philo_alive(philo))
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
	pthread_mutex_lock(&data->pencil);
	printf("[%ld] %d is eating\n", ft_get_current_time(data->start_time), philo->id);
	pthread_mutex_unlock(&data->pencil);
	ft_wait(data->time_to_eat);
	philo->last_meal = ft_what_time_is_it();
	philo->meal_count++;
}

static void	ft_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->pencil);
	printf("[%ld] %d is sleeping\n", ft_get_current_time(data->start_time), philo->id);
	pthread_mutex_unlock(&data->pencil);
	ft_wait(data->time_to_sleep);
}

static void	ft_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->pencil);
	printf("[%ld] %d is thinking\n", ft_get_current_time(data->start_time), philo->id);
	pthread_mutex_unlock(&data->pencil);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&data->pencil);
	printf("[%ld] hi from thread %d\n", ft_get_current_time(data->start_time), philo->id);
	pthread_mutex_unlock(&data->pencil);
	if (philo->id % 2)
		ft_wait(data->time_to_die);
	while (ft_is_philo_alive(philo) && !ft_philo_is_full(philo))
	{
		ft_take_forks(philo);
		if (!ft_is_philo_alive(philo))
			break ;
		ft_eat(philo);
		ft_drop_forks(philo);
		ft_sleep(philo);
		ft_think(philo);
		ft_wait(10);
	}

	pthread_mutex_lock(&data->pencil);
	printf("[%ld] bye from thread %d\n", ft_get_current_time(data->start_time), philo->id);
	pthread_mutex_unlock(&data->pencil);
	return (NULL);
}
