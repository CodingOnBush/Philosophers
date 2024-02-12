/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/12 17:34:07 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_start_threads(t_philo2 *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, ft_philo_routine2, (void *)&philos[i]) < 0)
			return (-1);
		if (pthread_detach(philos[i].thread) < 0)
			return (-1);
		i++;
	}
	return (0);
}

void	*ft_run_loop(void *arg)
{
	t_philo2	*philos;
	t_data		*data;

	philos = (t_philo2 *)arg;
	data = philos->data;
	if (ft_start_threads(philos) < 0)
		pthread_exit(NULL);
	while (data->someone_died == -1)
	{
		ft_check_philos(philos);
		ft_wait(3000);
	}
	
	pthread_exit(NULL);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo2	*philos;
	t_data 		data;
	pthread_t	main_thread;
	
	// int			loop;

	philos = NULL;
	if (ft_init_everything2(&data, ac, av) < 0)
		return (-1);
	philos = ft_create_philos2(&data);
	if (!philos)
		return (-1);
	pthread_create(&main_thread, NULL, ft_run_loop, (void *)philos);
	pthread_join(main_thread, NULL);
	free(philos);
	free(data.forks);
	return (0);
}
