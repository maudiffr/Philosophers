/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:18:38 by maudiffr          #+#    #+#             */
/*   Updated: 2024/03/01 10:59:05 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

/* Represents a single philosopher at the table.
   Stores its ID, thread, left and right forks, and a reference to shared variables. */

typedef struct s_Philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	mutex_lf;
	pthread_mutex_t	*mutex_rf;
	struct s_Var	*var;
}	t_Philo;

/* Stores shared data for the simulation.
   Keeps track of number of philosophers, timing rules, meal counters,
   mutexes for synchronization, start time, and last meal times. */

typedef struct s_Var
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				args;
	int				meals;
	int				keeper;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_sleep;
	pthread_mutex_t	mutex_think;
	pthread_mutex_t	mutex_check;
	struct timeval	start;
	struct timeval	*last_meal;
}	t_Var;

int		init(t_Var *var);
int		check_args(int argc, char **argv, t_Var *var);
int		ft_usleep(size_t time_in_ms);
long	int	t_diff(struct timeval *start);
void	*routine(t_Philo *phi);
void	*surveillance(t_Var *var);
void	taking_forks(t_Philo *phi);
void	put_forks_back(t_Philo *phi);
void	ft_end(t_Var *var, t_Philo *phi);
void	ft_exit(int error);

#endif
