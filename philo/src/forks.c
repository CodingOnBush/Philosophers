/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:42:37 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 10:01:07 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_drop_forks(t_philo *philo, int my_fork, int other_fork)
{
	t_simul	*simul;

	simul = philo->simul;
	pthread_mutex_unlock(&simul->forks[my_fork]);
	pthread_mutex_unlock(&simul->forks[other_fork]);
}

static int	ft_should_i_stop_grabbing(t_simul *simul)
{
	int		simul_state;
	
	simul_state = ft_get_simul_state(simul);
	if (simul_state == ALL_ATE || simul_state >= 0)
		return (FAIL);
	return (SUCCESS);
}

static int	ft_grab_first_fork(t_simul *simul, t_philo *philo, int my_fork)
{
	pthread_mutex_lock(&simul->forks[my_fork]);
	ft_print_status(philo, "has taken a fork");
	if (ft_should_i_stop_grabbing(simul) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

static int	ft_grab_other_fork(t_simul *simul, t_philo *philo, int other_fork)
{
	pthread_mutex_lock(&simul->forks[other_fork]);
	ft_print_status(philo, "has taken a fork");
	if (ft_should_i_stop_grabbing(simul) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	ft_grab_forks(t_philo *philo)
{
	t_simul	*simul;
	int		my_fork;
	int		other_fork;

	simul = philo->simul;
	my_fork = philo->my_fork;
	other_fork = philo->other_fork;
	if (philo->id == simul->infos.nb_of_philo - 1)
		ft_swap(&my_fork, &other_fork);
	if (ft_grab_first_fork(simul, philo, my_fork) == FAIL)
		return (pthread_mutex_unlock(&simul->forks[my_fork]), FAIL);
	if (simul->infos.nb_of_philo == 1)
	{
		pthread_mutex_unlock(&simul->forks[philo->my_fork]);
		ft_usleep(simul->infos.time_to_die);
		return (FAIL);	
	}
	if (ft_grab_other_fork(simul, philo, other_fork) == FAIL)
		return (ft_drop_forks(philo, my_fork, other_fork), FAIL);
	return (SUCCESS);
}
