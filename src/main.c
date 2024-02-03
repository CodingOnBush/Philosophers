/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/03 19:02:51 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_start_routine(t_env env)
{
	t_philo	*philos;

	philos = env.philos;
	while (env.end == 0)
	{
		ft_grab_forks(philos);
		ft_render_forks(env, philos);
		ft_start_eating(env, philos);
		ft_start_sleeping(env, philos);
		ft_start_thinking(env, philos);
		philos = philos->right;
	}
}

int	main(int ac, char **av)
{
	t_env	env;

	if (ft_check_args(ac, av) < 0)
		return (0);
	if (ft_init_env(&env, av) < 0)
		return (0);
	ft_start_routine(env);
	// printf("Letsgooooo\n");
	ft_free_philos(env.philos, env.nb);
	return (0);
}
