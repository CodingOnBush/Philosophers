/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:43:01 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 11:43:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_philo	*ft_create_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		philos[i].id = i;
		philos[i].meal_count = 0;
		philos[i].last_meal = -1;
		philos[i].alive = 1;
		philos[i].data = data;
		i++;
	}
	return (philos);
}

static int	ft_init_shared(t_data *data)
{
	data->shared.someone_died = 0;
	data->shared.philo_full = 0;
	data->shared.forks = ft_create_forks(data->philo_nb);
	if (!data->shared.forks)
		return (0);
	if (pthread_mutex_init(&data->shared.pencil, NULL))
		return (free(data->shared.forks), 0);
	if (pthread_mutex_init(&data->shared.update_flags, NULL))
		return (free(data->shared.forks), 0);
	return (1);
}

static int	ft_init_data(t_data *data, int ac, char **av)
{
	if (!ft_get_arguments(data, ac, av))
		return (0);
	data->beginning = -1;
	data->philos = ft_create_philos(data);
	if (!data->philos)
		return (0);
	if (!ft_init_shared(data))
		return (free(data->philos), 0);
	return (1);
}

t_data	*ft_create_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (!ft_init_data(data, ac, av))
		return (free(data), NULL);
	return (data);
}
