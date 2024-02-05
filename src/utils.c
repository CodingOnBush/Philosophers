/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:06:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/05 17:59:42 by allblue          ###   ########.fr       */
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
	while (i < env.nb_philos)
	{
		if (env.philos->id == id)
			return (env.philos);
		env.philos = env.philos->right;
		i++;
	}
	return (NULL);
}

int	ft_isphilo_dead(t_philo *philo)
{
	long	time;

	time = ft_get_current_time(philo->start_time);
	if (time - philo->last_meal > philo->time_to_die)
	{
		printf("%ld %d died\n", time, philo->id + 1);
		return (1);
	}
	return (0);
}
