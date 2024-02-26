/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/26 13:41:35 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_routine_must_stop(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->shared.update_looping);
	if (data->shared.looping == 0)
	{
		pthread_mutex_unlock(&data->shared.update_looping);
		return (1);
	}

	
	
	pthread_mutex_lock(&data->shared.someone_died_mutex);
	if (data->shared.someone_died == 1)
	{
		if (data->shared.looping == 1)
			data->shared.looping = 0;
		pthread_mutex_unlock(&data->shared.someone_died_mutex);
		pthread_mutex_unlock(&data->shared.update_looping);
		return (1);
	}
	if (data->shared.someone_died == 1 || ft_philo_is_dead(philo))
	{
		data->shared.someone_died = 1;
		if (data->shared.looping == 1)
			data->shared.looping = 0;
		pthread_mutex_unlock(&data->shared.someone_died_mutex);
		pthread_mutex_unlock(&data->shared.update_looping);
		return (1);
	}
	pthread_mutex_unlock(&data->shared.someone_died_mutex);
	
	
	
	pthread_mutex_unlock(&data->shared.update_looping);
	return (0);
}

void	*func(void *arg)
{
	t_philo	*philo;
	int		me;
	int		him;

	philo = (t_philo *)arg;
	me = philo->id;
	him = (philo->id + 1) % philo->data->philo_nb;
	if (me % 2)
		ft_wait(philo->data->time_to_eat);
	ft_set_last_meal(philo);
	while (1)
	{
		if (ft_routine_must_stop(philo->data, philo))
			break ;
		ft_print_msg(philo->data, me, "is waiting for his fork");
		pthread_mutex_lock(&philo->data->shared.forks[me]);
		if (ft_routine_must_stop(philo->data, philo))
		{
			pthread_mutex_unlock(&philo->data->shared.forks[me]);
			break ;
		}
		ft_print_msg(philo->data, me, "has taken a fork");


		ft_print_msg(philo->data, me, "is waiting for the neighbor's fork");
		pthread_mutex_lock(&philo->data->shared.forks[him]);
		if (ft_routine_must_stop(philo->data, philo))
		{
			pthread_mutex_unlock(&philo->data->shared.forks[me]);
			pthread_mutex_unlock(&philo->data->shared.forks[him]);
			break ;
		}
		ft_print_msg(philo->data, me, "has taken a fork");

		ft_print_msg(philo->data, me, "is eating");
		ft_wait(philo->data->time_to_eat);
		pthread_mutex_lock(&philo->data->shared.last_meal_mutex);
		philo->last_meal += philo->data->time_to_eat;
		pthread_mutex_unlock(&philo->data->shared.last_meal_mutex);
		
		pthread_mutex_unlock(&philo->data->shared.forks[me]);
		pthread_mutex_unlock(&philo->data->shared.forks[him]);

		if (ft_routine_must_stop(philo->data, philo))
			break ;
		
		ft_print_msg(philo->data, me, "is sleeping");
		ft_wait(philo->data->time_to_sleep);

		if (ft_routine_must_stop(philo->data, philo))
			break ;

		ft_print_msg(philo->data, me, "is thinking");

		ft_wait(1);
	}
	return (NULL);
}

void	*watch(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		if (ft_philo_is_dead(&data->philos[i]))
		{
			pthread_mutex_lock(&data->shared.update_looping);
			data->shared.looping = 0;
			pthread_mutex_unlock(&data->shared.update_looping);
			ft_print_msg(data, i, "died");
			break ;
		}
		i++;
		if (i == data->philo_nb)
			i = 0;
		ft_wait(8);
	}
	// pthread_mutex_lock(&data->shared.finish);
	// data->shared.looping = 0;
	// pthread_mutex_unlock(&data->shared.finish);
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
	// pthread_detach(watcher);
	// printf("bye\n");
	data->beginning = ft_what_time_is_it();
	pthread_create(&data->philos[0].thrd, NULL, func, &data->philos[0]);
	pthread_create(&data->philos[1].thrd, NULL, func, &data->philos[1]);
	// pthread_create(&data->philos[2].thrd, NULL, func, &data->philos[2]);
	pthread_join(data->philos[0].thrd, NULL);
	pthread_join(data->philos[1].thrd, NULL);
	// pthread_join(data->philos[2].thrd, NULL);

	pthread_join(watcher, NULL);
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