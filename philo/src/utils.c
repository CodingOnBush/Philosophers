/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 16:22:13 by momrane          ###   ########.fr       */
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
	char	*msg;
	int		ret;
	int		philo_id;

	data = philo->data;
	philo_id = philo->id;
	ret = 0;
	msg = NULL;
	pthread_mutex_lock(&data->loop_mutex);
	if (data->loop >= 0 || data->loop == -1)
		ret = 1;
	else if (ft_should_i_die(data, philo_id))
	{
		data->loop = philo_id;
		msg = "died";
		ret = 1;
	}
	pthread_mutex_unlock(&data->loop_mutex);
	if (ret == 1 && msg)
		ft_print_msg(&data->philos[philo_id], msg);
	return (ret);
}

static int	ft_msg_is_died(char *msg)
{
	if (msg[0] == 'd' && msg[1] == 'i' && msg[2] == 'e' && msg[3] == 'd')
		return (1);
	return (0);
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	long	current_time;
	t_data	*data;
	int		philo_id;

	data = philo->data;
	philo_id = philo->id + 1;
	pthread_mutex_lock(&(data->pencil));
	pthread_mutex_lock(&data->loop_mutex);
	current_time = ft_get_ms_since(data->beginning);
	if (data->loop == -42 || ft_msg_is_died(msg))
		printf("%ld\t%d\t%s\n", ft_get_ms_since(data->beginning), philo_id, msg);
	pthread_mutex_unlock(&data->loop_mutex);
	pthread_mutex_unlock(&(data->pencil));
}
