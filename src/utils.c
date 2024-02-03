/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:06:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 18:56:16 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	ft_toggle_status(t_philo *philo)
{
	if (philo->status == 'e')
		philo->status = 's';
	else if (philo->status == 's')
		philo->status = 't';
	else
		philo->status = 'e';
	return (philo->status);
}

t_philo	*ft_get_philo(t_env env, int id)
{
	int	i;

	i = 0;
	if (env.philos == NULL)
		return (NULL);
	while (i < env.nb)
	{
		if (env.philos->id == id)
			return (env.philos);
		env.philos = env.philos->right;
		i++;
	}
	return (NULL);
}

long	ft_get_time(t_env env)
{
	struct timeval	time;
	long			t;

	gettimeofday(&time, NULL);
	t = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (t - env.time_start);
}

void	ft_print_log(t_env env, t_philo *philo)
{
	if (philo == NULL)
		return ;
	if (philo->status == 'e')
		printf("%ld %d is eating\n", ft_get_time(env), philo->id + 1);
	else if (philo->status == 's')
		printf("%ld %d is sleeping\n", ft_get_time(env), philo->id + 1);
	else
		printf("%ld %d is thinking\n", ft_get_time(env), philo->id + 1);
}
