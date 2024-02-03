/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 12:17:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	char			status;
	int				last_meal;
	int				eat_count;
	int				dead_time;
	int				alive;
	int				fork_right;
	int				fork_left;
	pthread_mutex_t	mutex;
	struct s_philo	*right;
	struct s_philo	*left;
}					t_philo;

typedef struct s_env
{
	int				nb;
	int				die;
	int				eat;
	int				sleep;
	int				forks;
	int				end;
	struct s_philo	*philos;
}					t_env;

int					ft_atoi(const char *str);
int					ft_check_args(int ac, char **av);

int					ft_init_env(t_env *env, char **av);

t_philo				*ft_create_philos(int nb);
void				ft_print_philos(t_env env);
t_philo				*ft_free_philos(t_philo *philos, int i);

t_philo				*ft_get_philo(t_env env, int id);

void	ft_start_eating(t_env env, t_philo *philo);
void	ft_start_sleeping(t_env env, t_philo *philo);
void	ft_start_thinking(t_env env, t_philo *philo);

#endif