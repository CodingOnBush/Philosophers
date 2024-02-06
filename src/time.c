#include "../inc/philo.h"

int	ft_wait(long time)
{
	struct timeval	tv;
	long			start;
	long			second_start;

	if (gettimeofday(&tv, NULL))
		return (-1);
	start = (tv.tv_sec * (long)1000) + (tv.tv_usec / 1000);
	if (gettimeofday(&tv, NULL))
		return (-1);
	second_start = ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000) - start);
	while (second_start < time)
		usleep(time / 10);
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
	/*
		NULL in gettimeofday because we don't need to specify a time zone.
		tv_sec : nb of seconds since 1st January 1970
		tv_usec : nb of microseconds since the last second
		(time.tv_sec * 1000) : convert seconds to milliseconds
		(time.tv_usec / 1000) : microseconds to milliseconds
	*/
}

int	ft_usleep(int time)
{
	long	start;
	long	diff;

	start = ft_what_time_is_it();
	if (start < 0)
		return (-1);
	diff = 0;
	while (diff < time)
	{
		diff = ft_what_time_is_it() - start;
		if (diff < 0)
			return (-1);
		usleep(time / 10);
	}
	return(0);
}

long	ft_get_current_time(long start_time)
{
	struct timeval	time;
	long			now;

	gettimeofday(&time, NULL);
	now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now - start_time);
}
