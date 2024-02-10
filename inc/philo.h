/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/10 11:57:36 by allblue          ###   ########.fr       */
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
	int				global_meals_count;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
}					t_data;

typedef struct s_philo2
{
	int				id;
	pthread_t		thread;
	int				meal_count;
	int				last_meal;
	struct s_data	*data;
}					t_philo2;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				alive;
	int				meal_count;
	int				last_meal;
	int				routine_start;
	pthread_mutex_t	fork_mutex;
	struct s_philo	*right;
	struct s_philo	*left;
	struct s_env	*env;
}					t_philo;

typedef struct s_env
{
	pthread_t		boss;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	int				total_meals;
	int				meal_count;
	long			start_time;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	flag_mutex;
}					t_env;

void				*ft_philo_routine(void *arg);
void				*ft_boss_routine(void *arg);

int					ft_init_everything(t_env *env, int ac, char **av);

t_philo				*ft_create_philos(t_env *env);

long				ft_what_time_is_it(void);
int					ft_wait(long ms);
long				ft_get_current_time(long start_time);

void				ft_free_everything(t_env *env, t_philo *philos);

void				ft_print_msg(t_env *env, int philo_id, char *msg);

int					ft_still_alive(t_philo *philo);

#endif