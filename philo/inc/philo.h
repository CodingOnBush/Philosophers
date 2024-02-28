/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 14:30:20 by momrane          ###   ########.fr       */
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	pencil;
}					t_shared;

typedef struct s_philo
{
	pthread_t		thrd;
	int				id;
	int				meal_count;
	pthread_mutex_t	meal_count_mutex;
	long			last_meal;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	fork;
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
	int				loop;
	pthread_mutex_t	loop_mutex;
	struct s_philo	*philos;
	struct s_shared	shared;
}					t_data;
/* loop -> [-42]: continue | [-1]: stop | [i]: id of the philo who's dead  */

/*		DATA		*/
t_data				*ft_create_data(int ac, char **av);

/*		FORKS		*/
pthread_mutex_t		*ft_create_forks(int size);

/*		FREE		*/
void				ft_free_data(t_data *data);

/*		MSG			*/
void				ft_print_msg(t_philo *philo, char *msg);

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

#endif