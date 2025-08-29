/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:08:56 by maudiffr          #+#    #+#             */
/*   Updated: 2024/03/01 10:36:52 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Initializes the main mutexes used to protect shared resources:
   eat, sleep, think, and a global check mutex. */

static	void	ft_mutex_init(t_Var *var)
{
	pthread_mutex_init(&var->mutex_eat, NULL);
	pthread_mutex_init(&var->mutex_sleep, NULL);
	pthread_mutex_init(&var->mutex_think, NULL);
	pthread_mutex_init(&var->mutex_check, NULL);
}

/* Thread entry point.
   If the ID corresponds to the extra monitoring thread,
   it launches the surveillance function.
   Otherwise, it starts the philosopher routine. */

static	void	*distrib(void *arg)
{
	t_Philo	*phi;

	phi = (t_Philo *)arg;
	if (phi->id == phi->var->n_philo + 1)
		surveillance(phi->var);
	else
		routine(phi);
	return (0);
}

/* Allocates memory for tracking each philosopher's last meal.
   Initializes the timestamps and sets up mutexes.
   Returns 1 on failure, 0 on success. */

static	int	ft_malloc(t_Var *var)
{
	int	i;

	i = 0;
	var->last_meal = malloc(sizeof(struct timeval) * var->n_philo);
	if (var->last_meal == NULL)
	{
		ft_exit(3);
		return (1);
	}
	gettimeofday(&var->start, NULL);
	while (i < var->n_philo)
	{
		gettimeofday(&var->last_meal[i], NULL);
		i++;
	}
	ft_mutex_init(var);
	return (0);
}

/* Initializes philosopher structures.
   Each philosopher gets an ID, a pointer to the shared variables,
   and a left fork (own mutex).
   The right fork is the left fork of the next philosopher,
   forming a circular arrangement. */

static	void	ft_forks_init(t_Philo *philo, t_Var *var)
{
	int	i;

	i = 0;
	while (i < var->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].var = var;
		pthread_mutex_init(&philo[i].mutex_lf, NULL);
		if (i == var->n_philo - 1)
			philo[i].mutex_rf = &philo[0].mutex_lf;
		else
			philo[i].mutex_rf = &philo[i + 1].mutex_lf;
		i++;
	}
	philo[i].id = i + 1;
	philo[i].var = var;
}

/* Main initialization routine.
   Allocates memory, sets up philosophers and forks,
   creates one thread per philosopher plus an extra surveillance thread,
   and waits for all threads to finish before cleanup. */

int	init(t_Var *var)
{
	int		i;
	t_Philo	*philo;

	i = 0;
	if (ft_malloc(var) == 1)
		return (1);
	philo = malloc(sizeof(t_Philo) * (var->n_philo + 1));
	if (philo == NULL)
		return (1);
	ft_forks_init(philo, var);
	while (i < var->n_philo + 1)
	{
		if (pthread_create(&philo[i].thread, NULL, distrib, &philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < var->n_philo + 1)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (1);
		i++;
	}
	ft_end(var, philo);
	return (0);
}
