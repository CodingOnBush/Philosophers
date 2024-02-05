/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/05 17:32:48 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	struct s_philo	*philo;
	struct s_env	*env;
}					t_args;

typedef struct s_philo
{
	int				id;
	char			status;
	long			last_meal;
	int				meal_count;
	int				routine_start;
	int				alive;
	pthread_mutex_t	fork_mutex;
	pthread_t		tid;
	struct s_philo	*right;
	struct s_philo	*left;
}					t_philo;

typedef struct s_env
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				end_flag;
	int				meal_count;
	int				meal_goal;
	struct s_philo	*philos;
	long			start_time;
}					t_env;

// 					actions.c
void				*ft_philo_routine(void *arg);
void				ft_start_eating(t_env env, t_philo *philo);
void				ft_start_sleeping(t_env env, t_philo *philo);
void				ft_start_thinking(t_env env, t_philo *philo);

// 					env.c
int					ft_init_env(t_env *env, int ac, char **av);

// 					init.c
int					ft_init_all_mutex(t_env *env);
int					ft_start_all_routines(t_env *env);

// 					check.c
int					ft_check_args(int ac, char **av);

// 					philos.c
t_philo				*ft_create_philos(int nb);
void				ft_print_philos(t_env env);
t_philo				*ft_free_philos(t_philo *philos, int i);

// 					time.c
int					ft_wait(long time);
long				ft_get_current_time(t_env env);

// 					utils.c
char				ft_toggle_status(t_philo *philo);
t_philo				*ft_get_philo(t_env env, int id);
int					ft_isphilo_dead(t_env env, t_philo *philo);

#endif