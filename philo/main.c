/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:22:02 by maudiffr          #+#    #+#             */
/*   Updated: 2024/03/01 10:21:39 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_end(t_Var *var, t_Philo *phi)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&var->mutex_eat);
	pthread_mutex_destroy(&var->mutex_sleep);
	pthread_mutex_destroy(&var->mutex_think);
	pthread_mutex_destroy(&phi->var->mutex_check);
	while (i < var->n_philo)
	{
		pthread_mutex_destroy(&phi[i].mutex_lf);
		i++;
	}
	free(var->last_meal);
	free(phi);
}

int	main(int argc, char **argv)
{
	t_Var	var;

	if (argc < 5 || argc > 6)
	{
		ft_exit(1);
		return (1);
	}
	if (check_args(argc, argv, &var) == 1)
		return (1);
	init(&var);
	return (0);
}
