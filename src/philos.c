/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/13 15:59:51 by allblue          ###   ########.fr       */
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
	printf("nb_philos : %d\n", data->nb_philos);
	while (iter < data->nb_philos)
	{
		philos[iter].id = iter;
		philos[iter].data = data;
		philos[iter].meal_count = 0;
		philos[iter].last_meal = data->start_time;
		philos[iter].routine_flag = 0;
		iter++;
	}
	return (philos);
}
