/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:05:41 by lteng             #+#    #+#             */
/*   Updated: 2024/06/18 22:59:43 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philo[i].philo_thread, NULL, start_dinner,
				&table->philo[i]))
			return (error_msg(BR "Error Creating Philo Thread" RST), 1);
		i++;
	}
	return (0);
}

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philo[i].philo_thread, NULL);
		i++;
	}
	return (0);
}
