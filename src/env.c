/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:21:44 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 18:55:55 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_init_env(t_env *env, char **av)
{
	env->end = 0;
	env->nb = ft_atoi(av[1]);
	env->die = ft_atoi(av[2]);
	env->eat = ft_atoi(av[3]);
	env->sleep = ft_atoi(av[4]);
	env->forks = env->nb;
	env->philos = ft_create_philos(env->nb);
	if (!env->philos)
		return (-1);
	env->time_start = 0;
	return (0);
}
