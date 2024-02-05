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
	t_args	*args;
	int		i;

	i = 0;
	philos = env->philos;
	while (i < env->nb_philos)
	{
		args->philo = philos;
		args->env = env;
		if (pthread_create(&philos->tid, NULL, ft_philo_routine, args) != 0)
			return (-1);
		philos = philos->right->right;
		i++;
	}
	return (0);
}
