/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 14:40:13 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_msg_is_died(char *msg)
{
	if (msg[0] == 'd' && msg[1] == 'i' && msg[2] == 'e' && msg[3] == 'd')
		return (1);
	return (0);
}

static int	ft_msg_is_full(char *msg)
{
	if (msg[0] == 'f' && msg[1] == 'u' && msg[2] == 'l' && msg[3] == 'l')
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
	pthread_mutex_lock(&(data->shared.pencil));
	pthread_mutex_lock(&data->loop_mutex);
	current_time = ft_get_ms_since(data->beginning);
	if (ft_msg_is_died(msg) || ft_msg_is_full(msg))
		printf("%ld\t%d\t%s\n", ft_get_ms_since(data->beginning), philo_id, msg);
	else if (data->loop == -42)
		printf("%ld\t%d\t%s\n", ft_get_ms_since(data->beginning), philo_id, msg);
	pthread_mutex_unlock(&data->loop_mutex);
	pthread_mutex_unlock(&(data->shared.pencil));
}
