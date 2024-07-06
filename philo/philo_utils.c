/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:04:40 by lteng             #+#    #+#             */
/*   Updated: 2024/06/29 11:41:38 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	error_msg(char *error)
{
	printf("%s\n", error);
	return ;
}

// Function to check all are positive numbers
int	ft_num(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		error_msg(BR "Error: Please input positive numbers" RST);
		return (-1);
	}
	else if (str[i] == '+')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	else
	{
		error_msg(BR "Error: Please input a valid number" RST);
		return (-1);
	}
	return (0);
}

int	ft_atol(const char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	if (ft_num(&str[i]) == -1)
		return (-1);
	while (ft_num(&str[i]) == 0)
		i++;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
	{
		error_msg(BR "Error: Exceed upper limit of INT" RST);
		return (-1);
	}
	return (num);
}

void	print_status(long elapsed_time, t_philo *philo, t_status status)
{
	long	current_time;

	pthread_mutex_lock(&philo->table->print_mutex);
	pthread_mutex_lock(&philo->table->end_mutex);
	current_time = elapsed_time - philo->table->start_time;
	if (status == EATING && philo->table->end_simulation == 0)
		printf("%li %i is eating\n", current_time, philo->philo_id);
	else if (status == SLEEPING && philo->table->end_simulation == 0)
		printf("%li %i is sleeping\n", current_time, philo->philo_id);
	else if (status == TAKEN && philo->table->end_simulation == 0)
		printf("%li %i has taken a fork\n", current_time, philo->philo_id);
	else if (status == THINKING && philo->table->end_simulation == 0)
		printf("%li %i is thinking\n", current_time, philo->philo_id);
	else if (status == DIED)
	{
		philo->table->end_simulation = 1;
		printf("%li %i died\n", current_time, philo->philo_id);
	}
	pthread_mutex_unlock(&philo->table->end_mutex);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
