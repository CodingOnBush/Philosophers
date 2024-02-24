/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 13:55:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_philo philo, char *msg)
{
	long	time;

	time = ft_get_ms_since(philo.data->beginning);
	if (time < 0)
		return ;
	pthread_mutex_lock(&philo.data->shared.pencil);
	if (!philo.data->shared.someone_died)
		printf("%ld\t%d\t%s\n", time, (philo.id + 1), msg);
	pthread_mutex_unlock(&philo.data->shared.pencil);
}
