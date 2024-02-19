/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/19 11:19:46 by allblue          ###   ########.fr       */
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

// static int	ft_check(t_philo *philos)
// {
// 	t_data	*data;
// 	int		i;

// 	i = 0;
// 	data = philos->data;
// 	while (i < data->nb_philos)
// 	{
// 		if (ft_still_alive(&philos[i]) == 0)
// 		{
// 			ft_print_msg(&philos[i], "died");
// 			data->someone_died = philos[i].id;
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

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
	ft_run_routines(philos);
	while (1)
	{
		ft_check_philos(philos);
		ft_wait(10);
	}
	ft_wait(100);
	free(philos);
	free(data.forks);
	return (0);
}
