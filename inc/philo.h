/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/11 13:25:32 by momrane          ###   ########.fr       */
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
	int				nb_philos;// OK
	int				time_to_die;// OK
	int				time_to_eat;// OK
	int				time_to_sleep;// OK
	int				meal_goal;// OK
	int				global_meals_count;// OK
	int				global_meals_goal;
	long			start_time;// OK
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
}					t_data;

typedef struct s_philo2
{
	int				id;
	pthread_t		*thread;
	int				meal_count;
	int				last_meal;
	int				is_dead;
	struct s_data	*data;
	struct s_philo2	*right;
	struct s_philo2	*left;
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

void				*ft_philo_routine2(void *arg);

int					ft_init_everything2(t_data *data, t_philo2 *philos, int ac, char **av);

t_philo2			*ft_create_philos2(t_data *data);

long				ft_what_time_is_it(void);
int					ft_wait(long ms);
long				ft_get_current_time(long start_time);

void				ft_free_everything(t_env *env, t_philo *philos);
void				ft_free_everything2(t_data *data, t_philo2 *philos);

void				ft_print_msg(t_data *data, int philo_id, char *msg);

int					ft_still_alive(t_philo *philo);

#endif