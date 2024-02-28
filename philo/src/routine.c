/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 12:10:04 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static int	ft_take_pair_of_forks(t_philo *philo, pthread_mutex_t *forks)
// {
// 	int		me;
// 	int		neighbor;

// 	me = philo->id;
// 	neighbor = (philo->id + 1) % philo->data->philo_nb;
// 	while (forks[me].__align != 0)
// 		ft_wait(1);
// 	pthread_mutex_lock(&forks[me]);
// 	ft_print_msg(philo->data, me, "has taken a fork");
// 	while (forks[neighbor].__align != 0)
// 		ft_wait(1);
// 	pthread_mutex_lock(&forks[neighbor]);
// 	ft_print_msg(philo->data, neighbor, "has taken a fork");
// 	return (1);
// }

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
	// forks = data->shared.forks;
	philo->last_meal = ft_what_time_is_it();//data->beginning;
	// pthread_mutex_lock(&data->shared.pencil);
	// printf("what time is it in routine %d ? %ld\n", philo->id, ft_what_time_is_it());
	// pthread_mutex_unlock(&data->shared.pencil);
	// while (1)
	// {
	// 	if (!ft_check_looping(data))
	// 		break ;
	// 	if (!ft_take_pair_of_forks(philo, forks))
	// 		break ;
	// 	while (data->shared.update_looping.__align != 0)
	// 		ft_wait(1);
	// 	pthread_mutex_lock(&data->shared.update_looping);
	// 	philo->last_meal = ft_what_time_is_it() + data->time_to_eat;
	// 	pthread_mutex_unlock(&data->shared.update_looping);
	// 	ft_print_msg(data, philo->id, "is eating");
	// 	ft_wait(data->time_to_eat);
	// 	if (!ft_drop_pair_of_forks(philo, forks))
	// 		break ;
	// 	ft_print_msg(data, philo->id, "is sleeping");
	// 	ft_wait(data->time_to_sleep);
	// 	ft_print_msg(data, philo->id, "is thinking");
	// 	philo->meal_count++;
	// }
	philo->meal_count = data->philo_nb;
	return (NULL);
}
