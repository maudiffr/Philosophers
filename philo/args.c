/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:36:22 by maudiffr          #+#    #+#             */
/*   Updated: 2024/03/01 10:23:02 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (result < -2147483648 || result > 2147483647)
		return (0);
	return (result * sign);
}

static	void	convert_args(int argc, char **argv, t_Var *var)
{
	var->n_philo = ft_atoi(argv[1]);
	var->t_die = ft_atoi(argv[2]);
	var->t_eat = ft_atoi(argv[3]);
	var->t_sleep = ft_atoi(argv[4]);
	var->args = argc;
	if (argc == 6)
		var->meals = ft_atoi(argv[5]) * var->n_philo;
	else
		var->meals = -1;
	var->keeper = 0;
}

static	int	ft_valid_arg(const char *str)
{
	int	i;

	i = 0;
	if (ft_atoi(str) == 0)
		return (1);
	while (str[i])
	{
		if (str[i] != 0 && !(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv, t_Var *var)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_valid_arg(argv[i]) == 1)
		{
			ft_exit(2);
			return (1);
		}
		i++;
	}
	convert_args(argc, argv, var);
	return (0);
}
