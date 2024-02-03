/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 09:23:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	char			status;
	int				last_meal;
	int				eat_count;
	int				dead;
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

t_philo				*ft_create_philos(int nb);
void				ft_print_philo(t_env *env);

#endif