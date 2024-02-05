/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:07:45 by momrane           #+#    #+#             */
/*   Updated: 2024/02/05 19:45:06 by allblue          ###   ########.fr       */
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
	ft_fill_philos(&env);
	if (ft_init_all_mutex(&env) < 0)
		return (0);
	if (ft_start_all_routines(&env) < 0)
		return (0);
	while (1)
	{
		printf("Meals: %d\n", env.meal_count);
		if (env.meal_goal > 0 && env.meal_count >= env.meal_goal)
			break;
		if (env.end_flag == 1)
			break;
		ft_usleep(1000);
	}
	ft_free_philos(env.philos, env.nb_philos);
	return (0);
}
