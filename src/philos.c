/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/05 18:24:31 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_init_philo(t_philo *philos, int id)
{
	philos->id = id;
	philos->status = 't';
	philos->last_meal = 0;
	philos->meal_count = 0;
	philos->routine_start = 0;
	philos->alive = 1;
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

void	ft_print_philos(t_env env)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = env.philos;
	while (i < env.nb_philos)
	{
		printf("--[(%p){%d}(%p){%d}(%p)]--", tmp->left, tmp->id + 1, tmp, tmp->id + 1, tmp->right);
		tmp = tmp->right;
		i++;
	}
	printf("\n");
}

t_philo	*ft_free_philos(t_philo *philos, int i)
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
