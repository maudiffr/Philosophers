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

/* The eating function represents a philosopher taking their turn to eat.
   It first locks the eating and check mutexes to ensure exclusive access
   to shared variables. If the simulation has ended (keeper is set) or
   there are no meals left, the philosopher releases the forks and exits.
   Otherwise, it records the current time as the last meal, prints messages
   for taking forks and eating, decrements the remaining meal counter,
   and then sleeps for the eating duration. */

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

/* The sleeping function models a philosopher resting after eating.
   It releases both forks first, then locks the sleep and check mutexes
   to safely check simulation state. If the simulation has ended, it
   immediately returns. Otherwise, it prints a message indicating the
   philosopher is sleeping and waits for the sleep duration. */

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

/* The thinking function represents a philosopher contemplating
   between meals. It locks the thinking and check mutexes to safely
   access shared variables. If the simulation has ended, it returns
   immediately. Otherwise, it prints a message that the philosopher
   is thinking. */

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

/* The routine function defines the lifecycle of each philosopher thread.
   If there is only one philosopher, it waits until the philosopher dies
   because eating is impossible. For even-numbered philosophers, it
   waits half the eating time at the start to reduce simultaneous fork
   contention. Then, the philosopher continuously loops through taking
   forks, eating, sleeping, and thinking. The loop exits when the
   simulation ends or when all meals are consumed. */

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
