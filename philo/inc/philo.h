/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/26 13:08:29 by momrane          ###   ########.fr       */
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

typedef struct s_shared
{
	int				looping;
	int				someone_died;
	pthread_mutex_t	*forks;
	int				*forks_status;
	pthread_mutex_t	finish;
	pthread_mutex_t	pencil;
	pthread_mutex_t	update_looping;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	beginning_mutex;
	pthread_mutex_t	check_philo;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	someone_died_mutex;
}					t_shared;

typedef struct s_philo
{
	pthread_t		thrd;
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

/*		FORKS		*/
pthread_mutex_t		*ft_create_forks(int size);

/*		FREE		*/
void				ft_free_data(t_data *data);

/*		MSG			*/
void				ft_print_msg(t_data *data, int philo_id, char *msg);

/*		PARSING		*/
int					ft_get_arguments(t_data *data, int ac, char **av);

/*		PHILOS		*/
t_philo				*ft_create_philos(t_data *data);

/*		ROUTINE		*/
void				*ft_routine(void *arg);

/*		SHARED		*/
int					ft_init_shared(t_data *data);

/*		THREADS		*/
void				ft_launch_philosophers_threads(t_data *data);
void				ft_wait_for_threads(t_data *data);

/*		TIME		*/
void				ft_wait(long ms);
long				ft_what_time_is_it(void);
long				ft_get_ms_since(long start_time);

/*		UTILS		*/
int					ft_is_philo_alive(t_philo philo);
int					ft_philo_is_full(t_philo philo);
// int					ft_check_looping(t_data *data);
// int					ft_philo_is_dead(long last_meal, t_data *data);
int					ft_philo_is_dead(t_philo *philo);
void				ft_set_last_meal(t_philo *philo);
void				ft_update_last_meal(t_philo *philo);

#endif