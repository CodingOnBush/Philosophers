/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 12:50:35 by momrane          ###   ########.fr       */
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

# define SUCCESS 1
# define FAIL 0

# define CONTINUE 1
# define STOP 0

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

# define ALL_ATE -1
# define NO_MEAL_GOAL -2
# define RUNNING -3

typedef struct s_philo
{
	pthread_t		thrd;
	int				id;
	int				my_fork;
	int				other_fork;
	long			last_meal;
	int				meal_count;
	struct s_simul	*simul;
}					t_philo;

typedef struct s_infos
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
}					t_infos;

typedef struct s_simul
{
	pthread_t		supervisor;
	int				state;
	long			begin;
	struct s_infos	infos;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	pencil;
	pthread_mutex_t	simul_mutex;
	pthread_mutex_t	philo_mutex;
}					t_simul;

/*		FORKS		*/
void				ft_drop_forks(t_philo *philo, int my_fork, int other_fork);
int					ft_grab_forks(t_philo *philo);

/*		FREE		*/
void				*ft_free_simul(t_simul *simul);

/*		INIT_UTILS	*/
int					ft_parse_args(int ac, char **av, t_infos *infos);

/*		INIT		*/
t_simul				*ft_create_simul(int ac, char **av);

/*		ROUTINE		*/
int					ft_controller(t_philo *philo);
void				*ft_routine(void *arg);

/*		SIMULATION	*/
int					ft_start_simulation(t_simul *simul);
void				ft_wait_threads(t_simul *simul);

/*		SUPERVISOR	*/
void				*ft_supervisor(void *arg);

/*		TIME		*/
long				ft_get_time(void);
void				ft_usleep(int time);
int					ft_get_simul_time(t_simul *simul);

/*		UTILS		*/
void				ft_print_status(t_philo *philo, char *status);
void				ft_update_last_meal(t_philo *philo, long new_last_meal);
int					ft_get_simul_state(t_simul *simul);
void				ft_swap(int *a, int *b);

#endif