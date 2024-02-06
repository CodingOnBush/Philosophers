#include "../inc/philo.h"

// static int	ft_free_prev_mutex(t_env *env, int i)
// {
// 	t_philo	*philos;

// 	philos = env->philos;
// 	while (i > 0)
// 	{
// 		pthread_mutex_destroy(&philos->fork_mutex);
// 		philos = philos->right;
// 		i--;
// 	}
// 	return (-1);
// }

// static int	ft_init_all_mutex(t_env *env)
// {
// 	t_philo	*philos;
// 	int		i;

// 	i = 0;
// 	philos = env->philos;
// 	while (i < env->nb_philos)
// 	{
// 		if (pthread_mutex_init(&philos->fork_mutex, NULL) != 0)
// 			return (ft_free_prev_mutex(env, i));
// 		philos = philos->right;
// 		i++;
// 	}
// 	return (0);
// }

// static int	ft_start_all_routines(t_env *env)
// {
// 	t_philo	*philos;
// 	int		i;

// 	i = 0;
// 	philos = env->philos;
// 	while (i < env->nb_philos)
// 	{
// 		if (philos->routine_start == 0)
// 		{
// 			if (pthread_create(&philos->tid, NULL, ft_philo_routine, philos) != 0)
// 				return (-1);
// 			philos = philos->right->right;
// 		}
// 		else
// 			philos = philos->right;
// 		i++;
// 	}
// 	return (0);
// }

// static void	ft_fill_philos(t_env *env)
// {
// 	t_philo	*philos;
// 	int		i;

// 	i = 0;
// 	philos = ft_create_philos(env->nb_philos);
// 	env->philos = philos;
// 	while (i < env->nb_philos)
// 	{
// 		philos->time_to_die = env->time_to_die;
// 		philos->time_to_eat = env->time_to_eat;
// 		philos->time_to_sleep = env->time_to_sleep;
// 		philos->start_time = env->start_time;
// 		philos->meal_goal = env->meal_goal;
// 		philos->env = env;
// 		philos = philos->right;
// 		i++;
// 	}
// }

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// static int	ft_issign(char c)
// {
// 	if (c == '+')
// 		return (1);
// 	if (c == '-')
// 		return (-1);
// 	return (0);
// }

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

// static int	ft_atoi(const char *str)
// {
// 	int	i;
// 	int	sign;
// 	int	res;

// 	i = 0;
// 	sign = 1;
// 	res = 0;
// 	while (str[i] && ft_isspace(str[i]))
// 		i++;
// 	if (ft_issign(str[i]))
// 	{
// 		if (str[i] == '-')
// 			sign = sign * (-1);
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9' && str[i])
// 		res = (res * 10) + (str[i++] - 48);
// 	return (sign * res);
// }

// static int	ft_check_digit(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!(str[i] >= '0' && str[i] <= '9'))
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

// static int	ft_check_args(int ac, char **av)
// {
// 	int	i;

// 	if (ac < 5 || ac > 6)
// 		return (-1);
// 	if (ft_check_digit(av[1]) < 0 || ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
// 		return (-1);
// 	i = 2;
// 	while (i < 5)
// 	{
// 		if (ft_check_digit(av[i]) < 0 || ft_atoi(av[i]) <= 0)
// 			return (-1);
// 		i++;
// 	}
// 	if (ft_check_digit(av[5]) < 0)
// 		return (-1);
// 	return (0);
// }

// static int	ft_init_env(t_env *env, int ac, char **av)
// {
// 	struct timeval	time;

// 	env->nb_philos = ft_atoi(av[1]);
// 	env->time_to_die = ft_atoi(av[2]);
// 	env->time_to_eat = ft_atoi(av[3]);
// 	env->time_to_sleep = ft_atoi(av[4]);
// 	env->loop = 0;
// 	env->meal_count = 0;
// 	if (ac == 6)
// 		env->meal_goal = ft_atoi(av[5]);
// 	else
// 		env->meal_goal = -1;
// 	printf("after\n");
// 	env->philos = ft_create_philos(env->nb_philos);
// 	if (!env->philos)
// 		return (-1);
// 	gettimeofday(&time, NULL);
// 	env->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
// 	return (0);
// }

// static int	ft_init_env(t_env *env, int ac, char **av)
// {
// 	struct timeval	time;

// 	env->nb_philos = ft_atoi(av[1]);
// 	env->time_to_die = ft_atoi(av[2]);
// 	env->time_to_eat = ft_atoi(av[3]);
// 	env->time_to_sleep = ft_atoi(av[4]);
// 	env->loop = 0;
// 	env->meal_count = 0;
// 	if (ac == 6)
// 		env->meal_goal = ft_atoi(av[5]);
// 	else
// 		env->meal_goal = -1;
// 	env->philos = ft_create_philos(env->nb_philos);
// 	if (!env->philos)
// 		return (-1);
// 	gettimeofday(&time, NULL);
// 	env->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
// 	return (0);
// }

int	ft_get_param(char *s)
{
	int	i;
	int	res;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (!ft_isdigit(s[i]) && (s[i] != '+'))
		return (-1);
	if (s[i] == '+')
		i++;
	res = 0;
	while (ft_isdigit(s[i]))
		res = (res * 10) + (s[i++] - '0');
	if (s[i] != '\0')
		return (-1);
	return (res);
}

int	ft_get_args(t_env *env, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (-1);
	env->nb_philos = ft_get_param(av[1]);
	if (env->nb_philos < 0 || env->nb_philos > 200)
		return (-1);
	env->time_to_die = ft_get_param(av[2]);
	if (env->time_to_die < 0)
		return (-1);
	env->time_to_eat = ft_get_param(av[3]);
	if (env->time_to_eat < 0)
		return (-1);
	env->time_to_sleep = ft_get_param(av[4]);
	if (env->time_to_sleep < 0)
		return (-1);
	env->meal_goal = -1;
	if (ac == 6)
	{
		env->meal_goal = ft_get_param(av[5]);
		if (env->meal_goal < 0)
			return (-1);
	}
	return (0);
}

int	ft_init_vars(t_env *env)
{
	env->loop = 1;
	env->total_meals = 0;
	env->meal_count = 0;
	env->start_time = ft_what_time_is_it();
	if (env->start_time < 0)
		return (-1);
	env->philos = ft_create_philos(env->nb_philos);
	if (!env->philos)
		return (-1);
	env->selected_philo = env->philos;
	return (0);
}

int	ft_init_all_mutex(t_env *env)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = env->philos;
	while (i < env->nb_philos)
	{
		if (pthread_mutex_init(&(philos->fork_mutex), NULL) != 0)
			return (-1);
		philos = philos->right;
		i++;
	}
	return (0);
}

int	ft_init_everything(t_env *env, int ac, char **av)
{
	if (ft_get_args(env, ac, av) < 0)
		return (-1);
	if (ft_init_vars(env) < 0)
		return (-1);
	if (ft_init_all_mutex(env) < 0)
		return (-1);
	return (0);
}
