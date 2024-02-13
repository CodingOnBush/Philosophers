/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/13 16:03:09 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_think(t_philo *philo)
{
	ft_print_msg(philo, "is thinking");
}

static void	ft_eat(t_philo *philo)
{
	ft_print_msg(philo, "is eating");
	ft_wait(philo->data->time_to_eat);
	philo->last_meal = ft_get_current_time(philo->data->start_time);
	philo->meal_count++;
}

static void	ft_sleep(t_philo *philo)
{
	ft_print_msg(philo, "is sleeping");
	ft_wait(philo->data->time_to_sleep);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	ft_print_msg(philo, "start routine");
	if (philo->id % 2 != 0)
		ft_wait(data->time_to_eat * 10);
	philo->routine_flag = 1;
	while (philo->routine_flag == 1)
	{	
		pthread_mutex_lock(&data->forks[philo->id]);
		pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nb_philos]);
		ft_print_msg(philo, "has taken a fork");

		ft_eat(philo);

		pthread_mutex_unlock(&data->forks[philo->id]);
		pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->nb_philos]);

		ft_sleep(philo);

		ft_think(philo);
		
		ft_wait(10);
	}
	ft_print_msg(philo, "end routine");
	pthread_exit(NULL);
	return (NULL);
}
