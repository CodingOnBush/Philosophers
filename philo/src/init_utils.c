/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:30:06 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 13:15:00 by momrane          ###   ########.fr       */
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

int	ft_parse_args(int ac, char **av, t_infos *infos)
{
	if (ac < 5 || ac > 6)
		return (FAIL);
	infos->nb_of_philo = ft_get_param(av[1]);
	if (infos->nb_of_philo < 0)
		return (FAIL);
	infos->time_to_die = ft_get_param(av[2]);
	if (infos->time_to_die < 0)
		return (FAIL);
	infos->time_to_eat = ft_get_param(av[3]);
	if (infos->time_to_eat < 0)
		return (FAIL);
	infos->time_to_sleep = ft_get_param(av[4]);
	if (infos->time_to_sleep < 0)
		return (FAIL);
	infos->meal_goal = NO_MEAL_GOAL;
	if (ac == 6)
	{
		infos->meal_goal = ft_get_param(av[5]);
		if (infos->meal_goal < 0)
			return (FAIL);
	}
	return (SUCCESS);
}
