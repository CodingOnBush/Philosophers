#include "../inc/philo.h"

void	*ft_philo_routine(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	printf("philo routine started for %d\n", env->selected_philo->id);
	ft_usleep(7000);
	printf("philo routine ended for %d\n", env->selected_philo->id);
	env->loop = 0;
	return (NULL);
}

int	ft_start_routines(t_env *env)
{
	t_philo	*philos;
	// t_save	save;
	int		i;

	i = 0;
	philos = env->philos;
	while (i < env->nb_philos)
	{
		if (philos->routine_start == 0)
		{
			// save.philos = philos;
			// save.current_philo = philos;
			// save.env = env;
			env->selected_philo = philos;
			if (pthread_create(&(philos->thread), NULL, ft_philo_routine, env) != 0)
				return (-1);
			philos->routine_start = 1;
			philos = philos->right->right;
		}
		else
			philos = philos->right;
		i++;
	}
	return (0);
}
