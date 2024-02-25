/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/25 17:49:21 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_watching_philosophers(void *arg)
{
	int		philos_full;
	t_philo	*philos;
	t_data	*data;
	int		i;

	philos_full = 0;
	data = (t_data *)arg;
	philos = data->philos;
	i = 0;
	while (i < data->philo_nb)
	{
		if (!ft_philo_is_dead(philos[i].last_meal, data))
		{
			ft_print_msg(data, philos[i].id, "died");
			break;
		}
		if (ft_philo_is_full(philos[i]))
			philos_full++;
		if (i == data->philo_nb - 1)
		{
			i = 0;
			if (philos_full == data->philo_nb)
				break ;
			philos_full = 0;
		}
		else
			i++;
		ft_wait(1);
	}
	// pthread_mutex_unlock(&data->shared.finish);
	// pthread_mutex_lock(&data->shared.update_looping);
	// data->shared.looping = 0;
	// pthread_mutex_unlock(&data->shared.update_looping);
	if (data->philo_nb == 1)
		pthread_mutex_unlock(&data->shared.forks[0]);
	return (NULL);
}

int	ft_is_looping_finished(t_data *data)
{
	int	looping_status;

	pthread_mutex_lock(&data->shared.finish);
	looping_status = data->shared.looping;
	pthread_mutex_unlock(&data->shared.finish);
	return (looping_status);
}

void	*func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->shared.pencil);
	printf("%ld\t| HI from func %d\n", ft_get_ms_since(philo->data->beginning), philo->id);
	pthread_mutex_unlock(&philo->data->shared.pencil);
	philo->last_meal = philo->data->beginning;
	while (1)
	{
		if (!ft_is_looping_finished(philo->data))
			break ;
		pthread_mutex_lock(&philo->data->shared.philo_mutex);
		if (ft_philo_is_dead(philo->last_meal, philo->data))
		{
			philo->alive = 0;
			pthread_mutex_unlock(&philo->data->shared.philo_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->shared.philo_mutex);
		ft_wait(10);
	}
	pthread_mutex_lock(&philo->data->shared.pencil);
	printf("%ld\t| BYE from func %d\n", ft_get_ms_since(philo->data->beginning), philo->id);
	pthread_mutex_unlock(&philo->data->shared.pencil);
	return (NULL);
}

void	*watch(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->shared.pencil);
	printf("%ld\t| msg from the watcher\n", ft_get_ms_since(data->beginning));
	pthread_mutex_unlock(&data->shared.pencil);
	ft_wait(2000);
	
	i = 0;
	while (1)
	{	
		if (!data->philos[i].alive)
		{
			pthread_mutex_lock(&data->shared.pencil);
			printf("%ld\t| %d died\n", ft_get_ms_since(data->beginning), i);
			pthread_mutex_unlock(&data->shared.pencil);
			break;
		}
		i++;
		if (i == data->philo_nb)
			i = 0;
		ft_wait(8);
	}

	pthread_mutex_lock(&data->shared.finish);
	data->shared.looping = 0;
	pthread_mutex_unlock(&data->shared.finish);
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	watcher;
	t_data		*data;

	data = ft_create_data(ac, av);
	if (!data)
		return (1);
	
	pthread_create(&watcher, NULL, watch, data);
	pthread_detach(watcher);

	pthread_create(&data->philos[0].thrd, NULL, func, &data->philos[0]);
	pthread_create(&data->philos[1].thrd, NULL, func, &data->philos[1]);
	pthread_create(&data->philos[2].thrd, NULL, func, &data->philos[2]);
	
	pthread_join(data->philos[0].thrd, NULL);
	pthread_join(data->philos[1].thrd, NULL);
	pthread_join(data->philos[2].thrd, NULL);
	ft_free_data(data);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	pthread_t	watcher;
// 	t_data		*data;

// 	data = ft_create_data(ac, av);
// 	if (!data)
// 		return (1);
// 	pthread_create(&watcher, NULL, ft_watching_philosophers, data);
// 	pthread_detach(watcher);
// 	ft_launch_philosophers_threads(data);
// 	ft_wait_for_threads(data);
// 	ft_free_data(data);
// 	return (0);
// }

/*
./philo 2 100 5000 200
./philo 198 210 100 100
./philo 200 210 100 100
./philo 2 210 100 100
Ensure the code of philo complies with the following requirements and ask for explanations.
Check there is one thrd per philosopher.
Check there is only one fork per philosopher.
Check if there is a mutex per fork and that it's used to check the fork value and/or change it.
Check the outputs are never mixed up.
Check how the death of a philosopher is verified and if there is a mutex to prevent a philosopher from dying and starting eating at the same time.
philo testing
Do not test with more than 200 philosophers.
Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
Test 1 800 200 200. The philosopher should not eat and should die.
Test 5 800 200 200. No philosopher should die.
Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
Test 4 410 200 200. No philosopher should die.
Test 4 310 200 100. One philosopher should die.
Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time,
	that they don't steal forks, and so forth.

*/

// int	main(void)
// {
// 	pthread_mutex_t t1;
// 	pthread_mutex_t t2;
	
// 	pthread_mutex_init(&t1, NULL);
// 	pthread_mutex_init(&t2, NULL);
// 	printf("t1.__align after pthread_mutex_init = %ld\n", t1.__align);
// 	printf("t2.__align after pthread_mutex_init = %ld\n", t2.__align);
	
// 	pthread_mutex_lock(&t1);
// 	pthread_mutex_lock(&t2);
// 	printf("t1.__align after pthread_mutex_lock = %ld\n", t1.__align);
// 	printf("t2.__align after pthread_mutex_lock = %ld\n", t2.__align);
	
// 	pthread_mutex_unlock(&t1);
// 	pthread_mutex_unlock(&t2);
// 	printf("t1.__align after pthread_mutex_unlock = %ld\n", t1.__align);
// 	printf("t2.__align after pthread_mutex_unlock = %ld\n", t2.__align);

// 	pthread_mutex_destroy(&t1);
// 	pthread_mutex_destroy(&t2);
// 	printf("t1.__align after pthread_mutex_destroy = %ld\n", t1.__align);
// 	printf("t2.__align after pthread_mutex_destroy = %ld\n", t2.__align);
// 	return (0);
// }