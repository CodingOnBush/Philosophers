/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/19 10:53:40 by allblue          ###   ########.fr       */
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
	int				meals_count;
	int				meals_goal;
	long			start_time;
	int				someone_died;
	int				routine_count;
	int				routine_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;	
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meal_count;
	long			last_meal;
	struct s_data	*data;
}					t_philo;

void				ft_check_philos(t_philo *philo);

void				*ft_philo_routine(void *arg);

int					ft_init_data(t_data *data, int ac, char **av);

t_philo				*ft_create_philos(t_data *data);

long				ft_what_time_is_it(void);
int					ft_wait(long ms);
long				ft_get_current_time(long start_time);

void				ft_free_everything(t_data *data, t_philo *philos);

void				ft_print_msg(t_philo *philo, char *msg);

int					ft_still_alive(t_philo *philo);

#endif