/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/14 08:07:03 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_start_threads(t_philo *philos)
{
	pthread_t	thread;
	void		*arg;
	int			i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		thread = philos[i].thread;
		arg = (void *)&philos[i];
		if (pthread_create(&thread, NULL, ft_philo_routine, arg) < 0)
			return (-1);
		if (pthread_detach(thread) < 0)
			return (-1);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (ft_init_data(&data, ac, av) < 0)
		return (-1);
	philos = ft_create_philos(&data);
	if (!philos)
	{
		free(data.forks);
		return (-1);
	}
	if (ft_start_threads(philos) > 0)
	{
		while (data.routine_count != data.nb_philos)
		{
			ft_check_philos(philos);
			ft_wait(10);
		}
		ft_wait(100);
	}
	free(philos);
	free(data.forks);
	return (0);
}
