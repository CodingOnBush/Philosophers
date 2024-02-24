/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 17:26:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_data *data, int philo_id, char *msg)
{
	pthread_mutex_t	pencil;
	long			time;

	time = ft_get_ms_since(data->beginning);
	if (time < 0)
		return ;
	pencil = data->shared.pencil;
	pthread_mutex_lock(&pencil);
	pthread_mutex_lock(&data->shared.update_looping);
	if (data->shared.looping)
		printf("%ld\t%d\t%s\n", time, (philo_id + 1), msg);
	else
		pthread_mutex_unlock(&data->shared.update_looping);
	pthread_mutex_unlock(&data->shared.update_looping);
	pthread_mutex_unlock(&pencil);
}
