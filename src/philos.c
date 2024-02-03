/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 09:40:14 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_philo	*ft_free_philos(t_philo *philos, int i)
{
	t_philo	*tmp;
	t_philo	*tmp2;

	tmp2 = philos;
	while (i >= 0)
	{
		tmp = tmp2->left;
		free(tmp2);
		tmp2 = tmp;
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
	philos->dead = 0;
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
		printf("Philo %d created\n", i + 1);
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

void	ft_print_philo(t_env *env)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = env->philos;
	while (i < env->nb)
	{
		printf("--[(%p){%d}(%p){%d}(%p)]--", tmp->left, tmp->id + 1, tmp, tmp->id + 1, tmp->right);
		tmp = tmp->right;
		i++;
	}
	printf("\n");
}

/* --[(0x16cd740){1}(0x16cd2a0){1}(0x16cd6e0)]----[(0x16cd2a0){2}(0x16cd6e0){2}(0x16cd710)]----[(0x16cd6e0){3}(0x16cd710){3}(0x16cd740)]----[(0x16cd710){4}(0x16cd740){4}(0x16cd2a0)]-- */