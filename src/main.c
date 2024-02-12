/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/12 16:28:11 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_run_loop(void *arg)
{
	t_philo2	*philos;
	int			i;

	philos = (t_philo2 *)arg;
	i = 0;
	while (i < philos->data->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, ft_philo_routine2, (void *)&philos[i]);
		pthread_detach(philos[i].thread);
		// pthread_join(philos[i].thread, NULL);
		i++;
	}
	ft_wait(3000);
	philos->data->someone_died = 15;
	ft_wait(3000);
	// i = 0;
	// while (i < philos->data->nb_philos)
	// {
	// 	pthread_cancel(philos[i].thread);
	// 	i++;
	// }
	free(philos->data->forks);
	free(philos);
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
	// free(philos);
	// free(data.forks);
	return (0);
}
