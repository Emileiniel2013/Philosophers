/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:54:13 by temil-da          #+#    #+#             */
/*   Updated: 2024/08/16 14:33:01 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	posorneg;
	int	number;

	number = 0;
	posorneg = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			posorneg = posorneg * -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		number *= 10;
		number += *str - 48;
		str++;
	}
	return (number * posorneg);
}

void	free_struct(t_info *philo)
{
	int	i;

	i = 0;
	if (philo->mutexes)
	{
		while (i < philo->philo)
			pthread_mutex_destroy(&philo->mutexes[i++]);
		free(philo->mutexes);
	}
	pthread_mutex_destroy(&philo->checker_mutex);
	pthread_mutex_destroy(&philo->printf_mutex);
	pthread_mutex_destroy(&philo->last_meal_mutex);
	pthread_mutex_destroy(&philo->ready_mutex);
	pthread_mutex_destroy(&philo->finish_mutex);
}

int	init_mutexes(t_info *philo)
{
	int	i;

	i = 0;
	philo->mutexes = malloc(sizeof(pthread_mutex_t) * philo->philo);
	if (!philo->mutexes)
	{
		printf("Memory allocation failed! Aborting...\n");
		return (1);
	}
	while (i < philo->philo)
	{
		pthread_mutex_init(&philo->mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->printf_mutex, NULL);
	pthread_mutex_init(&philo->checker_mutex, NULL);
	pthread_mutex_init(&philo->last_meal_mutex, NULL);
	pthread_mutex_init(&philo->ready_mutex, NULL);
	pthread_mutex_init(&philo->finish_mutex, NULL);
	return (0);
}

int	get_curent_time(struct timeval *time, int start_time)
{
	int	curent_time;

	gettimeofday(time, NULL);
	curent_time = (time->tv_sec * 1000) + (time->tv_usec / 1000);
	return (curent_time - start_time);
}

void	init_info(t_info *philo, char **argv)
{
	philo->philo = ft_atoi(argv[1]);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	philo->cycles = -1;
	philo->threads_running = 0;
	philo->ready = false;
	philo->finished = false;
}
