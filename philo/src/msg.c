/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 12:02:19 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_msg_is_died(char *msg)
{
	if (msg[0] == 'd' && msg[1] == 'i' && msg[2] == 'e' && msg[3] == 'd')
		return (1);
	return (0);

}

void	ft_print_msg(t_data *data, long time, int philo_id, char *msg)
{
	pthread_mutex_lock(&(data->shared.pencil));
	// pthread_mutex_lock(&data->loop_mutex);
	// if (data->loop == -42 || ft_msg_is_died(msg))
	printf("%ld\t%d\t%s\n", time, philo_id, msg);
	// pthread_mutex_unlock(&data->loop_mutex);
	pthread_mutex_unlock(&(data->shared.pencil));
}
