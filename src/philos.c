/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 08:39:49 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_init_philo(t_philo *philos, int id)
{
	philos->thread = malloc(sizeof(pthread_t));
	philos->id = id;
	philos->alive = 1;
	philos->meal_count = 0;
	philos->last_meal = -1;
	philos->routine_start = 0;
	philos->right = NULL;
	philos->left = NULL;
	pthread_mutex_init(&philos->fork_mutex, NULL);
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


t_philo	*ft_create_philos(int nb)
{
	t_philo	*philos;
	t_philo	*prev;
	t_philo	*first;
	int		i;

	i = 0;
	prev = NULL;
	while (i < nb)
	{
		philos = malloc(sizeof(t_philo));
		if (!philos)
			return (ft_free_philos(philos, i));
		ft_init_philo(philos, i);
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

