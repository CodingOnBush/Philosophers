/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:03 by momrane           #+#    #+#             */
/*   Updated: 2024/02/10 10:19:29 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_wait(long ms)
{
	long	start;
	long	diff;

	start = ft_what_time_is_it();
	if (start < 0)
		return (-1);
	diff = 0;
	while (diff < ms)
	{
		diff = ft_what_time_is_it() - start;
		if (diff < 0)
			return (-1);
		usleep(ms / 10);
	}
	return(0);
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

/*
	NULL in gettimeofday because we don't need/want to specify a time zone.
	tv_sec : nb of seconds since 1st January 1970
	tv_usec : nb of microseconds since the last second
	(time.tv_sec * 1000) : convert seconds to milliseconds
	(time.tv_usec / 1000) : microseconds to milliseconds
*/

long	ft_get_current_time(long start_time)
{
	long			now;

	now = ft_what_time_is_it();
	if (now < 0)
		return (-1);
	return (now - start_time);
}
