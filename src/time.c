/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:03 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 10:55:55 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_wait(long ms)
{
	long int	start_time;

	start_time = ft_what_time_is_it();
	while ((ft_what_time_is_it() - start_time) < ms)
		usleep(ms / 100);
}

long	ft_what_time_is_it(void)
{
	struct timeval	time;
	long			out;

	if (gettimeofday(&time, NULL) < 0)
		return (-1);
	out = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (out);
}

long	ft_get_current_time(long start_time)
{
	long			now;

	now = ft_what_time_is_it();
	if (now < 0)
		return (-1);
	return (now - start_time);
}
