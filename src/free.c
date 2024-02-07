/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:34 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 13:54:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free_everything(t_env *env, t_philo *philos)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (i < env->nb_philos)
	{
		tmp = philos->right;
		pthread_mutex_destroy(&philos->fork_mutex);
		if (philos)
			free(philos);
		philos = tmp;
		i++;
	}
}
