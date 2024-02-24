/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 17:44:13 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_take_pair_of_forks(t_philo *philo, pthread_mutex_t *forks)
{
	int		me;
	int		neighbor;

	me = philo->id;
	neighbor = (philo->id + 1) % philo->data->philo_nb;
	pthread_mutex_lock(&forks[me]);
	ft_print_msg(philo->data, me, "has taken a fork");
	pthread_mutex_lock(&forks[neighbor]);
	ft_print_msg(philo->data, neighbor, "has taken a fork");
	return (1);
}

static int	ft_drop_pair_of_forks(t_philo *philo, pthread_mutex_t *forks)
{
	t_data	*data;
	int		me;
	int		neighbor;

	data = philo->data;
	me = philo->id;
	neighbor = (philo->id + 1) % data->philo_nb;
	if (pthread_mutex_unlock(&forks[me]))
		return (0);
	if (pthread_mutex_unlock(&forks[neighbor]))
		return (0);
	return (1);
}

void	*ft_routine(void *arg)
{
	pthread_mutex_t	*forks;
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = philo->data;
	forks = data->shared.forks;
	if (philo->id % 2)
		ft_wait(data->time_to_eat);
	while (1)
	{
		if (pthread_mutex_lock(&data->shared.update_looping))
			break ;
		if (!data->shared.looping)
		{
			pthread_mutex_unlock(&data->shared.update_looping);
			break ;
		}
		pthread_mutex_unlock(&data->shared.update_looping);
		
		if (!ft_take_pair_of_forks(philo, forks))
			break ;

		ft_print_msg(data, philo->id, "is eating");
		ft_wait(data->time_to_eat);
		if (!ft_drop_pair_of_forks(philo, forks))
			break ;
		philo->last_meal = ft_what_time_is_it();
		philo->meal_count++;
		ft_print_msg(data, philo->id, "is sleeping");
		ft_wait(data->time_to_sleep);
		ft_print_msg(data, philo->id, "is thinking");
	}
	
	return (NULL);
}
