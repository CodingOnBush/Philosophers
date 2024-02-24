/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/24 11:50:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_shared
{
	int				someone_died;
	int				philo_full;
	pthread_mutex_t	*forks;
	pthread_mutex_t	pencil;
	pthread_mutex_t	update_flags;
}					t_shared;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meal_count;
	long			last_meal;
	int				alive;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	long			beginning;
	struct s_philo	*philos;
	struct s_shared	shared;
}					t_data;

/*		DATA		*/
t_data				*ft_create_data(int ac, char **av);
int					ft_get_arguments(t_data *data, int ac, char **av);

/*		FREE		*/
void				ft_free_data(t_data *data);

int					ft_init_mutex(t_data *data);
pthread_mutex_t		*ft_create_forks(int size);

// destroy.c

// threads.c
int					ft_start_routines(t_philo *philos, t_data *data);
int					ft_join_threads(t_philo *philos, t_data *data);

// init_utils.c

// init.c

// msg.c
void				ft_print_msg(t_philo philo, char *msg);

// routine.c
void				*ft_routine(void *arg);

// time.c
long				ft_what_time_is_it(void);
void				ft_wait(long ms);
long				ft_get_current_time(long start_time);

// utils.c
int					ft_is_philo_alive(t_philo philo);
int					ft_philo_is_full(t_philo philo);
int					ft_all_philos_are_full(t_philo *philos);
void				ft_check_philos_dead(t_philo *philos);

#endif