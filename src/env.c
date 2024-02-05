/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:21:44 by momrane           #+#    #+#             */
/*   Updated: 2024/02/05 16:55:46 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
