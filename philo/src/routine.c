/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/03/01 10:54:25 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static int	ft_philo_is_full(t_philo *philo)
// {
// 	t_data	*data;

// 	data = philo->data;
// 	if (data->meal_goal == -1)
// 		return (0);
// 	pthread_mutex_lock(&philo->meal_count_mutex);
// 	if (philo->meal_count == data->meal_goal)
// 	{
// 		pthread_mutex_unlock(&philo->meal_count_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->meal_count_mutex);
// 	return (0);
// }

// static int	ft_check_loop(t_data *data)
// {
// 	pthread_mutex_lock(&data->loop_mutex);
// 	if (data->loop >= 0 || data->loop == -1)
// 	{
// 		pthread_mutex_unlock(&data->loop_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&data->loop_mutex);
// 	return (0);
// }

static int	ft_philo_is_alive(t_philo *philo)
{
	long	last_meal;
	long	current_time;
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	current_time = ft_what_time_is_it();
	if (current_time - last_meal >= data->time_to_die)
		return (0);
	return (1);
}

static void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		meal_count;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_wait(philo->data->time_to_eat / 2);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = ft_what_time_is_it();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	meal_count = 0;
	while (1)
	{
		if (philo->data->meal_goal != -1 && meal_count == philo->data->meal_goal)
			break;
		
		if (!ft_grab_forks(philo))
			break;
		
		if (!ft_philo_is_alive(philo))
		{
			pthread_mutex_lock(&philo->death_mutex);
			philo->dead = 1;
			philo->time_death = ft_what_time_is_it();
			pthread_mutex_unlock(&philo->death_mutex);
			ft_drop_forks(philo);
			break;
		}


		ft_print_msg(philo, "is eating");
		ft_wait(philo->data->time_to_eat);

		if (!ft_philo_is_alive(philo))
		{
			pthread_mutex_lock(&philo->death_mutex);
			philo->dead = 1;
			philo->time_death = ft_get_ms_since(philo->data->beginning);
			pthread_mutex_unlock(&philo->death_mutex);
			ft_drop_forks(philo);
			break;
		}

		// pthread_mutex_lock(&philo->last_meal_mutex);
		// if (ft_what_time_is_it() - philo->last_meal > philo->data->time_to_die)
		// {
		// 	philo->dead = 1;
		// 	pthread_mutex_unlock(&philo->last_meal_mutex);
		// 	ft_drop_forks(philo);
		// 	break;
		// }
		// pthread_mutex_unlock(&philo->last_meal_mutex);

		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = ft_what_time_is_it();
		pthread_mutex_unlock(&philo->last_meal_mutex);

		ft_drop_forks(philo);
		
		if (philo->data->meal_goal != -1)
			meal_count++;
		
		ft_print_msg(philo, "is sleeping");
		ft_wait(philo->data->time_to_sleep);
		ft_print_msg(philo, "is thinking");
	}
	
	// check death
	pthread_mutex_lock(&philo->death_mutex);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->death_mutex);
		pthread_mutex_lock(&philo->data->loop_mutex);
		if (philo->data->loop == -42)
		{
			pthread_mutex_lock(&philo->data->pencil);
			printf("%ld %d died\n", philo->time_death, philo->id + 1);
			pthread_mutex_unlock(&philo->data->pencil);
			philo->data->loop = philo->id;
		}
		pthread_mutex_unlock(&philo->data->loop_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->death_mutex);

	// check if all philosophers have eaten
	if (meal_count == philo->data->meal_goal)
	{
		pthread_mutex_lock(&philo->data->all_ate_mutex);
		philo->data->all_ate++;
		if (philo->data->all_ate == philo->data->philo_nb)
		{
			pthread_mutex_lock(&philo->data->loop_mutex);
			pthread_mutex_lock(&philo->data->pencil);
			printf("All philosophers have eaten at least %d times \n", philo->data->meal_goal);
			pthread_mutex_unlock(&philo->data->pencil);
			philo->data->loop = -1;
			pthread_mutex_unlock(&philo->data->loop_mutex);
		}
		pthread_mutex_unlock(&philo->data->all_ate_mutex);
	}
	return (NULL);
}

// static void	*ft_monitoring(void *arg)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->all_ate_mutex);
// 		if (data->all_ate == data->philo_nb)
// 		{
// 			pthread_mutex_lock(&data->loop_mutex);
// 			data->loop = -1;
// 			pthread_mutex_unlock(&data->loop_mutex);
// 			printf("All philosophers have eaten at least %d times \n", data->meal_goal);
// 			pthread_mutex_unlock(&data->all_ate_mutex);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&data->all_ate_mutex);

// 		i = 0;
// 		while (i < data->philo_nb)
// 		{
// 			if (!ft_philo_is_alive(&data->philos[i]))
// 			{
// 				pthread_mutex_lock(&data->loop_mutex);
// 				if (data->loop == -42)
// 					data->loop = i;
// 				pthread_mutex_unlock(&data->loop_mutex);
// 				ft_print_msg(&data->philos[i], "died");
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		ft_wait(1);
// 	}	
// 	return (NULL);
// }

void	ft_start_simulation(t_data *data)
{
	int			i;
	// pthread_t	monitor;

	i = 0;
	
	// pthread_create(&monitor, NULL, ft_monitoring, data);
	// pthread_detach(monitor);
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philos[i].thrd, NULL, ft_routine,
				&data->philos[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->philos[i].thrd, NULL))
			return ;
		i++;
	}
}
