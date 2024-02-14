/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/14 08:23:34 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// int	ft_still_alive(t_philo *philo)
// {
// 	long	diff;
// 	long	current_time;

// 	current_time = ft_get_current_time(philo->data->start_time);
// 	diff = current_time - philo->last_meal;// diff contains the time since the last meal
// 	if (diff >= philo->data->time_to_die)// if the time since the last meal is greater than the time to die
// 		return (0);// return 0 to indicate that the philo is dead
// 	return (1);// return 1 to indicate that the philo is still alive
// }

int	ft_still_alive(t_philo *philo)
{
	long	diff;
	long	current_time;

	current_time = ft_get_current_time(philo->data->start_time);
	diff = current_time - philo->last_meal;
	if (diff >= philo->data->time_to_die)
		return (0);
	return (1);
}

void	ft_check_philos(t_philo *philos)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	i = 0;
	data = philos->data;
	while (i < data->nb_philos)
	{
		philo = &philos[i];
		if (ft_still_alive(philo) == 0)
		{
			ft_print_msg(philo, "died");
			data->someone_died = philo->id;
			return ;
		}
		
		i++;
	}
}
