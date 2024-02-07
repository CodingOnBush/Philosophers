/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 08:33:59 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_philo_routine(void *arg)
{
	t_save	*save;

	save = (t_save *)arg;
	// pthread_mutex_lock(&save->env->msg_mutex);
	printf("I'm in the routine with id: %d\n", save->current_philo->id);
	// pthread_mutex_unlock(&save->env->msg_mutex);
	// t_env	*env;

	// env = (t_env *)arg;
	// printf("I'm in the routine with id: %d\n", env->selected_philo->id);
	// env->someone_died = 0;
	ft_wait(4000);
	// pthread_mutex_lock(&save->env->msg_mutex);
	printf("I'm done with id: %d\n", save->current_philo->id);
	// pthread_mutex_unlock(&save->env->msg_mutex);
	save->env->someone_died = 1;
	return (NULL);
}

int	ft_start_routines(t_env *env)
{
	t_philo	*philos;
	t_save	*save;
	// t_save	save;
	int		i;

	i = 0;
	philos = env->philos;
	if (env->nb_philos % 2 != 0)
	{
		while (i < env->nb_philos)
		{
			if (philos->last_meal == -1)
				philos->last_meal = env->start_time;
			save = malloc(sizeof(t_save));
			if (!save)
				return (-1);
			printf("save created\n");
			save->current_philo = philos;
			save->env = env;
			// save.current_philo = philos;
			// save.env = env;
			pthread_create(philos->thread, NULL, ft_philo_routine, save);
			pthread_join(*philos->thread, NULL);
			philos = philos->right->right;
			// if (philos->routine_start == 0)
			// {
			// 	env->selected_philo = philos;
			// 	printf("Starting routine with id: %d\n", env->selected_philo->id);
			// 	if (pthread_create(&(philos->thread), NULL, ft_philo_routine, env) != 0)
			// 		return (-1);
			// 	philos->routine_start = 1;
			// 	philos = philos->right->right;
			// }
			// else
			// 	philos = philos->right;
			i++;
		}
	}
	return (0);
}
