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

u_int64_t	get_time(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
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
