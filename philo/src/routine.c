/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:53:44 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 09:35:08 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_controller(t_philo *philo)
{
	t_simul	*simul;
	int		state;

	simul = philo->simul;

	// pthread_mutex_lock(&simul->simul_mutex);
	// state = simul->state;
	// pthread_mutex_unlock(&simul->simul_mutex);
	state = ft_get_simul_state(simul);
	if (state >= 0 || state == ALL_ATE)
		return (STOP);
	return (CONTINUE);
}

void	*ft_routine(void *arg)
{
	t_philo		*philo;
	t_infos		infos;
	int			think_time;

	philo = (t_philo *)arg;
	infos = philo->simul->infos;
	think_time = (infos.time_to_die - (infos.time_to_eat + infos.time_to_sleep)) / 2;
	if (philo->id % 2 == 0)
		ft_usleep(philo->simul->infos.time_to_eat / 10);
	ft_update_last_meal(philo, ft_get_time());
	while (1)
	{
		if (ft_controller(philo) == STOP)
			break ;
		
		if (ft_grab_forks(philo) == FAIL)
			break ;
		if (ft_controller(philo) == STOP)
		{
			ft_drop_forks(philo, philo->my_fork, philo->other_fork);
			break ;
		}

		ft_update_last_meal(philo, ft_get_time());

		ft_print_status(philo, "is eating");
		ft_usleep(philo->simul->infos.time_to_eat);
		
		ft_drop_forks(philo, philo->my_fork, philo->other_fork);
		
		pthread_mutex_lock(&philo->simul->philo_mutex);
		philo->meal_count = philo->meal_count + 1;
		pthread_mutex_unlock(&philo->simul->philo_mutex);

		if (ft_controller(philo) == STOP)
			break ;

		ft_print_status(philo, "is sleeping");
		ft_usleep(philo->simul->infos.time_to_sleep);
		ft_print_status(philo, "is thinking");
		
		if (ft_controller(philo) == STOP)
			break ;

		ft_usleep(think_time);
	}
	return (NULL);
}
