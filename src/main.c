/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/05 17:20:57 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_env	env;

	if (ft_check_args(ac, av) < 0)
		return (0);
	if (ft_init_env(&env, ac, av) < 0)
		return (0);
	if (ft_init_all_mutex(&env) < 0)
		return (0);
	if (ft_start_all_routines(&env) < 0)
		return (0);
	while (env.end_flag != 1)
	{
		if (env.meal_goal > 0 && env.meal_count >= env.meal_goal)
			env.end_flag = 1;
		usleep(1000);
	}
	
	ft_free_philos(env.philos, env.nb_philos);
	return (0);
}
