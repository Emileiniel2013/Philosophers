/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:45:14 by temil-da          #+#    #+#             */
/*   Updated: 2024/08/17 20:34:15 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_main(void *arg)
{
	t_philo			*philo;
	struct timeval	time;
	long long		start_time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->info->ready_mutex);
	while (philo->info->ready != true)
	{
		pthread_mutex_unlock(&philo->info->ready_mutex);
		usleep(100);
		pthread_mutex_lock(&philo->info->ready_mutex);
	}
	pthread_mutex_unlock(&philo->info->ready_mutex);
	increase_nbr(&philo->info->checker_mutex, &philo->info->threads_running);
	gettimeofday(&time, NULL);
	start_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	set_last_meal(philo, start_time);
	hold_up(philo, &time, start_time);
	philo_routine(philo, &time, start_time);
	return (NULL);
}

void	philo_eat(t_philo *philo, struct timeval *time, int start_time)
{
	int				meal_time;

	pthread_mutex_lock(&philo->info->mutexes[philo->first_fork]);
	print_action(get_curent_time(time, start_time), "fork", philo);
	pthread_mutex_lock(&philo->info->mutexes[philo->second_fork]);
	print_action(get_curent_time(time, start_time), "fork", philo);
	philo->meals++;
	gettimeofday(time, NULL);
	meal_time = ((time->tv_sec * 1000) + (time->tv_usec / 1000));
	pthread_mutex_lock(&philo->info->last_meal_mutex);
	philo->last_meal = meal_time;
	pthread_mutex_unlock(&philo->info->last_meal_mutex);
	print_action(get_curent_time(time, start_time), "eat", philo);
	ft_usleep(philo->info->eat * 1000, philo);
	if (philo->meals == philo->info->cycles)
		philo->full = true;
	pthread_mutex_unlock(&philo->info->mutexes[philo->first_fork]);
	pthread_mutex_unlock(&philo->info->mutexes[philo->second_fork]);
}

void	philo_think(t_philo *philo, struct timeval *time, int start_time)
{
	int	think;

	print_action(get_curent_time(time, start_time), "think", philo);
	if (philo->info->philo % 2 == 0)
		return ;
	think = (philo->info->eat * 2 - philo->info->sleep) * 1000;
	if (think < 0)
		return ;
	else
		ft_usleep(think * 0.5, philo);
}

void	*philo_solo(void *arg)
{
	t_philo			*philo;
	struct timeval	time;
	int				start_time;

	philo = (t_philo *)arg;
	gettimeofday(&time, NULL);
	increase_nbr(&philo->info->checker_mutex, &philo->info->threads_running);
	start_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	pthread_mutex_lock(&philo->info->last_meal_mutex);
	philo->last_meal = start_time;
	pthread_mutex_unlock(&philo->info->last_meal_mutex);
	pthread_mutex_lock(&philo->info->mutexes[0]);
	print_action(get_curent_time(&time, start_time), "fork", philo);
	pthread_mutex_unlock(&philo->info->mutexes[0]);
	while (check_finished(philo->info) != true)
	{
		usleep(100);
	}
	return (NULL);
}
