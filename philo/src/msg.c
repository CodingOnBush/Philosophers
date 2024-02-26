/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/26 18:11:22 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_msg_is_died(char *msg)
{
	if (msg[0] == 'd' && msg[1] == 'i' && msg[2] == 'e' && msg[3] == 'd')
		return (1);
	return (0);

}

void	ft_print_msg(t_data *data, int philo_id, char *msg)
{
	pthread_mutex_lock(&data->shared.pencil);
	if (data->loop == -42 || ft_msg_is_died(msg))
		printf("%ld\t%d\t%s\n", ft_get_ms_since(data->beginning), philo_id, msg);
	pthread_mutex_unlock(&data->shared.pencil);	
}
