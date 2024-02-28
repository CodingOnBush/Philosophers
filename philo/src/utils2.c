/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:28:51 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 16:29:21 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_nb)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->pencil);
	if (data->philos)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
			pthread_mutex_destroy(&data->philos[i].meal_count_mutex);
			i++;
		}
		free(data->philos);
	}
	if (data)
		free(data);
}

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

int	ft_get_arguments(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Syntax error : ./philo philo_nb die eat sleep [meal]\n");
		return (0);
	}
	data->philo_nb = ft_get_param(av[1]);
	if (data->philo_nb < 0)
		return (0);
	data->time_to_die = ft_get_param(av[2]);
	if (data->time_to_die < 0)
		return (0);
	data->time_to_eat = ft_get_param(av[3]);
	if (data->time_to_eat < 0)
		return (0);
	data->time_to_sleep = ft_get_param(av[4]);
	if (data->time_to_sleep < 0)
		return (0);
	data->meal_goal = -1;
	if (ac == 6)
	{
		data->meal_goal = ft_get_param(av[5]);
		if (data->meal_goal < 0)
			return (0);
	}
	return (1);
}
