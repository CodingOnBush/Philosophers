/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:41 by momrane           #+#    #+#             */
/*   Updated: 2024/02/22 17:57:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_init_data(t_data *data, int ac, char **av)
{
	int	i;

	if (!ft_init_vars_with_args(data, ac, av))
		return (0);
	if (!ft_init_vars(data))
		return (0);
	if (pthread_mutex_init(&data->pencil, NULL))
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

static void	ft_init_philos(t_philo *philos, t_data *data)
{
	int	i;

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
}

int	ft_init_data_and_philos(t_data *data, t_philo *philos, int ac, char **av)
{
	if (!ft_init_data(data, ac, av))
		return (0);
	ft_init_philos(philos, data);
	return (1);
}
