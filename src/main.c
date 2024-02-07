/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 14:51:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_env(t_env env)
{
	printf("typedef struct s_env\n");
	printf("someone_died: %d\n", env.someone_died);
	printf("nb_philos: %d\n", env.nb_philos);
	printf("time_to_die: %d\n", env.time_to_die);
	printf("time_to_eat: %d\n", env.time_to_eat);
	printf("time_to_sleep: %d\n", env.time_to_sleep);
	printf("meal_goal: %d\n", env.meal_goal);
	printf("total_meals: %d\n", env.total_meals);
	printf("meal_count: %d\n", env.meal_count);
	printf("start_time: %ld\n", env.start_time);
	printf("msg_mutex: %p\n", &env.msg_mutex);
	printf("flag_mutex: %p\n", &env.flag_mutex);
}

void	ft_print_philos(t_philo *philos)
{
	int	i;
	t_philo	*all;

	i = 0;
	all = philos;
	while (i < all->env->nb_philos)
	{
		printf("typedef struct s_philo\n");
		printf("thread: %lu\n", all->thread);
		printf("id: %d\n", all->id);
		printf("alive: %d\n", all->alive);
		printf("meal_count: %d\n", all->meal_count);
		printf("last_meal: %d\n", all->last_meal);
		printf("routine_start: %d\n", all->routine_start);
		printf("fork_mutex: %p\n", &all->fork_mutex);
		printf("right: %p\n", all->right);
		printf("left: %p\n", all->left);
		ft_print_env(*all->env);
		all = all->right;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_env 	env;

	if (ft_init_everything(&env, ac, av) < 0)
	{
		printf("[Error : Initialization failed]\n");
		return (-1);
	}
	philos = ft_create_philos(&env);
	if (!philos)
	{
		printf("[Error : Philos creation failed]\n");
		return (-1);
	}
	pthread_create(&env.boss, NULL, ft_boss_routine, philos);
	printf("Starting simulation\n");
	pthread_join(env.boss, NULL);
	// while (1)
	// {
	// 	if (env.someone_died == 1)
	// 	{
	// 		printf("Someone died\n");
	// 		break ;
	// 	}
	// 	if (env.total_meals == env.meal_goal)
	// 	{
	// 		printf("All meals have been eaten\n");
	// 		break ;
	// 	}
	// 	ft_wait(100);
	// }
	printf("Simulation ended\n");
	ft_free_everything(&env, philos);
	return (0);
}
