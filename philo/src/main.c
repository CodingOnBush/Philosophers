/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:11:02 by momrane           #+#    #+#             */
/*   Updated: 2024/03/05 12:40:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_simul		*simul;

	simul = ft_create_simul(ac, av);
	if (!simul)
		return (1);
	if (ft_start_simulation(simul) == SUCCESS)
		ft_wait_threads(simul);
	ft_free_simul(simul);
	return (0);
}
