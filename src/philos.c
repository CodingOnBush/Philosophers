/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/14 07:32:01 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*ft_create_philos(t_data *data)
{
	t_philo	*philos;
	int			iter;

	philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
		return (NULL);
	iter = 0;
	while (iter < data->nb_philos)
	{
		philos[iter].id = iter;
		philos[iter].meal_count = 0;
		philos[iter].last_meal = data->start_time;
		philos[iter].data = data;
		iter++;
	}
	return (philos);
}
