/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:41 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 12:33:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_init_data(t_data *data, int ac, char **av)
{
	int	i;

	if (!ft_init_vars_with_args(data, ac, av))
		return (0);
	if (!ft_init_vars(data))
		return (0);
	if (pthread_mutex_init(&data->pencil, NULL))
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

t_philo	*ft_create_philos(t_data *data)
{
	t_philo	*philos;
	int	i;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].thread = i;
		philos[i].id = i;
		philos[i].meal_count = 0;
		philos[i].last_meal = data->start_time;
		philos[i].data = data;
		i++;
	}
	return (philos);
}
