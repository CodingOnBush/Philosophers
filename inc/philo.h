/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/06 14:58:59 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_save
{
	struct s_philo	*philos;
	struct s_philo	*current_philo;
	struct s_env	*env;
}					t_save;

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
}					t_philo;

typedef struct s_env
{
	int				loop;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	int				total_meals;
	int				meal_count;
	long			start_time;
	struct s_philo	*philos;
	struct s_philo	*selected_philo;
}					t_env;

int					ft_init_everything(t_env *env, int ac, char **av);

t_philo				*ft_create_philos(int nb);

long				ft_what_time_is_it(void);
int					ft_usleep(int time);

void				ft_free_everything(t_env *env);

int					ft_start_routines(t_env *env);

#endif