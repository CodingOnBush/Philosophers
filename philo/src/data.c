/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:43:01 by momrane           #+#    #+#             */
/*   Updated: 2024/02/29 19:33:56 by momrane          ###   ########.fr       */
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
	memset(philos, 0, sizeof(t_philo) * data->philo_nb);
	i = 0;
	while (i < data->philo_nb)
	{
		philos[i].thrd = 0;
		philos[i].id = i;
		philos[i].meal_count = 0;
		if (pthread_mutex_init(&(philos[i].last_meal_mutex), NULL))
			return (NULL);
		if (pthread_mutex_init(&(philos[i].meal_count_mutex), NULL))
			return (NULL);
		philos[i].last_meal = 0;
		philos[i].data = data;
		i++;
	}
	return (philos);
}

static int	ft_init_data(t_data *data, int ac, char **av)
{
	if (!ft_get_arguments(data, ac, av))
	{
		printf("err_ philo_nb die eat sleep [meal]\n");
		return (0);
	}
	data->beginning = 0;
	data->loop = -42;
	data->philos = ft_create_philos(data);
	if (!data->philos)
		return (0);
	data->forks = ft_create_forks(data->philo_nb);
	if (!data->forks)
		return (free(data->philos), 0);
	if (pthread_mutex_init(&data->loop_mutex, NULL))
		return (free(data->philos), free(data->forks), 0);
	if (pthread_mutex_init(&data->pencil, NULL))
		return (free(data->philos), free(data->forks), 0);
	return (1);
}

t_data	*ft_create_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	if (!ft_init_data(data, ac, av))
		return (free(data), NULL);
	return (data);
}
