/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/12 15:17:08 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_data2
{
	pthread_mutex_t	*mutex;
	char			*message;
}					t_data2;

void	*func(void *arg)
{
	t_data2	*data;

	data = (t_data2 *)arg;
	printf("[%s] lancé ✅\n", data->message);
	sleep(3);
	pthread_mutex_lock(data->mutex);
	printf("[%s] le mutex a été lock et on va patienter 5 secondes\n", data->message);
	sleep(5);// 5 seconds
	pthread_mutex_unlock(data->mutex);
	printf("[%s] le mutex a été unlock\n", data->message);
	return (NULL);
}

int	main(void)
{
	pthread_t		thread_id1;
	pthread_t		thread_id2;
	t_data2			data1;
	t_data2			data2;
	pthread_mutex_t	mutex;

	data1.message = "Thread 1";
	data2.message = "Thread 2";
	data1.mutex = &mutex;
	data2.mutex = &mutex;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread_id1, NULL, func, (void *)&data1);
	pthread_create(&thread_id2, NULL, func, (void *)&data2);
	sleep(11);// 11 seconds
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_philo2	*philos;
// 	t_data 		data;
// 	// int			loop;

// 	philos = NULL;
// 	if (ft_init_everything2(&data, philos, ac, av) < 0)
// 		return (-1);
// 	// loop = 0;
// 	// while (loop < 10)
// 	// {
// 	// 	if (data.global_meals_count == data.global_meals_goal)
// 	// 	{
// 	// 		printf("All philos have eaten enough\n");
// 	// 		break ;
// 	// 	}
// 	// 	else if (data.someone_died != -1)
// 	// 	{
// 	// 		printf("Philosopher %d died\n", data.someone_died);
// 	// 		break ;
// 	// 	}
// 	// 	printf("looping\n");
// 	// 	ft_wait(10);
// 	// 	loop++;
// 	// }
// 	ft_free_everything2(&data, philos);
// 	return (0);
// }
