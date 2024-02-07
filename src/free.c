/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:34 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 08:33:21 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free_everything(t_env *env)
{
	t_philo	*philos;
	t_philo	*tmp;
	int		i;

	i = 0;
	philos = env->philos;
	tmp = NULL;
	while (i < env->nb_philos)
	{
		tmp = philos->right;
		pthread_mutex_destroy(&philos->fork_mutex);
		free(philos->thread);
		if (philos)
			free(philos);
		philos = tmp;
		i++;
	}
}
