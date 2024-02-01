/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:25:54 by momrane           #+#    #+#             */
/*   Updated: 2024/02/01 21:46:03 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (-1);
	if (ft_check_digit(av[1]) < 0 || ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
		return (-1);
	i = 2;
	while (i < 5)
	{
		if (ft_check_digit(av[i]) < 0 || ft_atoi(av[i]) <= 0)
			return (-1);
		i++;
	}
	if (ft_check_digit(av[5]) < 0)
		return (-1);
	return (0);
}
