/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:07:37 by lteng             #+#    #+#             */
/*   Updated: 2024/06/29 11:35:38 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_table *table)
{
	int	all_full;
	int	i;

	all_full = 1;
	i = 0;
	if (table->min_meals == -1 || table->min_meals == -2)
		return (0);
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philo[i].meal_mutex);
		if (table->min_meals != -1 && table->min_meals != -2
			&& table->philo[i].no_of_meals < table->min_meals)
			all_full = 0;
		pthread_mutex_unlock(&table->philo[i].meal_mutex);
		i++;
	}
	if (all_full == 1)
	{
		pthread_mutex_lock(&table->end_mutex);
		table->end_simulation = 1;
		pthread_mutex_unlock(&table->end_mutex);
		return (1);
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (time_in_ms() - philo->last_meal > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->end_mutex);
		philo->table->end_simulation = 1;
		pthread_mutex_unlock(&philo->table->end_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		print_status(time_in_ms(), philo, DIED);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	end_monitoring(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->end_mutex);
		if (table->end_simulation == 1)
		{
			pthread_mutex_unlock(&table->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->end_mutex);
		if (is_dead(&table->philo[i]) || is_full(table))
			return (1);
		i++;
	}
	return (0);
}
