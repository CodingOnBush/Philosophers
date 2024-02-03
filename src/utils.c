/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:06:39 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 10:47:16 by momrane          ###   ########.fr       */
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
