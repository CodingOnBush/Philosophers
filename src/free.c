/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:34 by momrane           #+#    #+#             */
/*   Updated: 2024/02/10 16:31:42 by allblue          ###   ########.fr       */
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
		pthread_detach(philos->thread);
		if (philos != NULL)
			free(philos);
		philos = tmp;
		i++;
	}
}

// static void	ft_free_threads(t_data *data, t_philo2 *philos)
// {
// 	int		i;

// 	i = 0;
// 	while (i < data->nb_philos)
// 	{
// 		free(philos[i].thread);
// 		printf("COUCOU\n");
// 		i++;
// 	}
// }

// static void	ft_free_philosophers(t_data *data, t_philo2 *philos)
// {
// 	int		i;

// 	i = 0;
// 	while (i < data->nb_philos)
// 	{
// 		if (philos[i] != NULL)
// 			free(philos[i]);
// 		i++;
// 	}
// }

static void	ft_free_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	ft_free_everything2(t_data *data, t_philo2 *philos)
{
	// ft_free_threads(data, philos);
	// ft_free_philosophers(data, philos);
	(void)philos;
	pthread_mutex_destroy(&data->log_mutex);
	ft_free_forks(data);
}
