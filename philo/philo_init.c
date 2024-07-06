/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:06:58 by lteng             #+#    #+#             */
/*   Updated: 2024/06/23 12:14:40 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Parameters:
1. number_of_philosophers
2. time_to_die (milliseconds)
3. time_to_eat (milliseconds)
4. time_to_sleep (milliseconds)
5. number_of_times_each_philosopher_must_eat (optional)
*/

int	input_init(t_table *table, char *argv[])
{
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr > 200)
	{
		error_msg(BR "Limit set to 200 Philosophers" RST);
		return (-1);
	}
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
	{
		table->min_meals = ft_atol(argv[5]);
	}
	else
		table->min_meals = -2;
	if (table->time_to_die == -1 || table->philo_nbr == -1
		|| table->time_to_eat == -1 || table->time_to_sleep == -1
		|| table->min_meals == -1)
		return (-1);
	return (0);
}

void	fork_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->fork[i].fork_id = i + 1;
		pthread_mutex_init(&table->fork[i].fork_mutex, NULL);
		i++;
	}
}

void	forks_assignment(t_table *table, int philo_pos)
{
	t_philo	*philo;

	philo = &table->philo[philo_pos];
	if (table->philo_nbr == 1)
	{
		philo->first_fork = &table->fork[philo_pos];
		philo->second_fork = NULL;
	}
	else if (philo->philo_id % 2 == 1)
	{
		philo->first_fork = &table->fork[(philo_pos + 1) % table->philo_nbr];
		philo->second_fork = &table->fork[philo_pos];
	}
	else if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = &table->fork[philo_pos];
		philo->second_fork = &table->fork[(philo_pos + 1) % table->philo_nbr];
	}
}

void	philo_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].no_of_meals = 0;
		table->philo[i].last_meal = table->start_time;
		forks_assignment(table, i);
		table->philo[i].table = table;
		pthread_mutex_init(&table->philo[i].meal_mutex, NULL);
		i++;
	}
}

int	table_init(t_table *table, char *argv[])
{
	if (input_init(table, argv) == -1)
		return (-1);
	table->start_time = time_in_ms();
	table->end_simulation = 0;
	table->philo = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!(table->philo))
		error_msg(BR "Error: Malloc" RST);
	table->fork = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!(table->fork))
		error_msg(BR "Error: Malloc" RST);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->end_mutex, NULL);
	fork_init(table);
	philo_init(table);
	return (0);
}
