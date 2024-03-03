/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:05:07 by momrane           #+#    #+#             */
/*   Updated: 2024/03/03 20:25:46 by momrane          ###   ########.fr       */
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
	
	pthread_mutex_lock(&simul->forks[philo->my_fork]);
	simul_state = ft_get_simul_state(simul);
	if (simul_state == ALL_ATE || simul_state >= 0)
	{
		pthread_mutex_unlock(&simul->forks[philo->my_fork]);
		return (FAIL);
	}
	ft_print_status(philo, "has taken a fork");
	
	if (simul->infos.nb_of_philo == 1)
	{
		ft_usleep(simul->infos.time_to_die);
		return (FAIL);
	}

	pthread_mutex_lock(&simul->forks[philo->other_fork]);
	simul_state = ft_get_simul_state(simul);
	if (simul_state == ALL_ATE || simul_state >= 0)
	{
		pthread_mutex_unlock(&simul->forks[philo->my_fork]);
		pthread_mutex_unlock(&simul->forks[philo->other_fork]);
		return (FAIL);
	}
	ft_print_status(philo, "has taken a fork");
	
	return (SUCCESS);
}

static void	ft_update_last_meal(t_philo *philo)
{
	t_simul	*simul;

	simul = philo->simul;
	pthread_mutex_lock(&simul->philo_mutex);
	// printf("[%d]Previous last_meal at : %ld\n", philo->id, philo->last_meal - simul->begin);
	philo->last_meal = ft_get_time();
	// printf("[%d]New last_meal at : %ld\n", philo->id, philo->last_meal - simul->begin);
	pthread_mutex_unlock(&simul->philo_mutex);
}

static int	ft_inspector(t_philo *philo, int meal_count)
{
	t_simul	*simul;
	// long	last_meal;
	int		state;

	simul = philo->simul;
	
	pthread_mutex_lock(&simul->simul_mutex);
	state = simul->state;
	pthread_mutex_unlock(&simul->simul_mutex);
	
	if (state >= 0 || state == ALL_ATE)
		return (STOP);
	// pthread_mutex_lock(&simul->philo_mutex);
	// last_meal = philo->last_meal;
	// pthread_mutex_unlock(&simul->philo_mutex);
	if (simul->infos.meal_goal != NO_MEAL_GOAL && meal_count >= simul->infos.meal_goal)
	{
		// printf("philo %d is full\n", philo->id + 1);
		pthread_mutex_lock(&simul->philo_mutex);
		pthread_mutex_lock(&simul->simul_mutex);
		philo->full = YES;
		simul->philo_full++;
		if (simul->philo_full == simul->infos.nb_of_philo)
			simul->state = ALL_ATE;
		pthread_mutex_unlock(&simul->simul_mutex);
		pthread_mutex_unlock(&simul->philo_mutex);
		return (STOP);
	}
	return (CONTINUE);
}

static void	*ft_routine(void *arg)
{
	t_philo		*philo;
	int			meal_count;

	philo = (t_philo *)arg;
	meal_count = 0;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(&philo->simul->philo_mutex);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->simul->philo_mutex);
	while (1)
	{
		if (ft_inspector(philo, meal_count) == STOP)
		{
			// printf("YOOOW\n");
			break ;
		}
		
		if (ft_grab_forks(philo) == FAIL)
			break ;
		if (ft_inspector(philo, meal_count) == STOP)
		{
			// printf("TOTO\n");
			pthread_mutex_unlock(&philo->simul->forks[philo->my_fork]);
			pthread_mutex_unlock(&philo->simul->forks[philo->other_fork]);
			break ;
		}
		ft_print_status(philo, "is eating");
		ft_usleep(philo->simul->infos.time_to_eat);
		
		pthread_mutex_unlock(&philo->simul->forks[philo->my_fork]);
		pthread_mutex_unlock(&philo->simul->forks[philo->other_fork]);
		
		ft_update_last_meal(philo);
		meal_count++;


		if (ft_inspector(philo, meal_count) == STOP)
		{
			// printf("YYOYOOYY\n");
			// printf("YOOOW\n");
			// if (philo->id == 4)
			// 	printf("------------------------------------COUCOU------------------------------------\n");
			break ;
		}

		ft_print_status(philo, "is sleeping");
		ft_usleep(philo->simul->infos.time_to_sleep);
		ft_print_status(philo, "is thinking");
		
		if (ft_inspector(philo, meal_count) == STOP)
		{
			// printf("YOOOW\n");
			break ;
		}

		ft_usleep(1);
	}
	// printf("BYE FROM PHILO %d\n", philo->id + 1);
	// printf("[%d]simul state : %d\n", philo->id, philo->simul->state);
	// printf("last meal at : %ld\n", philo->last_meal - philo->simul->begin);
	// printf("bye from philo %d at %ld\n", philo->id, ft_get_time() - philo->simul->begin);
	// if (routine.state == PHILO_DEAD)
	// {
	// 	pthread_mutex_lock(&philo->simul->simul_mutex);
	// 	philo->simul->state = philo->id;
	// 	pthread_mutex_unlock(&philo->simul->simul_mutex);
	// }
	// else if (routine.state == PHILO_FULL)
	// {
	// 	pthread_mutex_lock(&philo->simul->simul_mutex);
	// 	philo->simul->philo_full++;
	// 	if (philo->simul->philo_full == philo->simul->infos.nb_of_philo)
	// 		philo->simul->state = ALL_ATE;
	// 	pthread_mutex_unlock(&philo->simul->simul_mutex);
	// }
	return (NULL);
}

void	ft_start_simulation(t_simul *simul)
{
	t_philo		*philos;
	int		i;

	philos = simul->philos;
	// pthread_mutex_lock(&simul->philo_mutex);
	// i = 0;
	// while (i < simul->infos.nb_of_philo)
	// 	philos[i++].last_meal = simul->begin;
	// pthread_mutex_unlock(&simul->philo_mutex);
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
