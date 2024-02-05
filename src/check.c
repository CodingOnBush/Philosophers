#include "../inc/philo.h"

static int	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (ft_issign(str[i]))
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		res = (res * 10) + (str[i++] - 48);
	return (sign * res);
}

static int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (-1);
	if (ft_check_digit(av[1]) < 0 || ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
		return (-1);
	i = 2;
	while (i < 5)
	{
		if (ft_check_digit(av[i]) < 0 || ft_atoi(av[i]) <= 0)
			return (-1);
		i++;
	}
	if (ft_check_digit(av[5]) < 0)
		return (-1);
	return (0);
}

int	ft_init_env(t_env *env, int ac, char **av)
{
	struct timeval	time;

	env->nb_philos = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	env->end_flag = 0;
	env->meal_count = 0;
	if (ac == 6)
		env->meal_goal = ft_atoi(av[5]);
	else
		env->meal_goal = -1;
	env->philos = ft_create_philos(env->nb_philos);
	if (!env->philos)
		return (-1);
	gettimeofday(&time, NULL);
	env->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (0);
}
