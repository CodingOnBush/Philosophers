/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/13 10:39:58 by allblue          ###   ########.fr       */
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
	t_philo	*philos;
	t_data		*data;

	philos = (t_philo *)arg;
	data = philos->data;
	ft_print_msg(philos, "start routine");
	if (philos->id % 2 != 0)
		ft_wait(data->time_to_eat * 10);
	while (1)
	{
		if (data->someone_died != -1 || philos->meal_count == data->meal_goal)
			break ;
		pthread_mutex_lock(&data->forks[philos->id]);
		pthread_mutex_lock(&data->forks[(philos->id + 1) % data->nb_philos]);
		ft_print_msg(philos, "has taken a fork");

		ft_eat(philos);

		pthread_mutex_unlock(&data->forks[philos->id]);
		pthread_mutex_unlock(&data->forks[(philos->id + 1) % data->nb_philos]);

		ft_sleep(philos);

		ft_think(philos);
		
		ft_wait(10);
	}
	ft_print_msg(philos, "end routine");
	pthread_exit(NULL);
	return (NULL);
}
