/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/06 15:14:11 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_error(t_env *env, char *str)
{
	ft_free_everything(env);
	printf("[Error : %s]\n", str);
	return (-1);
}

void	ft_print_env(t_env env)
{
	int		i;
	t_philo	*philos;

	i = 0;
	printf("ENV INITIALIZED\n");
	printf("nb_philos: %d\n", env.nb_philos);
	printf("time_to_die: %d\n", env.time_to_die);
	printf("time_to_eat: %d\n", env.time_to_eat);
	printf("time_to_sleep: %d\n", env.time_to_sleep);
	printf("total_meals: %d\n", env.total_meals);
	printf("meal_count: %d\n", env.meal_count);
	printf("meal_goal: %d\n", env.meal_goal);
	printf("start_time: %ld\n", env.start_time);
	philos = env.philos;
	while (i < env.nb_philos)
	{
		printf("[%p]{%d}%p{%d}[%p]--", philos->left, philos->id, philos, philos->id, philos->right);
		philos = philos->right;
		i++;
	}
	printf("\n");
	printf("loop: %d\n", env.loop);
}

int	main(int ac, char **av)
{
	t_env env;

	if (ft_init_everything(&env, ac, av) < 0)
		return (ft_error(&env, "Initialization failed"));
	ft_print_env(env);
	if (ft_start_routines(&env) < 0)
		return (ft_error(&env, "Routines failed"));
	while (env.loop == 1)
	{
		printf("Meals: %d\n", env.meal_count);
		ft_usleep(1000);
	}
	
	// t_env	env;

	// if (ft_check_args(ac, av) < 0)
	// 	return (0);
	// if (ft_init_env(&env, ac, av) < 0)
	// 	return (0);
	// ft_fill_philos(&env);
	// if (ft_init_all_mutex(&env) < 0)
	// 	return (0);
	// if (ft_start_all_routines(&env) < 0)
	// 	return (0);
	// while (1)
	// {
	// 	printf("Meals: %d\n", env.meal_count);
	// 	if (env.mea > 0 && env.meal_count >= env.meal_goal)
	// 		break ;
	// 	if (env.loop == 1)
	// 		break ;
	// 	ft_usleep(1000);
	// }
	// ft_free_philos(env.philos, env.nb_philos);
	return (0);
}



// void	*function(void *arg)
// {
// 	int		*count;
// 	int		i;

// 	i = 0;
// 	count = (int *)arg;
// 	while (i < 1000000)
// 	{
// 		*count += 1;
// 		i++;
// 	}
// 	return (NULL);
// }

// int	main(void)
// {
// 	pthread_t	tid1;
// 	pthread_t	tid2;
// 	int			cont;

// 	cont = 0;
// 	pthread_create(&tid1, NULL, function, &cont);
// 	pthread_create(&tid2, NULL, function, &cont);
// 	pthread_join(tid1, NULL);
// 	pthread_join(tid2, NULL);
// 	printf("cont: %d\n", cont);
// 	return (0);
// }