/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:34 by momrane           #+#    #+#             */
/*   Updated: 2024/02/11 14:08:33 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free_everything2(t_data *data, t_philo2 *philos)
{
	// int	i;

	// i = 0;
	// while (i < data->nb_philos)
	// {
	// 	free(philos[i].thread);
	// 	i++;
	// }
	free(data->forks);
	free(philos);
}
