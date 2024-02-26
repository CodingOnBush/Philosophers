/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/26 17:20:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_data *data, int philo_id, char *msg)
{
	pthread_mutex_lock(&data->loop_mutex);
	if (data->loop == -42)
		printf("%ld\t%d\t%s\n", ft_get_ms_since(data->beginning), philo_id, msg);
	pthread_mutex_unlock(&data->loop_mutex);	
}
