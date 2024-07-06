/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:41:07 by lteng             #+#    #+#             */
/*   Updated: 2024/07/06 15:37:33 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	print_status(time_in_ms(), philo, TAKEN);
	if (philo->table->philo_nbr == 1)
	{
		pthread_mutex_unlock(&philo->first_fork->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->second_fork->fork_mutex);
	print_status(time_in_ms(), philo, TAKEN);
	pthread_mutex_lock(&philo->meal_mutex);
	print_status(time_in_ms(), philo, EATING);
	philo->no_of_meals += 1;
	philo->last_meal = time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	force_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
}

void	ft_sleep(t_philo *philo)
{
	print_status(time_in_ms(), philo, SLEEPING);
	force_sleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	print_status(time_in_ms(), philo, THINKING);
	if (philo->table->philo_nbr % 2 == 1)
		return ;
	else if (philo->table->philo_nbr % 2 == 0)
		force_sleep(1);
}

void	*start_dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id % 2 == 0)
		force_sleep(1);
	while (1)
	{
		pthread_mutex_lock(&philo->table->end_mutex);
		if (philo->table->end_simulation == 1)
		{
			pthread_mutex_unlock(&philo->table->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->end_mutex);
		ft_eat(philo);
		if (philo->table->philo_nbr == 1)
			break ;
		else if (philo->table->philo_nbr > 1)
		{
			ft_sleep(philo);
			ft_think(philo);
		}
	}
	return (NULL);
}
