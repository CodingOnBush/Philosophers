/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/03/02 14:47:55 by momrane          ###   ########.fr       */
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

static void	ft_maybe_philo_die(t_philo *philo)
{
	t_data	*data;
	long	death_time;
	int		philo_id;

	data = philo->data;
	philo_id = philo->id;
	pthread_mutex_lock(&data->loop_mutex);
	if (data->loop >= 0 || data->loop == -1)
	{
		pthread_mutex_unlock(&data->loop_mutex);
		return ;
	}
	death_time = philo->last_meal - data->beginning + data->time_to_die;
	if (data->time_to_die < data->time_to_eat)
		death_time = philo->last_meal - data->beginning + data->time_to_die;
	else
		death_time = ft_get_ms_since(data->beginning);
	// printf("%ld\t%d\t%s\n", death_time, philo_id + 1, "died");
	printf("%ld %d %s\n", death_time, philo_id + 1, "died");
	data->loop = philo_id;
	pthread_mutex_unlock(&data->loop_mutex);
}

int	ft_check_death(t_philo *philo)
{
	t_data	*data;
	int		philo_id;

	data = philo->data;
	philo_id = philo->id;
	pthread_mutex_lock(&data->loop_mutex);
	if (data->loop >= 0 || data->loop == -1)
	{
		// printf("YOLO\n");
		pthread_mutex_unlock(&data->loop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->loop_mutex);
	if (ft_should_i_die(data, philo_id))
	{
		// printf("philo %d should die\n", philo_id + 1);
		ft_maybe_philo_die(philo);
		return (1);
	}
	return (0);
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	t_data	*data;
	int		philo_id;
	long	time;

	data = philo->data;
	philo_id = philo->id + 1;
	time = ft_get_ms_since(data->beginning);
	pthread_mutex_lock(&(data->pencil));
	pthread_mutex_lock(&(data->loop_mutex));
	if (data->loop == -42)
		printf("%ld %d %s\n", time, philo_id, msg);
	// printf("%ld\t%d\t%s\n", current_time, philo_id, msg);
	pthread_mutex_unlock(&(data->loop_mutex));
	pthread_mutex_unlock(&(data->pencil));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (s1[i] != s2[j])
			return (0);
		i++;
		j++;
	}
	if (s1[i] != s2[j])
		return (0);
	return (1);
}
