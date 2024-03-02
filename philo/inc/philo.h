/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/03/02 15:57:23 by momrane          ###   ########.fr       */
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
	long			last_meal;
	char			status;
	pthread_mutex_t	meal_count_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	status_mutex;
	struct s_data	*data;
}					t_philo;

typedef struct s_env
{
	int				meal_count;
	int				last_meal;
	int				my_fork;
	int				other_fork;
	char			status;
}					t_env;

/* status : 'a' 'd' 'f' */

typedef struct s_data
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	long			beginning;
	char			*flag;
	pthread_mutex_t	mutex_flag;
	int				loop;
	int				all_ate;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	loop_mutex;
	pthread_mutex_t	all_ate_mutex;
	pthread_mutex_t	pencil;
}					t_data;

/* flag : "someone_died" "all_ate" "continue" */

/*		DATA		*/
t_data				*ft_create_data(int ac, char **av);

/*		FORKS		*/
pthread_mutex_t		*ft_create_forks(int size);
int					ft_grab_forks(t_philo *philo);
void				ft_drop_forks(t_philo *philo);
// void				ft_unlock_forks(t_data *data);

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
int					ft_strcmp(const char *s1, const char *s2);

/*		UTILS2		*/
void				ft_free_data(t_data *data);
int					ft_get_arguments(t_data *data, int ac, char **av);

#endif