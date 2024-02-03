/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 11:51:14 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_env	env;

	if (ft_check_args(ac, av) < 0)
		return (0);
	if (ft_init_env(&env, av) < 0)
		return (0);
	
	// while (!env.end)
	// {
		
	// }
	// printf("Letsgooooo\n");
	
	ft_free_philos(env.philos, env.nb);
	return (0);
}
