#include "../inc/philo.h"

int	ft_wait(long time)
{
	struct timeval	tv;
	long			start;
	long			second_start;

	if (gettimeofday(&tv, NULL))
		return (-1);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (gettimeofday(&tv, NULL))
		return (-1);
	second_start = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start);
	while (second_start < time)
		usleep(time / 10);
	return(0);
}

long	ft_get_current_time(t_env env)
{
	struct timeval	time;
	long			now;

	gettimeofday(&time, NULL);
	now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now - env.start_time);
}
