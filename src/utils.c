/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/13 10:38:23 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_still_alive(t_philo *philo)
{
	long	diff;
	long	current_time;

	current_time = ft_get_current_time(philo->data->start_time);
	diff = current_time - philo->last_meal;// diff contains the time since the last meal
	if (diff >= philo->data->time_to_die)// if the time since the last meal is greater than the time to die
		return (0);// return 0 to indicate that the philo is dead
	return (1);// return 1 to indicate that the philo is still alive
}

void	ft_check_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philos)
	{
		if (ft_still_alive(&philo[i]) == 0 && philo->last_meal != philo->data->start_time)
		{
			ft_print_msg(&philo[i], "died...");
			philo->data->someone_died = 1;
			return ;
		}
		i++;
	}
}
