/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:20:10 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 16:21:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

pthread_mutex_t	*ft_create_forks(int size)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(size * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			printf("Error: pthread_mutex_init\n");
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static int	ft_lock_forks_mutex(t_philo *philo, int me, int him)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_lock(&(data->forks[me])))
		return (0);
	if (ft_check_death(philo))
	{
		pthread_mutex_unlock(&(data->forks[me]));
		return (0);
	}
	ft_print_msg(philo, "has taken a fork");
	if (pthread_mutex_lock(&(data->forks[him])))
	{
		pthread_mutex_unlock(&(data->forks[me]));
		return (0);
	}
	if (ft_check_death(philo))
	{
		pthread_mutex_unlock(&(data->forks[him]));
		pthread_mutex_unlock(&(data->forks[me]));
		return (0);
	}
	ft_print_msg(philo, "has taken a fork");
	return (1);
}

int	ft_grab_forks(t_philo *philo)
{
	t_data	*data;
	int		me;
	int		him;

	data = philo->data;
	me = philo->id;
	him = (philo->id + 1) % data->philo_nb;
	if (me == data->philo_nb - 1)
		ft_swap(&me, &him);
	if (!ft_lock_forks_mutex(philo, me, him))
		return (0);
	return (1);
}

void	ft_drop_forks(t_philo *philo)
{
	t_data	*data;
	int		me;
	int		him;

	data = philo->data;
	me = philo->id;
	him = (philo->id + 1) % data->philo_nb;
	if (me == data->philo_nb - 1)
		ft_swap(&me, &him);
	pthread_mutex_unlock(&(data->forks[me]));
	pthread_mutex_unlock(&(data->forks[him]));
}
