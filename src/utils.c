/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:49:12 by momrane           #+#    #+#             */
/*   Updated: 2024/02/07 08:16:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
