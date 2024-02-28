/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 12:38:17 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// int	ft_someone_died(t_data *data)
// {
// 	pthread_mutex_lock(&data->loop_mutex);
// 	if (data->loop >= 0)
// 	{
// 		pthread_mutex_unlock(&data->loop_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&data->loop_mutex);
// 	return (0);
// }

int	ft_should_i_die(t_data *data, int philo_id)
{
	long	current_time;
	long	diff;

	current_time = ft_what_time_is_it();
	diff = current_time - data->philos[philo_id].last_meal;
	if (diff >= data->time_to_die)
		return (1);
	return (0);
}

// void	*func(void *arg)
// {
// 	t_philo	*philo;
// 	t_data	*data;
// 	int		me;
// 	int		him;

// 	philo = (t_philo *)arg;
// 	data = philo->data;
// 	me = philo->id;
// 	him = (philo->id + 1) % philo->data->philo_nb;
// 	if (me % 2)
// 		ft_wait(philo->data->time_to_eat / 10);
// 	while (1)
// 	{
// 		// CHECK
// 		if (ft_someone_died(data) || philo->meal_count == data->meal_goal)
// 			break ;
// 		if (ft_should_i_die(data, me))
// 		{
// 			pthread_mutex_lock(&data->loop_mutex);
// 			if (data->loop == -42)
// 				data->loop = me;
// 			pthread_mutex_unlock(&data->loop_mutex);
// 			ft_print_msg(data, me, "died");
// 			break;
// 		}
		
// 		pthread_mutex_lock(&(philo->data->philos[him].fork));
// 		ft_print_msg(philo->data, me, "has taken a fork");
// 		pthread_mutex_lock(&(philo->data->philos[me].fork));
// 		ft_print_msg(philo->data, me, "has taken a fork");
// 		ft_print_msg(philo->data, me, "is eating");
// 		ft_wait(philo->data->time_to_eat);
// 		pthread_mutex_unlock(&(philo->data->philos[me].fork));
// 		pthread_mutex_unlock(&(philo->data->philos[him].fork));
		
// 		philo->meal_count++;
		
// 		// CHECK
// 		if (ft_someone_died(data))
// 			break ;
// 		if (ft_should_i_die(data, me))
// 		{
// 			pthread_mutex_lock(&data->loop_mutex);
// 			if (data->loop == -42)
// 				data->loop = me;
// 			pthread_mutex_unlock(&data->loop_mutex);
// 			ft_print_msg(data, me, "died");
// 			break;
// 		}
		
// 		philo->last_meal = ft_what_time_is_it();
// 		ft_print_msg(philo->data, me, "is sleeping");
// 		ft_wait(philo->data->time_to_sleep);
// 		if (ft_someone_died(data))
// 			break ;
// 		if (ft_should_i_die(data, me))
// 		{
// 			pthread_mutex_lock(&data->loop_mutex);
// 			if (data->loop == -42)
// 				data->loop = me;
// 			pthread_mutex_unlock(&data->loop_mutex);
// 			ft_print_msg(data, me, "died");
// 			break;
// 		}
// 		ft_print_msg(data, me, "is thinking");
// 		ft_wait(100);
// 	}
// 	if (philo->meal_count == philo->data->meal_goal)
// 		ft_print_msg(philo->data, me, "is full");
// 	return (NULL);
// }

int	ft_check_death(t_data *data, int philo_id)
{
	char	*msg;
	int		ret;

	ret = 0;
	msg = NULL;
	pthread_mutex_lock(&data->loop_mutex);
	if (data->loop >= 0)
	{
		msg = "[someone died]";
		ret = 1;
	}
	else if (data->loop == -1)
	{
		msg = "[someone is full]";
		ret = 1;
	}
	else if (ft_should_i_die(data, philo_id))
	{
		data->loop = philo_id;
		msg = "[died]";
		ret = 1;
	}
	pthread_mutex_unlock(&data->loop_mutex);

	if (ret == 1)
		ft_print_msg(data, ft_get_ms_since(data->beginning), philo_id, msg);
	return (ret);
}

int	ft_check_meal(t_data *data, int me)
{
	if (data->meal_goal == -1)
		return (0);
	if (data->philos[me].meal_count == data->meal_goal)
	{
		pthread_mutex_lock(&data->loop_mutex);
		data->loop = -1;
		pthread_mutex_unlock(&data->loop_mutex);
		return (1);
	}
	return (0);
}

void	*func(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		me;
	int		him;

	philo = (t_philo *)arg;
	data = philo->data;
	me = philo->id;
	him = (philo->id + 1) % data->philo_nb;
	if (me % 2)
		ft_wait(data->time_to_eat / 10);
	ft_print_msg(philo->data, ft_get_ms_since(data->beginning), me, "HIIII !!");
	while (1)
	{
		if (ft_check_death(data, me))
			break;
		if (ft_check_meal(data, me))
			break;
		
		// take first fork
		pthread_mutex_lock(&(data->shared.forks[me]));
		ft_print_msg(philo->data, ft_get_ms_since(data->beginning), me, "has taken a fork");
	
		// // take second fork
		// pthread_mutex_lock(&(data->shared.forks[him]));
		// ft_print_msg(philo->data, ft_get_ms_since(data->beginning), me, "has taken a fork");

		// start eating
		ft_print_msg(data, ft_get_ms_since(data->beginning), me, "is eating");
		ft_wait(data->time_to_eat);

		// unlock first fork after eating
		pthread_mutex_unlock(&(data->shared.forks[me]));
		pthread_mutex_unlock(&(data->shared.forks[him]));

		// update meal count and last meal
		if (data->meal_goal != -1)
			philo->meal_count++;
		philo->last_meal = ft_what_time_is_it();


		if (ft_check_death(data, me))
			break;
		if (ft_check_meal(data, me))
			break;

		ft_print_msg(data, ft_get_ms_since(data->beginning), me, "is sleeping");
		ft_wait(data->time_to_sleep);
		ft_print_msg(data, ft_get_ms_since(data->beginning), me, "is thinking");
	}
	if (philo->meal_count == data->meal_goal)
		ft_print_msg(data, ft_get_ms_since(data->beginning), me, "is full");
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = ft_create_data(ac, av);
	if (!data)
		return (1);
	data->beginning = ft_what_time_is_it();
	
	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].last_meal = data->beginning;
		pthread_create(&data->philos[i].thrd, NULL, func, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(data->philos[i].thrd, NULL);
		i++;
	}

	ft_free_data(data);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_data	*data;
// 	int		i;

// 	data = ft_create_data(ac, av);
// 	if (!data)
// 		return (1);
// 	data->beginning = ft_what_time_is_it();
// 	i = 0;
// 	while (i < data->philo_nb)
// 	{
// 		data->philos[i].last_meal = data->beginning;
// 		pthread_create(&data->philos[i].thrd, NULL, func, &data->philos[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->philo_nb)
// 	{
// 		pthread_join(data->philos[i].thrd, NULL);
// 		i++;
// 	}
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