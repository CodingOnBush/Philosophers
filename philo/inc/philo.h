/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/28 16:29:47 by momrane          ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thrd;
	int				id;
	int				meal_count;
	long			last_meal;
	pthread_mutex_t	meal_count_mutex;
	pthread_mutex_t	last_meal_mutex;
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
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	loop_mutex;
	pthread_mutex_t	pencil;
}					t_data;

/*		DATA		*/
t_data				*ft_create_data(int ac, char **av);

/*		FORKS		*/
pthread_mutex_t		*ft_create_forks(int size);
int					ft_grab_forks(t_philo *philo);
void				ft_drop_forks(t_philo *philo);

/*		ROUTINE		*/
void				ft_start_simulation(t_data *data);

/*		TIME		*/
void				ft_wait(long ms);
long				ft_what_time_is_it(void);
long				ft_get_ms_since(long start_time);

/*		UTILS		*/
void				ft_swap(int *a, int *b);
int					ft_should_i_die(t_data *data, int philo_id);
int					ft_check_death(t_philo *philo);
void				ft_print_msg(t_philo *philo, char *msg);

/*		UTILS2		*/
void				ft_free_data(t_data *data);
int					ft_get_arguments(t_data *data, int ac, char **av);

#endif