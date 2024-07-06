/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:32:16 by lteng             #+#    #+#             */
/*   Updated: 2024/06/23 14:01:15 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Libraries
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// ANSI Escape Codes
# define BR "\033[1;31m" // Red
# define BY "\033[1;33m" // Yellow
# define RST "\033[0m"   // Reset color

// Error Messages
# define INPUT_ERROR \
	"Incorrect input, please input in the following order:\n\
1) number_of_philosophers\n\
2) time_to_die (milliseconds)\n\
3) time_to_eat (milliseconds)\n\
4) time_to_sleep (milliseconds)\n\
5) number_of_times_each_philosopher_must_eat (optional)\n\
Positive Numbers only"

// Define enum
typedef enum e_status
{
	EATING,
	DIED,
	SLEEPING,
	TAKEN,
	THINKING,
}					t_status;

// Define structs
typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	long			no_of_meals;
	long			last_meal;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		philo_thread;
	pthread_mutex_t	meal_mutex;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			min_meals;
	long			start_time;
	int				end_simulation;
	t_fork			*fork;
	t_philo			*philo;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;

	pthread_t		monitor_thread;
}					t_table;

// Utils
void				error_msg(char *error);
int					ft_num(const char *str);
int					ft_atol(const char *str);
void				print_status(long start_time, t_philo *philo,
						t_status status);

// Utils 2
long				time_in_ms(void);
void				force_sleep(long milliseconds);
void				free_all(t_table *table);

// Init
int					input_init(t_table *table, char *argv[]);
void				fork_init(t_table *table);
void				forks_assignment(t_table *table, int philo_pos);
void				philo_init(t_table *table);
int					table_init(t_table *table, char *argv[]);

// Dinner
void				ft_eat(t_philo *philo);
void				ft_sleep(t_philo *philo);
void				ft_think(t_philo *philo);
void				*start_dinner(void *data);

// Threads
int					threads_init(t_table *table);
int					join_threads(t_table *table);

// Monitor
int					end_monitoring(void *data);
int					is_full(t_table *table);
int					is_dead(t_philo *philo);

#endif
