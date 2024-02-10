/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/10 11:50:22 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_init_philo(t_env *env, t_philo *philo, int id)
{
	philo->id = id;
	philo->alive = 1;
	philo->meal_count = 0;
	philo->last_meal = -1;
	philo->routine_start = 0;
	pthread_mutex_init(&philo->fork_mutex, NULL);
	philo->right = NULL;
	philo->left = NULL;
	philo->env = env;
	pthread_create(&(philo->thread), NULL, ft_philo_routine, (void *)philo);
}

static t_philo	*ft_free_philos(t_philo *philos, int i)
{
	t_philo	*tmp;

	while (i > 0)
	{
		tmp = philos->right;
		pthread_mutex_destroy(&philos->fork_mutex);
		free(philos);
		philos = tmp;
		i--;
	}
	return (NULL);
}


t_philo	*ft_create_philos(t_env *env)
{
	t_philo	*philos;
	t_philo	*prev;
	t_philo	*first;
	int		i;

	i = 0;
	prev = NULL;
	while (i < env->nb_philos)
	{
		philos = malloc(sizeof(t_philo));
		if (!philos)
			return (NULL);
		ft_init_philo(env, philos, i);
		if (i == 0)
			first = philos;
		philos->left = prev;
		if (i > 0)
			prev->right = philos;
		prev = philos;
		i++;
	}
	philos->right = first;
	first->left = philos;
	return (first);
}

// void	ft_print_philos(t_env env)
// {
// 	t_philo	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = env.philos;
// 	while (i < env.nb_philos)
// 	{
// 		printf("--[(%p){%d}(%p){%d}(%p)]--", tmp->left, tmp->id + 1, tmp, tmp->id + 1, tmp->right);
// 		tmp = tmp->right;
// 		i++;
// 	}
// 	printf("\n");
// }

