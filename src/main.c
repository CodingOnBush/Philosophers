/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/20 13:55:12 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_run_routines(t_philo *philos)
{
	pthread_t	thread;
	void		*arg;
	int			i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		thread = philos[i].thread;
		arg = (void *)&philos[i];
		pthread_create(&thread, NULL, ft_philo_routine, arg);
		pthread_detach(thread);
		i++;
	}
}

static int	ft_check(t_philo *philos)
{
	t_data	*data;
	int		i;

	i = 0;
	data = philos->data;
	while (i < data->nb_philos)
	{
		if (philos[i].last_meal + data->time_to_die < ft_get_current_time(data->start_time))
		{
			data->routine_flag = 0;
			ft_print_msg(&philos[i], "died");
			return (-1);
		}
		else if (data->meals_count == data->meals_goal)
		{
			data->routine_flag = 0;
			return (-1);
		}
		i++;
	}
	return (1);
}

static void	ft_free_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_unlock(&data->forks[i]);
		// pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
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
	if (data.nb_philos == 1)
	{
		ft_wait(data.time_to_die);
		ft_print_msg(&philos[0], "died");
	}
	else
	{
		ft_run_routines(philos);
		while (1)
		{
			if (ft_check(philos) < 0)
				break ;
			ft_wait(1);
		}
	}
	ft_free_forks(&data);
	free(philos);
	free(data.forks);
	ft_wait(100);
	return (0);
}
