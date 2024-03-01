/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:48:52 by momrane           #+#    #+#             */
/*   Updated: 2024/03/01 15:40:18 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static int	ft_philo_is_full(t_philo *philo)
// {
// 	t_data	*data;

// 	data = philo->data;
// 	if (data->meal_goal == -1)
// 		return (0);
// 	pthread_mutex_lock(&philo->meal_count_mutex);
// 	if (philo->meal_count == data->meal_goal)
// 	{
// 		pthread_mutex_unlock(&philo->meal_count_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->meal_count_mutex);
// 	return (0);
// }

// static int	ft_check_loop(t_data *data)
// {
// 	pthread_mutex_lock(&data->loop_mutex);
// 	if (data->loop >= 0 || data->loop == -1)
// 	{
// 		pthread_mutex_unlock(&data->loop_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&data->loop_mutex);
// 	return (0);
// }

static int	ft_philo_is_alive(t_philo *philo)
{
	long	last_meal;
	long	current_time;
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	current_time = ft_what_time_is_it();
	if (current_time - last_meal >= data->time_to_die)
		return (0);
	return (1);
}

static void	ft_change_status(t_philo *philo, char new_status)
{
	if (new_status != 'a' || philo->status != 'd' || philo->status != 'f')
		return ;
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = new_status;
	pthread_mutex_unlock(&philo->status_mutex);
}

static char	ft_get_status(t_philo *philo)
{
	char	status;

	pthread_mutex_lock(&philo->status_mutex);
	status = philo->status;
	pthread_mutex_unlock(&philo->status_mutex);
	return (status);
}

static int	ft_philo_should_die(t_philo *philo, long last_meal)
{
	t_data	*data;
	long	current_time;

	data = philo->data;
	current_time = ft_what_time_is_it();
	if (current_time - last_meal >= data->time_to_die)
		return (1);
	return (0);
}

// static void	ft_update_last_meal(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->last_meal_mutex);
// 	philo->last_meal = ft_what_time_is_it();
// 	pthread_mutex_unlock(&philo->last_meal_mutex);
// }

static int	ft_grab_the_two_forks(t_philo *philo)
{
	t_data	*data;
	int		me;
	int		him;

	data = philo->data;
	me = philo->id;
	him = (philo->id + 1) % data->philo_nb;
	if (me == data->philo_nb - 1)
		ft_swap(&me, &him);
	if (pthread_mutex_lock(&(data->forks[me])))
		return (0);
}

static int	ft_grab_first_fork(t_philo *philo)
{
	t_data	*data;
	int		me;
	int		him;

	data = philo->data;
	me = philo->id;
	him = (philo->id + 1) % data->philo_nb;
	if (me == data->philo_nb - 1)
		ft_swap(&me, &him);
	if (pthread_mutex_lock(&(data->forks[me])))
		return (0);
	if (ft_philo_should_die(philo, philo->last_meal))
	{
		pthread_mutex_unlock(&(data->forks[me]));
		return (0);
	}
	ft_print_msg(philo, "has taken a fork");
	return (1);
}

static int	ft_grab_second_fork(t_philo *philo, int my_fork, int r_fork)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_lock(&(data->forks[r_fork])))
	{
		pthread_mutex_unlock(&(data->forks[my_fork]));
		return (0);
	}
	if (ft_philo_should_die(philo, philo->last_meal))
	{
		pthread_mutex_unlock(&(data->forks[r_fork]));
		pthread_mutex_unlock(&(data->forks[my_fork]));
		return (0);
	}
	ft_print_msg(philo, "has taken a fork");
	return (1);
}

static int	ft_grab_fork(t_philo *philo, int fork)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_lock(&(data->forks[fork])))
		return (0);
	if (ft_philo_should_die(philo, philo->last_meal))
	{
		pthread_mutex_unlock(&(data->forks[fork]));
		return (0);
	}
	ft_print_msg(philo, "has taken a fork");
	return (1);
}

static void	ft_drop_the_forks(t_philo *philo, int my_fork, int r_fork)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&(data->forks[my_fork]));
	pthread_mutex_unlock(&(data->forks[r_fork]));
}

static char	*ft_get_flag(t_philo *philo)
{
	t_data	*data;
	char	*flag;

	data = philo->data;
	pthread_mutex_lock(&data->mutex_flag);
	flag = data->flag;
	pthread_mutex_unlock(&data->mutex_flag);
	return (flag);
}

static int	ft_stop_routine(t_philo *philo)
{
	t_data	*data;
	char	*flag;

	data = philo->data;
	flag = ft_get_flag(philo);
	if (flag == "stop" || flag == "all_ate")
		return (1);
	return (0);
}

static void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		meal_count;
	long	last_meal;
	int		my_fork;
	int		r_fork;
	char	status;

	philo = (t_philo *)arg;
	my_fork = philo->id;
	r_fork = (philo->id + 1) % philo->data->philo_nb;
	if (my_fork == philo->data->philo_nb - 1)
		ft_swap(&my_fork, &r_fork);
	
	if (philo->id % 2)
		ft_wait(1);
	
	last_meal = ft_what_time_is_it();
	meal_count = 0;
	status = 'a';
	while (1)
	{
		// check if I am full of meals
		if (philo->data->meal_goal != -1 && meal_count == philo->data->meal_goal)
		{
			status = 'f';
			break;
		}

		// grab my fork
		if (!ft_grab_fork(philo, my_fork))
			break;
		
		// check if I am the only philo
		if (philo->data->philo_nb == 1)
		{
			ft_wait(philo->data->time_to_die);
			ft_change_status(philo, 'd');
			pthread_mutex_unlock(&(philo->data->forks[my_fork]));
			break;
		}
		
		// check if I should die because I waited too long before starting to eat
		if (ft_philo_should_die(philo, last_meal))
		{
			ft_change_status(philo, 'd');
			pthread_mutex_unlock(&(philo->data->forks[my_fork]));
			break;
		}

		// grab the fork next to me
		if (!ft_grab_fork(philo, r_fork))
		{
			pthread_mutex_unlock(&(philo->data->forks[my_fork]));
			break;
		}
		if (ft_philo_should_die(philo, last_meal))
		{
			ft_change_status(philo, 'd');
			ft_drop_the_forks(philo, my_fork, r_fork);
			break;
		}
		ft_print_msg(philo, "is eating");
		ft_wait(philo->data->time_to_eat);
		if (ft_philo_should_die(philo, last_meal))
		{
			ft_change_status(philo, 'd');
			ft_drop_the_forks(philo, my_fork, r_fork);
			break;
		}
		
		last_meal = ft_what_time_is_it();
		
		ft_drop_forks(philo);
		
		if (philo->data->meal_goal != -1)
			meal_count++;
		
		ft_print_msg(philo, "is sleeping");
		ft_wait(philo->data->time_to_sleep);
		ft_print_msg(philo, "is thinking");
		// ft_wait(((philo->data->time_to_die - (philo->data->time_to_eat + philo->data->time_to_sleep)) / 2));
	}
	if (ft_get_status(philo) == 'f')
	{
			
	}
	else if (ft_get_status(philo) == 'd')
	{
		
	}
	return (NULL);
}

void	ft_start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philos[i].thrd, NULL, ft_routine,
				&data->philos[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->philos[i].thrd, NULL))
			return ;
		i++;
	}
}
