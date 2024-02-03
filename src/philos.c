/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 16:16:47 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*ft_free_philos(t_philo *philos, int i)
{
	t_philo	*tmp;

	while (i > 0)
	{
		tmp = philos->right;
		pthread_mutex_destroy(&philos->mutex);
		free(philos);
		philos = tmp;
		i--;
	}
	return (NULL);
}

static void	ft_init_philo(t_philo *philos, int id)
{
	philos->id = id;
	philos->status = 't';
	philos->last_meal = 0;
	philos->eat_count = 0;
	philos->dead_time = 1000;
	philos->alive = 1;
	philos->fork_right = 1;
	philos->fork_left = 0;
	pthread_mutex_init(&philos->mutex, NULL);
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
		// printf("Philo %d created\n", i + 1);
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
	while (i < env.nb)
	{
		printf("--[(%p){%d}(%p){%d}(%p)]--", tmp->left, tmp->id + 1, tmp, tmp->id + 1, tmp->right);
		tmp = tmp->right;
		i++;
	}
	printf("\n");
}

/* --[(0x16cd740){1}(0x16cd2a0){1}(0x16cd6e0)]----[(0x16cd2a0){2}(0x16cd6e0){2}(0x16cd710)]----[(0x16cd6e0){3}(0x16cd710){3}(0x16cd740)]----[(0x16cd710){4}(0x16cd740){4}(0x16cd2a0)]-- */
/* --[(0x17c7770){1}(0x17c72a0){1}(0x17c76e0)]----[(0x17c72a0){2}(0x17c76e0){2}(0x17c7710)]----[(0x17c76e0){3}(0x17c7710){3}(0x17c7740)]----[(0x17c7710){4}(0x17c7740){4}(0x17c7770)]----[(0x17c7740){5}(0x17c7770){5}(0x17c72a0)]-- */