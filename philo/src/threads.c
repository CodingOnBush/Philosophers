/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:07:53 by momrane           #+#    #+#             */
/*   Updated: 2024/02/23 14:30:47 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_start_routines(t_philo *philos, t_data *data)
{
	void	*arg;
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		arg = (void *)&philos[i];
		if (pthread_create(&philos[i].thread, NULL, ft_routine, arg) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_join_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
