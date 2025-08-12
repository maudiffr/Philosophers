/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keeper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:18:52 by maudiffr          #+#    #+#             */
/*   Updated: 2024/03/01 11:05:39 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 1)
		return (1);
	return ((time.tv_sec * 1000) + (time.tv_usec) / 1000);
}

int	ft_usleep(size_t time_in_ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time_in_ms)
		usleep(500);
	return (0);
}

long	int	t_diff(struct timeval *start)
{
	long int		diff_sec;
	long int		diff_usec;
	struct timeval	current;

	gettimeofday(&current, NULL);
	diff_sec = (current.tv_sec - start->tv_sec) * 1000;
	diff_usec = (current.tv_usec - start->tv_usec) / 1000;
	return (diff_sec + diff_usec);
}

void	*surveillance(t_Var *var)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < var->n_philo)
		{
			pthread_mutex_lock(&var->mutex_check);
			if (var->meals == 0)
			{
				pthread_mutex_unlock(&var->mutex_check);
				return (0);
			}
			if (t_diff(&var->last_meal[i]) > var->t_die)
			{
				var->keeper = 1;
				printf("%ld %d died\n", t_diff(&var->start), i + 1);
				pthread_mutex_unlock(&var->mutex_check);
				return (0);
			}
			pthread_mutex_unlock(&var->mutex_check);
			i++;
		}
	}
	return (0);
}
