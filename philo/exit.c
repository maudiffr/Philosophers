/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:27:32 by maudiffr          #+#    #+#             */
/*   Updated: 2024/03/01 10:37:39 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_exit(int error)
{
	if (error == 1)
		printf("Incorrect number of arguments.\n");
	else if (error == 2)
		printf("Invalid arguments.\n");
	else
		printf("Malloc failed to allocate memory.\n");
}
