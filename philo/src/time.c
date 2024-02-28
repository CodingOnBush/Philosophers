/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:03 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 14:50:39 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_wait(long ms)
{
	long int	start_time;

	start_time = 0;
	start_time = ft_what_time_is_it();
	while ((ft_what_time_is_it() - start_time) < ms)
		usleep(ms / 10);
		
	// long	start;
	// long	now;

	// start = ft_what_time_is_it();
	// if (start < 0)
	// 	return ;
	// while (1)
	// {
	// 	now = ft_what_time_is_it();
	// 	if (now < 0)
	// 		return ;
	// 	if (now - start >= ms)
	// 		break ;
	// 	usleep(ms / 10);
	// }
	
	// usleep(ms * 1000);
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

long	ft_get_ms_since(long start_time)
{
	long			now;

	now = ft_what_time_is_it();
	if (now < 0)
		return (-1);
	if (now - start_time < 3)
		return (0);
	return (now - start_time);
}
