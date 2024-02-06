#include "../inc/philo.h"

void	ft_free_everything(t_env *env)
{
	t_philo	*philos;
	t_philo	*tmp;
	int		i;

	i = 0;
	philos = env->philos;
	while (i < env->nb_philos)
	{
		tmp = philos->right;
		pthread_mutex_destroy(&philos->fork_mutex);
		if (philos)
			free(philos);
		philos = tmp;
		i++;
	}
}
