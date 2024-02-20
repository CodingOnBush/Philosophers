/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:41 by momrane           #+#    #+#             */
/*   Updated: 2024/02/20 21:08:13 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	ft_get_param(char *s)
{
	int	i;
	int	res;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (!ft_isdigit(s[i]) && (s[i] != '+'))
		return (-1);
	if (s[i] == '+')
		i++;
	res = 0;
	while (ft_isdigit(s[i]))
		res = (res * 10) + (s[i++] - '0');
	if (s[i] != '\0')
		return (-1);
	return (res);
}

static int	ft_get_args(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (-1);
	}
	data->nb_philos = ft_get_param(av[1]);
	if (data->nb_philos < 0 || data->nb_philos > 200)
		return (-1);
	data->time_to_die = ft_get_param(av[2]);
	if (data->time_to_die < 0)
		return (-1);
	data->time_to_eat = ft_get_param(av[3]);
	if (data->time_to_eat < 0)
		return (-1);
	data->time_to_sleep = ft_get_param(av[4]);
	if (data->time_to_sleep < 0)
		return (-1);
	data->meal_goal = -1;
	if (ac == 6)
	{
		data->meal_goal = ft_get_param(av[5]);
		if (data->meal_goal < 0)
			return (-1);
	}
	return (0);
}

static int	ft_init_vars(t_data *data)
{
	int	i;

	i = 0;
	data->meals_count = 0;
	data->meals_goal = data->nb_philos * data->meal_goal;
	data->start_time = ft_what_time_is_it();
	data->someone_died = -1;
	if (data->start_time < 0)
		return (-1);
	pthread_mutex_init(&data->log_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (-1);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	ft_init_data(t_data *data, int ac, char **av)
{
	if (ft_get_args(data, ac, av) < 0)
		return (-1);
	if (ft_init_vars(data) < 0)
		return (-1);
	return (0);
}
