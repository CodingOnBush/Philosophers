/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:43:01 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 14:43:00 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_init_data(t_data *data, int ac, char **av)
{
	if (!ft_get_arguments(data, ac, av))
		return (0);
	data->beginning = ft_what_time_is_it();
	data->philos = ft_create_philos(data);
	if (!data->philos)
		return (0);
	if (!ft_init_shared(data))
		return (free(data->philos), 0);
	return (1);
}

t_data	*ft_create_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (!ft_init_data(data, ac, av))
		return (free(data), NULL);
	return (data);
}
