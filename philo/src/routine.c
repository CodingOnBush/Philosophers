/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 20:06:37 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_philo_is_full(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->meal_goal == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_count_mutex);
	if (philo->meal_count == data->meal_goal)
	{
		pthread_mutex_lock(&data->loop_mutex);
		data->loop = -1;
		pthread_mutex_unlock(&data->loop_mutex);
		pthread_mutex_unlock(&philo->meal_count_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_count_mutex);
	return (0);
}

int	ft_stop_loop(t_data *data)
{
	int	loop;

	pthread_mutex_lock(&data->loop_mutex);
	loop = data->loop;
	pthread_mutex_unlock(&data->loop_mutex);
	if (loop >= 0)
		return (1);
	return (0);
}

static void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		ft_wait(philo->data->time_to_eat);
	while (1)
	{
		if (ft_check_death(philo) || ft_philo_is_full(philo))
			break ;
		if (!ft_grab_forks(philo))
			break ;
		ft_print_msg(philo, "is eating");
		ft_wait(philo->data->time_to_eat);
		ft_drop_forks(philo);
		if (ft_check_death(philo))
			break ;
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = ft_what_time_is_it();
		pthread_mutex_unlock(&philo->last_meal_mutex);
		if (philo->data->meal_goal != -1)
		{
			pthread_mutex_lock(&philo->last_meal_mutex);
			philo->meal_count++;
			pthread_mutex_unlock(&philo->last_meal_mutex);
		}
		ft_print_msg(philo, "is sleeping");
		ft_wait(philo->data->time_to_sleep);
		ft_print_msg(philo, "is thinking");
		ft_wait(1);
	}
	return (NULL);
}

void	ft_start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->beginning = ft_what_time_is_it();
	while (i < data->philo_nb)
	{
		data->philos[i].last_meal = data->beginning;
		if (pthread_create(&data->philos[i].thrd, NULL, ft_routine,
				&data->philos[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->philos[i].thrd, NULL))
			return ;
		i++;
	}
}
