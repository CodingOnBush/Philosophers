/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 07:56:04 by momrane           #+#    #+#             */
/*   Updated: 2024/03/04 16:16:34 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_parse_args(int ac, char **av, t_infos *infos)
{
	if (ac < 5 || ac > 6)
		return (FAIL);
	infos->nb_of_philo = atoi(av[1]);
	infos->time_to_die = atoi(av[2]);
	infos->time_to_eat = atoi(av[3]);
	infos->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		infos->meal_goal = atoi(av[5]);
	else
		infos->meal_goal = NO_MEAL_GOAL;
	return (SUCCESS);
}

static void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static t_philo	*ft_create_philos(t_simul *simul)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * simul->infos.nb_of_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < simul->infos.nb_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].simul = simul;
		philos[i].meal_count = 0;
		philos[i].my_fork = i;
		philos[i].other_fork = (i + 1) % simul->infos.nb_of_philo;
		// if (i == simul->infos.nb_of_philo - 1 && simul->infos.nb_of_philo != 1)
		// 	ft_swap(&philos[i].my_fork, &philos[i].other_fork);
		philos[i].last_meal = simul->begin;
		i++;
	}
	return (philos);
}

static int	ft_init_all_mutex(t_simul *simul)
{
	if (pthread_mutex_init(&simul->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&simul->simul_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&simul->philo_mutex, NULL))
		return (1);
	return (0);
}

static pthread_mutex_t	*ft_create_forks(t_simul *simul)
{
	pthread_mutex_t	*forks;
	int				i;
	int				nb_of_philo;

	nb_of_philo = simul->infos.nb_of_philo;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_of_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static void	ft_init_simul_vars(t_simul *simul)
{
	simul->begin = ft_get_time();
	simul->philo_full = 0;
	simul->state = RUNNING;
	simul->philos = NULL;
	simul->forks = NULL;
	memset(&simul->print_mutex, 0, sizeof(pthread_mutex_t));
	memset(&simul->simul_mutex, 0, sizeof(pthread_mutex_t));
}

t_simul	*ft_create_simul(int ac, char **av)
{
	t_simul	*simul;

	simul = (t_simul *)malloc(sizeof(t_simul));
	if (!simul)
		return (NULL);
	ft_init_simul_vars(simul);
	if (ft_parse_args(ac, av, &(simul->infos)) == FAIL)
		return (ft_free_simul(simul));
	simul->philos = ft_create_philos(simul);
	if (!simul->philos)
		return (ft_free_simul(simul));
	simul->forks = ft_create_forks(simul);
	if (!simul->forks)
		return (ft_free_simul(simul));
	if (ft_init_all_mutex(simul))
		return (ft_free_simul(simul));
	return (simul);
}
