/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:32:07 by lteng             #+#    #+#             */
/*   Updated: 2024/06/23 12:14:43 by lteng            ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (table_init(&table, argv) == -1)
			return (-1);
		threads_init(&table);
		while (1)
		{
			if (end_monitoring(&table))
				break ;
		}
		join_threads(&table);
		free_all(&table);
	}
	else
		error_msg(BY INPUT_ERROR RST);
	return (0);
}
