/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:05:07 by momrane           #+#    #+#             */
/*   Updated: 2024/03/04 16:39:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_get_simul_state(t_simul *simul)
{
	int	state;

	pthread_mutex_lock(&simul->simul_mutex);
	state = simul->state;
	pthread_mutex_unlock(&simul->simul_mutex);
	return (state);
}

static int	ft_grab_forks(t_philo *philo)
{
	t_simul	*simul;
	int		simul_state;

	simul = philo->simul;
	if (philo->id ==  simul->infos.nb_of_philo - 1)
	{
		pthread_mutex_lock(&simul->forks[philo->other_fork]);
		ft_print_status(philo, "has taken a fork");
		
		simul_state = ft_get_simul_state(simul);
		if (simul_state == ALL_ATE || simul_state >= 0)
		{
			pthread_mutex_unlock(&simul->forks[philo->other_fork]);
			return (FAIL);
		}
		
		if (simul->infos.nb_of_philo == 1)
		{
			ft_usleep(simul->infos.time_to_die);
			return (FAIL);
		}

		pthread_mutex_lock(&simul->forks[philo->my_fork]);
		ft_print_status(philo, "has taken a fork");
		
		simul_state = ft_get_simul_state(simul);
		if (simul_state == ALL_ATE || simul_state >= 0)
		{
			pthread_mutex_unlock(&simul->forks[philo->my_fork]);
			pthread_mutex_unlock(&simul->forks[philo->other_fork]);
			return (FAIL);
		}
	}
	else
	{
		pthread_mutex_lock(&simul->forks[philo->my_fork]);
		ft_print_status(philo, "has taken a fork");
		
		simul_state = ft_get_simul_state(simul);
		if (simul_state == ALL_ATE || simul_state >= 0)
		{
			pthread_mutex_unlock(&simul->forks[philo->my_fork]);
			return (FAIL);
		}
		
		if (simul->infos.nb_of_philo == 1)
		{
			ft_usleep(simul->infos.time_to_die);
			return (FAIL);
		}

		pthread_mutex_lock(&simul->forks[philo->other_fork]);
		ft_print_status(philo, "has taken a fork");
		
		simul_state = ft_get_simul_state(simul);
		if (simul_state == ALL_ATE || simul_state >= 0)
		{
			pthread_mutex_unlock(&simul->forks[philo->my_fork]);
			pthread_mutex_unlock(&simul->forks[philo->other_fork]);
			return (FAIL);
		}
	}
	
	
	return (SUCCESS);
}

static void	ft_update_last_meal(t_philo *philo, long new_last_meal)
{
	t_simul	*simul;

	simul = philo->simul;
	pthread_mutex_lock(&simul->philo_mutex);
	// printf("[%d]Previous last_meal at : %ld\n", philo->id, philo->last_meal - simul->begin);
	philo->last_meal = new_last_meal;
	// printf("[%d]New last_meal at : %ld\n", philo->id, philo->last_meal - simul->begin);
	pthread_mutex_unlock(&simul->philo_mutex);
}

static int	ft_inspector(t_philo *philo)
{
	t_simul	*simul;
	// long	last_meal;
	int		state;

	simul = philo->simul;

	pthread_mutex_lock(&simul->simul_mutex);
	state = simul->state;
	pthread_mutex_unlock(&simul->simul_mutex);
	if (state >= 0 || state == ALL_ATE)
	{
		printf("state = %d\n", state);
		return (STOP);
	}
	return (CONTINUE);
}

static void	*ft_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->simul->infos.time_to_eat / 10);
	ft_update_last_meal(philo, ft_get_time());
	while (1)
	{
		if (ft_inspector(philo) == STOP)
		{
			// printf("YOOOW\n");
			break ;
		}
		
		if (ft_grab_forks(philo) == FAIL)
			break ;
		if (ft_inspector(philo) == STOP)
		{
			// printf("TOTO\n");
			pthread_mutex_unlock(&philo->simul->forks[philo->my_fork]);
			pthread_mutex_unlock(&philo->simul->forks[philo->other_fork]);
			break ;
		}

		ft_update_last_meal(philo, ft_get_time());

		ft_print_status(philo, "is eating");
		ft_usleep(philo->simul->infos.time_to_eat);
		
		pthread_mutex_unlock(&philo->simul->forks[philo->my_fork]);
		pthread_mutex_unlock(&philo->simul->forks[philo->other_fork]);
		
		// ft_update_last_meal(philo, ft_get_time());
		// meal_count++;
		pthread_mutex_lock(&philo->simul->philo_mutex);
		philo->meal_count = philo->meal_count + 1;
		pthread_mutex_unlock(&philo->simul->philo_mutex);

		if (ft_inspector(philo) == STOP)
		{
			// printf("TOTO\n");
			break ;
		}

		ft_print_status(philo, "is sleeping");
		ft_usleep(philo->simul->infos.time_to_sleep);
		ft_print_status(philo, "is thinking");
		
		if (ft_inspector(philo) == STOP)
		{
			// printf("YOOOW\n");
			break ;
		}

		// usleep(10);
		usleep(((philo->simul->infos.time_to_die - (philo->simul->infos.time_to_eat + philo->simul->infos.time_to_sleep)) / 2) * 1000);
	}
	return (NULL);
}

void	ft_start_simulation(t_simul *simul)
{
	t_philo		*philos;
	int		i;

	philos = simul->philos;
	simul->begin = ft_get_time();
	i = 0;
	while (i < simul->infos.nb_of_philo)
	{
		if (pthread_create(&philos[i].thr, NULL, ft_routine, &philos[i]))
			return ((void)ft_free_simul(simul));
		i++;
	}
	i = 0;
	while (i < simul->infos.nb_of_philo)
	{
		pthread_join(philos[i].thr, NULL);
		i++;
	}
}
