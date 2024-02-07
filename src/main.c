/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 08:28:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	printf("someone_died: %d\n", env.someone_died);
}

int	main(int ac, char **av)
{
	t_env env;

	if (ft_init_everything(&env, ac, av) < 0)
	{
		ft_free_everything(&env);
		printf("[Error : Initialization failed]\n");
		return (-1);
	}
	printf("Starting simulation\n");
	while (1)
	{
		if (env.someone_died == 1)
		{
			printf("Someone died\n");
			break ;
		}
		if (env.meal_goal != -1 && env.total_meals >= env.meal_goal)
		{
			printf("All meals eaten\n");
			break ;
		}
		ft_wait(1000);
	}
	printf("Simulation ended\n");
	ft_free_everything(&env);
	return (0);
}
