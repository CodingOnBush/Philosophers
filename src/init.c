#include "../inc/philo.h"

static int	ft_free_prev_mutex(t_env *env, int i)
{
	t_philo	*philos;

	philos = env->philos;
	while (i > 0)
	{
		pthread_mutex_destroy(&philos->fork_mutex);
		philos = philos->right;
		i--;
	}
	return (-1);
}

int	ft_init_all_mutex(t_env *env)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = env->philos;
	while (i < env->nb_philos)
	{
		if (pthread_mutex_init(&philos->fork_mutex, NULL) != 0)
			return (ft_free_prev_mutex(env, i));
		philos = philos->right;
		i++;
	}
	return (0);
}

int	ft_start_all_routines(t_env *env)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = env->philos;
	while (i < env->nb_philos)
	{
		if (philos->routine_start == 0)
		{
			if (pthread_create(&philos->tid, NULL, ft_philo_routine, philos) != 0)
				return (-1);
			philos = philos->right->right;
		}
		else
			philos = philos->right;
		i++;
	}
	return (0);
}

void	ft_fill_philos(t_env *env)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = ft_create_philos(env->nb_philos);
	env->philos = philos;
	while (i < env->nb_philos)
	{
		philos->time_to_die = env->time_to_die;
		philos->time_to_eat = env->time_to_eat;
		philos->time_to_sleep = env->time_to_sleep;
		philos->start_time = env->start_time;
		philos->meal_goal = env->meal_goal;
		philos->env = env;
		philos = philos->right;
		i++;
	}
}
