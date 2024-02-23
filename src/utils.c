/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 10:15:57 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_is_philo_alive(t_philo *philo)
{
	long long int	current_time;
	long long int	diff;

	current_time = ft_what_time_is_it();
	diff = current_time - philo->last_meal;
	if (diff >= philo->data->time_to_die)
		return (0);
	return (1);
}

int	ft_philo_is_full(t_philo *philo)
{
	if (philo->data->meal_goal == -1)
		return (0);
	if (philo->meal_count >= philo->data->meal_goal)
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
	while (i < data->nb_philos)
	{
		philo = &philos[i];
		if (ft_philo_is_full(philo) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_philos_dead(t_philo *philos)
{
	t_data	*data;
	int		nb_philos;
	int		i;

	data = philos->data;
	nb_philos = data->nb_philos;
	i = 0;
	while (data->someone_died == -1 && !ft_all_philos_are_full(philos))
	{
		if (!ft_is_philo_alive(&philos[i]))
		{
			ft_print_msg(&philos[i], "died");
			data->someone_died = i;
			break ;
		}
		if (i == nb_philos - 1)
			i = 0;
		else
			i++;
	}
	pthread_mutex_unlock(&data->pencil);
	ft_unlock_and_destroy_forks(data);
}
