/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:30:25 by maudiffr          #+#    #+#             */
/*   Updated: 2024/02/27 11:47:24 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Locks both forks for the philosopher:
   first the left fork (own mutex),
   then the right fork (neighbor's left fork). */

void	taking_forks(t_Philo *phi)
{
	pthread_mutex_lock(&phi->mutex_lf);
	pthread_mutex_lock(phi->mutex_rf);
}

/* Unlocks both forks after eating,
   first the right fork, then the left fork. */

void	put_forks_back(t_Philo *phi)
{
	pthread_mutex_unlock(phi->mutex_rf);
	pthread_mutex_unlock(&phi->mutex_lf);
}
