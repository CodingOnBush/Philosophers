/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:20:10 by momrane           #+#    #+#             */
/*   Updated: 2024/02/26 12:45:17 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

pthread_mutex_t	*ft_create_forks(int size)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(size * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	memset(forks, 0, size * sizeof(pthread_mutex_t));
	while (i < size)
	{
		memset(&forks[i], 0, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(&forks[i], NULL))
		{
			printf("Error: pthread_mutex_init\n");
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
