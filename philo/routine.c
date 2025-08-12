/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:21:37 by maudiffr          #+#    #+#             */
/*   Updated: 2024/03/01 10:47:50 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_Philo *phi)
{
	pthread_mutex_lock(&phi->var->mutex_eat);
	pthread_mutex_lock(&phi->var->mutex_check);
	if (phi->var->keeper == 1 || phi->var->meals == 0)
	{
		pthread_mutex_unlock(&phi->var->mutex_check);
		pthread_mutex_unlock(&phi->var->mutex_eat);
		put_forks_back(phi);
		return (1);
	}
	else
	{
		gettimeofday(&phi->var->last_meal[phi->id - 1], NULL);
		printf("%ld %d has taken a fork\n", t_diff(&phi->var->start), phi->id);
		printf("%ld %d has taken a fork\n", t_diff(&phi->var->start), phi->id);
		printf("%ld %d is eating\n", t_diff(&phi->var->start), phi->id);
		phi->var->meals--;
	}
	pthread_mutex_unlock(&phi->var->mutex_check);
	pthread_mutex_unlock(&phi->var->mutex_eat);
	ft_usleep(phi->var->t_eat);
	return (0);
}

int	sleeping(t_Philo *phi)
{
	put_forks_back(phi);
	pthread_mutex_lock(&phi->var->mutex_sleep);
	pthread_mutex_lock(&phi->var->mutex_check);
	if (phi->var->keeper == 1 || phi->var->meals == 0)
	{
		pthread_mutex_unlock(&phi->var->mutex_check);
		pthread_mutex_unlock(&phi->var->mutex_sleep);
		return (1);
	}
	else
		printf("%ld %d is sleeping\n", t_diff(&phi->var->start), phi->id);
	pthread_mutex_unlock(&phi->var->mutex_check);
	pthread_mutex_unlock(&phi->var->mutex_sleep);
	ft_usleep(phi->var->t_sleep);
	return (0);
}

int	thinking(t_Philo *phi)
{
	pthread_mutex_lock(&phi->var->mutex_think);
	pthread_mutex_lock(&phi->var->mutex_check);
	if (phi->var->keeper == 1 || phi->var->meals == 0)
	{
		pthread_mutex_unlock(&phi->var->mutex_check);
		pthread_mutex_unlock(&phi->var->mutex_think);
		return (1);
	}
	else
		printf("%ld %d is thinking\n", t_diff(&phi->var->start), phi->id);
	pthread_mutex_unlock(&phi->var->mutex_check);
	pthread_mutex_unlock(&phi->var->mutex_think);
	return (0);
}

void	*routine(t_Philo *phi)
{
	if (phi->var->n_philo == 1)
	{
		ft_usleep(phi->var->t_die);
		return (0);
	}
	if (phi->id % 2 == 0)
		ft_usleep(phi->var->t_eat / 2);
	while (1)
	{
		taking_forks(phi);
		if (eating(phi) == 1)
			return (0);
		if (sleeping(phi) == 1)
			return (0);
		if (thinking(phi) == 1)
			return (0);
	}
	return (0);
}
