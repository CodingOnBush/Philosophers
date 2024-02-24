/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 11:06:34 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_is_philo_alive(t_philo philo)
{
	long	current_time;
	long	diff;

	current_time = ft_what_time_is_it();
	if (current_time < 0)
		return (0);
	diff = current_time - philo.last_meal;
	if (diff >= philo.data->time_to_die)
		return (0);
	return (1);
}

int	ft_philo_is_full(t_philo philo)
{
	if (philo.data->meal_goal == -1)
		return (0);
	if (philo.meal_count >= philo.data->meal_goal)
		return (1);
	return (0);
}

int	ft_all_philos_are_full(t_philo *philos)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	i = 0;
	data = philos->data;
	while (i < data->philo_nb)
	{
		philo = &philos[i];
		if (ft_philo_is_full(philo[philo->id]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_philos_dead(t_philo *philos)
{
	t_data	*data;
	int		philo_nb;
	int		i;

	data = philos->data;
	philo_nb = data->philo_nb;
	i = 0;
	while (!ft_all_philos_are_full(philos))
	{
		if (!ft_is_philo_alive(philos[i]))
		{
			ft_print_msg(philos[i], "died");
			data->shared.someone_died = 1;
			// pthread_mutex_unlock(&data->pencil);
			// ft_unlock_and_destroy_forks(data);
			break ;
		}
		if (i == philo_nb - 1)
			i = 0;
		else
			i++;
		usleep(10);// 100
	}
	if (data->shared.someone_died == 1)
		printf("Someone died\n");
}
