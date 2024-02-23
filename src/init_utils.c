/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:04:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 07:58:20 by momrane          ###   ########.fr       */
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

int	ft_init_vars_with_args(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("❌: ./philo nb_philos die_time eat_time sleep_time [meals]\n");
		return (0);
	}
	data->nb_philos = ft_get_param(av[1]);
	if (data->nb_philos < 0 || data->nb_philos > 200)
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

int	ft_init_vars(t_data *data)
{
	data->someone_died = -1;
	data->start_time = ft_what_time_is_it();
	if (data->start_time < 0)
		return (0);
	return (1);
}
