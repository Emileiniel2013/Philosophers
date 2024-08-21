/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:32:28 by temil-da          #+#    #+#             */
/*   Updated: 2024/08/17 20:16:08 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_info
{
	int				philo;
	int				die;
	int				eat;
	int				sleep;
	int				cycles;
	int				threads_running;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	printf_mutex;
	pthread_t		checker;
	pthread_mutex_t	checker_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	finish_mutex;
	bool			ready;
	bool			finished;
}			t_info;

typedef struct s_philosophers
{
	int				forks;
	int				index;
	int				first_fork;
	int				second_fork;
	bool			alive;
	bool			full;
	int				meals;
	int				last_meal;
	t_info			*info;
}			t_philo;

int		ft_atoi(const char *str);
void	free_struct(t_info *philo);
int		init_mutexes(t_info *philo);
t_philo	*init_threads(pthread_t *threads, t_info *philo);
void	join_threads(pthread_t *threads, t_info *philo);
void	*philo_main(void *arg);
int		get_curent_time(struct timeval *time, int start_time);
void	ft_usleep(long usecs, t_philo *philo);
void	print_action(int timestamp, char *action, t_philo *philo);
void	philo_eat(t_philo *philo, struct timeval *time, int start_time);
int		ft_strcmp(char *s1, char *s2);
void	philo_think(t_philo *philo, struct timeval *time, int start_time);
void	*philo_check(void *arg);
bool	all_threads_running(pthread_mutex_t *mutex, int *threads, int philos);
void	increase_nbr(pthread_mutex_t *mutex, int *nbr);
bool	check_alive(t_philo *philo);
void	hold_up(t_philo *philo, struct timeval *time, int start_time);
void	*philo_solo(void *arg);
void	init_info(t_info *philo, char **argv);
void	assign_variables(t_philo *philo);
void	set_last_meal(t_philo *philo, long long start_time);
void	philo_routine(t_philo *philo, struct timeval *time, long long start);
void	set_finished(t_philo *philo);
// s is start, u is usecs, had to make the line shorter
int		check_time(t_philo *philo, struct timeval *time, long long s, long u);
bool	check_finished(t_info *info);

#endif
