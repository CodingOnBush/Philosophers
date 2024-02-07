/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 14:32:08 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_still_alive(t_philo *philo)
{
	long	diff;
	long	current_time;

	current_time = ft_get_current_time(philo->env->start_time);
	diff = current_time - philo->last_meal;// diff contains the time since the last meal
	if (diff >= philo->env->time_to_die)// if the time since the last meal is greater than the time to die
		return (0);// return 0 to indicate that the philo is dead
	return (1);// return 1 to indicate that the philo is still alive
}
