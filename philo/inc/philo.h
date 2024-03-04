/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/03/04 11:00:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 1
# define FAIL 0

# define YES 1
# define NO 0

# define CONTINUE 1
# define STOP 0

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

# define ALL_ATE -1
# define NO_MEAL_GOAL -2
# define RUNNING -3
# define PHILO_DEAD -4
# define END_SIMUL -4
# define PHILO_FULL -6
# define SOMEONE_DIED -7

typedef struct s_philo
{
	pthread_t		thr;
	int				id;
	int				my_fork;
	int				other_fork;
	long			last_meal;
	struct s_simul	*simul;
}					t_philo;

typedef struct s_infos
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
}					t_infos;

typedef struct s_simul
{
	int				state;
	long			begin;
	int				philo_full;
	struct s_infos	infos;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simul_mutex;
	pthread_mutex_t	philo_mutex;
}					t_simul;

typedef struct s_routine
{
	int				philo_id;
	int				meal_count;
	long			current_time;
}					t_routine;

void				ft_print_status(t_philo *philo, char *status);

void				*ft_free_simul(t_simul *simul);
t_simul				*ft_create_simul(int ac, char **av);

void				ft_start_simulation(t_simul *simul);

long				ft_get_time(void);
void				ft_usleep(int time);
int					ft_get_simul_time(t_simul *simul);

#endif