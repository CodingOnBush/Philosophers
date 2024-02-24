/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 11:06:34 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static void	ft_take_forks(t_philo *philo)
// {
// 	t_data	*data;

// 	data = philo->data;
// 	pthread_mutex_lock(&data->forks[philo->id]);
// 	if (data->someone_died)
// 		return ;
// 	ft_print_msg(philo[philo->id], "has taken a fork");
// 	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->philo_nb_philos]);
// 	if (data->someone_died)
// 		return ;
// 	ft_print_msg(philo[philo->id], "has taken a fork");
// }

// static void	ft_drop_forks(t_philo *philo)
// {
// 	t_data	*data;

// 	data = philo->data;
// 	pthread_mutex_unlock(&data->forks[philo->id]);
// 	pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->philo_nb_philos]);
// }

// static void	ft_eat(t_philo *philo)
// {
// 	t_data	*data;

// 	data = philo->data;
// 	if (data->someone_died)
// 		return ;
// 	ft_print_msg(philo[philo->id], "is eating");
// 	ft_wait(data->time_to_eat);
// 	philo->last_meal = ft_what_time_is_it();
// 	if (data->someone_died)
// 		return ;
// }

// static void	ft_sleep_and_think(t_philo *philo)
// {
// 	t_data	*data;

// 	data = philo->data;
// 	if (data->someone_died)
// 		return ;
// 	ft_print_msg(philo[philo->id], "is sleeping");
// 	ft_wait(data->time_to_sleep);
// 	if (data->someone_died)
// 		return ;
// 	ft_print_msg(philo[philo->id], "is thinking");
// }

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->data->beginning = ft_what_time_is_it();
	philo->last_meal = philo->data->beginning;
	if (philo->id % 2 == 0)
		ft_wait(philo->data->time_to_eat);
	while (!philo->data->shared.someone_died && !ft_philo_is_full(philo[philo->id]))
	{
		// ft_take_forks(philo);
		if (philo->data->shared.someone_died)
			break ;
		// ft_eat(philo);
		// ft_drop_forks(philo);
		if (ft_philo_is_full(philo[philo->id]))
			break ;
		philo->meal_count++;
		// ft_sleep_and_think(philo);
	}
	return (NULL);
}
