/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:24 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 08:04:03 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_print_msg(t_env *env, int philo_id, char *msg)
{
	long	time;

	time = ft_get_current_time(env->start_time);
	pthread_mutex_lock(&env->msg_mutex);
	printf("%ld %d %s\n", time, philo_id + 1, msg);
	pthread_mutex_unlock(&env->msg_mutex);
}
