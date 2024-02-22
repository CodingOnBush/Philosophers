/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/22 13:15:24 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	pencil;
	pthread_mutex_t	change_someone_died;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meal_count;
	long			last_meal;
	struct s_data	*data;
}					t_philo;

// destroy.c
void				ft_destroy_all_mutex(t_data *data);

// threads.c
int					ft_start_routines(t_philo *philos, t_data *data);
int					ft_join_threads(t_philo *philos, t_data *data);

// init_utils.c
int					ft_init_vars_with_args(t_data *data, int ac, char **av);
int					ft_init_vars(t_data *data);

// init.c
int					ft_init_data_and_philos(t_data *data, t_philo *philos,
						int ac, char **av);

// msg.c
void				ft_print_msg(t_philo *philo, char *msg);

// routine.c
void				*ft_routine(void *arg);

// time.c
long				ft_what_time_is_it(void);
void				ft_wait(long ms);
long				ft_get_current_time(long start_time);

// utils.c
void				ft_check_philos(t_philo *philo);
int					ft_still_alive(t_philo *philo);
int					ft_philo_is_full(t_philo *philo);
int					ft_all_philos_are_full(t_philo *philos);
int					ft_is_philo_alive(t_philo *philo);

#endif