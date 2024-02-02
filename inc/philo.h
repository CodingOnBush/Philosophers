/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/02 13:20:18 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

int	ft_atoi(const char *str);
int	ft_check_args(int ac, char **av);

typedef struct s_philo
{
	int	id;
	int pos;
}		t_philo;

typedef struct s_env
{
	int	someone_died;
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}		t_env;

#endif