/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 20:09:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	ft_should_i_die(t_data *data, int philo_id)
{
	long	current_time;
	long	diff;

	current_time = ft_what_time_is_it();
	pthread_mutex_lock(&data->philos[philo_id].last_meal_mutex);
	diff = current_time - data->philos[philo_id].last_meal;
	pthread_mutex_unlock(&data->philos[philo_id].last_meal_mutex);
	if (diff >= data->time_to_die)
		return (1);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	t_data	*data;
	int		loop_value;
	int		philo_id;

	data = philo->data;
	philo_id = philo->id;
	loop_value = 0;

	pthread_mutex_lock(&data->loop_mutex);
	loop_value = data->loop;
	pthread_mutex_unlock(&data->loop_mutex);

	if (ft_should_i_die(data, philo_id))
	{
		if (loop_value >= 0 || loop_value == -1)
			return (1);
		ft_print_msg(philo, "died");
		pthread_mutex_lock(&data->loop_mutex);
		data->loop = philo_id;
		pthread_mutex_unlock(&data->loop_mutex);
		return (1);
	}
	return (0);

	// pthread_mutex_lock(&data->loop_mutex);
	// if (ft_should_i_die(data, philo_id) && data->loop == -42)
	// {
	// 	data->loop = philo_id;
	// 	ft_print_msg(philo, "died");
	// }
	
	// if (data->loop >= 0)
	// {
	// 	ret = 3;

	// }
	// else if (ft_should_i_die(data, philo_id))
	// {
	// 	data->loop = philo_id;
	// 	ret = 1;
	// }
	// printf("LOOP: %d\n", data->loop);
	// pthread_mutex_unlock(&data->loop_mutex);
	// if (ret == 3)
	// 	ft_print_msg(&data->philos[philo_id], "died");
	// else if (ret == 1)
	// 	ft_print_msg(&data->philos[philo_id], "died");
	// if (ret == 3 || ret == 1)
	// 	return (1);
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	long	current_time;
	t_data	*data;
	int		philo_id;

	data = philo->data;
	philo_id = philo->id + 1;
	pthread_mutex_lock(&(data->pencil));
	pthread_mutex_lock(&(data->loop_mutex));
	current_time = ft_get_ms_since(data->beginning);
	if (data->loop < 0)
		printf("%ld\t%d\t%s\n", current_time, philo_id, msg);
	pthread_mutex_unlock(&(data->loop_mutex));
	pthread_mutex_unlock(&(data->pencil));
}
