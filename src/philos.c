/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/12 16:12:09 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo2	*ft_create_philos2(t_data *data)
{
	t_philo2	*philos;
	int			iter;

	philos = malloc(sizeof(t_philo2) * data->nb_philos);
	if (!philos)
		return (NULL);
	iter = 0;
	printf("nb_philos : %d\n", data->nb_philos);
	while (iter < data->nb_philos)
	{
		philos[iter].id = iter;
		philos[iter].data = data;
		philos[iter].meal_count = 0;
		philos[iter].last_meal = data->start_time;
		philos[iter].is_dead = 0;
		philos[iter].thread = iter;
		iter++;
	}
	return (philos);
}
