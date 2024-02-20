/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/20 17:24:14 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_run_routines(t_philo *philos)
{
	int			i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, ft_philo_routine, (void *)&philos[i]);
		pthread_detach(philos[i].thread);
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
			ft_print_msg(&philos[i], "died");
			return (-1);
		}
		else if (data->meals_count == data->meals_goal)
		{
			// data->routine_flag = 0;
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
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

static void ft_free_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		pthread_cancel(philos[i].thread);
		i++;
	}
}

static void	ft_run_loop(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (philos[i].last_meal + data->time_to_die < ft_get_current_time(data->start_time))
		{
			ft_print_msg(&philos[i], "died");
			break ;
		}
		else if (data->meals_count == data->meals_goal)
		{
			ft_print_msg(&philos[i], "ALL PHILOS has finished eating");
			break ;
		}
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
		ft_run_loop(&data, philos);
	}
	ft_free_threads(philos);
	ft_free_forks(&data);
	pthread_mutex_unlock(&data.log_mutex);
	pthread_mutex_destroy(&data.log_mutex);
	free(philos);
	ft_wait(1000);
	return (0);
}
