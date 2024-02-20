/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/20 21:21:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_start_routines(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, ft_philo_routine,
			(void *)&philos[i]);
		pthread_detach(philos[i].thread);
		i++;
	}
}

// static int	ft_check(t_philo *philos)
// {
// 	t_data	*data;
// 	int		i;

// 	i = 0;
// 	data = philos->data;
// 	while (i < data->nb_philos)
// 	{
// 		if (philos[i].last_meal
			// + data->time_to_die < ft_get_current_time(data->start_time))
// 		{
// 			ft_print_msg(&philos[i], "died");
// 			return (-1);
// 		}
// 		else if (data->meals_count == data->meals_goal)
// 		{
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

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

static void	ft_free_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		if (pthread_cancel(philos[i].thread) != 0)
			printf("Error: pthread_cancel\n");
		i++;
	}
}

static void	ft_run_loop(t_data *data, t_philo *philos)
{
	long	add;
	int		i;

	i = 0;
	while (1)
	{
		add = philos[i].last_meal + data->time_to_die;
		if (add < ft_get_current_time(data->start_time))
		{
			ft_print_msg(&philos[i], "died");
			data->someone_died = philos[i].id;
			break ;
		}
		else if (data->meals_count == data->meals_goal)
		{
			ft_print_msg(&philos[i], "ALL PHILOS has finished eating");
			break ;
		}
		if (i == data->nb_philos - 1)
			i = 0;
		else
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
		ft_start_routines(philos);
		ft_run_loop(&data, philos);
	}
	ft_free_threads(philos);
	ft_free_forks(&data);
	free(philos);
	ft_wait(1000);
	pthread_mutex_destroy(&data.log_mutex);
	return (0);
}

/*
Do not test with more than 200 philosophers.
Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
Test 1 800 200 200. The philosopher should not eat and should die.
Test 5 800 200 200. No philosopher should die.
Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
Test 4 410 200 200. No philosopher should die.
Test 4 310 200 100. One philosopher should die.
Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
Test with any values of your choice to verify all the requirements.
Ensure philosophers die at the right time, that they don't steal forks,
	and so forth.
*/