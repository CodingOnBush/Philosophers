/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 09:59:57 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_env	env;

	env.end = 0;
	if (ft_check_args(ac, av) < 0)
		return (printf("Error\n"));
	env.nb = ft_atoi(av[1]);
	env.die = ft_atoi(av[2]);
	env.eat = ft_atoi(av[3]);
	env.sleep = ft_atoi(av[4]);
	env.forks = env.nb;
	env.philos = ft_create_philos(env.nb);
	if (!env.philos)
		return (printf("Error\n"));
	// ft_print_philo(&env);
	
	// while (!env.end)
	// {
		
	// }
	printf("Letsgooooo\n");
	return (0);
}
