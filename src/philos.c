/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:22:09 by momrane           #+#    #+#             */
/*   Updated: 2024/02/11 14:08:12 by momrane          ###   ########.fr       */
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
	while (iter < data->nb_philos)
	{
		philos[iter].id = iter;
		philos[iter].data = data;
		philos[iter].meal_count = 0;
		philos[iter].last_meal = data->start_time;
		philos[iter].is_dead = 0;
		philos[iter].thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philos[iter].thread)
			return (NULL);
		philos[iter].right = &philos[(iter + 1) % data->nb_philos];
		philos[iter].left = &philos[(iter - 1 + data->nb_philos) % data->nb_philos];
		iter++;
	}
	return (philos);
}

void	ft_print_philos(t_philo2 *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		printf("--[(%p){%d}(%p){%d}(%p)]--", philos->left, philos->id + 1, philos, philos->id + 1, philos->right);
		philos = philos->right;
		i++;
	}
	printf("\n");
}
