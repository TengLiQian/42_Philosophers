/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:30:36 by lteng             #+#    #+#             */
/*   Updated: 2024/06/29 11:20:10 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Sleep for the specified duration

long	time_in_ms(void)
{
	struct timeval	s_time;
	long			time_millisecond;

	gettimeofday(&s_time, NULL);
	time_millisecond = ((s_time.tv_sec * 1000) + s_time.tv_usec / 1000);
	return (time_millisecond);
}

void	force_sleep(long milliseconds)
{
	long	start;

	start = time_in_ms();
	while ((time_in_ms() - start) < milliseconds)
		usleep(500);
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->fork[i].fork_mutex);
		i++;
	}
	free(table->philo);
	free(table->fork);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->end_mutex);
}
