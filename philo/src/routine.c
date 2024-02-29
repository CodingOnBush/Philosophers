/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/29 19:47:04 by momrane          ###   ########.fr       */
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

static void	*ft_routine(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_wait(1);
	while (1)
	{
		if (ft_check_death(philo) || ft_philo_is_full(philo))
			break ;
		if (!ft_grab_forks(philo))
			break ;
		time = ft_what_time_is_it();
		ft_print_msg(philo, "is eating");
		ft_wait(philo->data->time_to_eat);
		if (philo->data->philo_nb != 1)
			ft_drop_forks(philo);
		if (ft_check_death(philo))
		{
			// printf("COUCOU\n");
			break;
		}
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = time + philo->data->time_to_eat;
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
		data->philos[i].last_meal = ft_what_time_is_it();
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
