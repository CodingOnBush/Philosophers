/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:53:44 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 13:05:10 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_controller(t_philo *philo)
{
	t_simul	*simul;
	int		state;

	simul = philo->simul;
	state = ft_get_simul_state(simul);
	if (state >= 0 || state == ALL_ATE || simul->infos.meal_goal == 0)
		return (STOP);
	return (CONTINUE);
}

static void	ft_eat(t_philo *philo)
{
	ft_update_last_meal(philo, ft_get_time());
	ft_print_status(philo, "is eating");
	ft_usleep(philo->simul->infos.time_to_eat);
	ft_drop_forks(philo, philo->my_fork, philo->other_fork);
	pthread_mutex_lock(&philo->simul->philo_mutex);
	philo->meal_count = philo->meal_count + 1;
	pthread_mutex_unlock(&philo->simul->philo_mutex);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	t_infos	infos;
	int		think_time;

	philo = (t_philo *)arg;
	infos = philo->simul->infos;
	think_time = infos.time_to_die - (infos.time_to_eat + infos.time_to_sleep);
	ft_update_last_meal(philo, ft_get_time());
	while (ft_controller(philo) == CONTINUE)
	{
		if (ft_grab_forks(philo) == FAIL)
			break ;
		ft_eat(philo);
		if (ft_controller(philo) == STOP)
			break ;
		ft_print_status(philo, "is sleeping");
		ft_usleep(philo->simul->infos.time_to_sleep);
		ft_print_status(philo, "is thinking");
		if (ft_controller(philo) == STOP)
			break ;
		ft_usleep(think_time / 2);
	}
	return (NULL);
}
