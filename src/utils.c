/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:06:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/02 15:07:27 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	ft_toggle_status(t_philo *philo)
{
	if (philo->status == 'e')
		philo->status = 's';
	else if (philo->status == 's')
		philo->status = 't';
	else
		philo->status = 'e';
	return (philo->status);
}
