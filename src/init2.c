/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:41 by momrane           #+#    #+#             */
/*   Updated: 2024/02/10 12:00:44 by allblue          ###   ########.fr       */
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

static int	ft_get_args(t_env *env, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (-1);
	env->nb_philos = ft_get_param(av[1]);
	if (env->nb_philos < 0 || env->nb_philos > 200)
		return (-1);
	env->time_to_die = ft_get_param(av[2]);
	if (env->time_to_die < 0)
		return (-1);
	env->time_to_eat = ft_get_param(av[3]);
	if (env->time_to_eat < 0)
		return (-1);
	env->time_to_sleep = ft_get_param(av[4]);
	if (env->time_to_sleep < 0)
		return (-1);
	env->meal_goal = -1;
	if (ac == 6)
	{
		env->meal_goal = ft_get_param(av[5]);
		if (env->meal_goal < 0)
			return (-1);
	}
	return (0);
}

static int	ft_init_vars(t_env *env)
{
	pthread_mutex_init(&env->msg_mutex, NULL);
	env->total_meals = 0;
	env->meal_count = 0;
	env->start_time = ft_what_time_is_it();
	if (env->start_time < 0)
		return (-1);
	return (0);
}

int	ft_init_everything2(t_data *data, t_philo2 *philos, int ac, char **av)
{
	if (ft_get_args(env, ac, av) < 0)
		return (-1);
	if (ft_init_vars(env) < 0)
		return (-1);
	return (0);
}
