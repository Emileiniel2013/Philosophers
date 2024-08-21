/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:06:22 by temil-da          #+#    #+#             */
/*   Updated: 2024/08/17 21:10:48 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_check(void *arg)
{
	t_philo			*philo;
	int				i;
	struct timeval	time;
	int				start_time;

	philo = (t_philo *)arg;
	while (all_threads_running(&philo->info->checker_mutex, \
	&philo->info->threads_running, philo->info->philo) != true)
		;
	gettimeofday(&time, NULL);
	start_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	while (check_finished(philo->info) != true)
	{
		i = -1;
		while (++i < philo->info->philo && check_finished(philo->info) != true)
		{
			if (check_alive(&philo[i]) == false && philo[i].full != true)
			{
				print_action(get_curent_time(&time, start_time), "die", philo);
				set_finished(&philo[i]);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	increase_nbr(pthread_mutex_t *mutex, int *nbr)
{
	pthread_mutex_lock(mutex);
	(*nbr)++;
	pthread_mutex_unlock(mutex);
}

bool	all_threads_running(pthread_mutex_t *mutex, int *threads, int philos)
{
	bool	state;

	state = false;
	pthread_mutex_lock(mutex);
	if (*threads == philos)
		state = true;
	pthread_mutex_unlock(mutex);
	return (state);
}

bool	check_alive(t_philo *philo)
{
	struct timeval	time;
	int				current_time;

	gettimeofday(&time, NULL);
	current_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	pthread_mutex_lock(&philo->info->last_meal_mutex);
	if ((current_time - philo->last_meal) > philo->info->die)
	{
		pthread_mutex_unlock(&philo->info->last_meal_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->info->last_meal_mutex);
	return (true);
}

void	hold_up(t_philo *philo, struct timeval *time, int start_time)
{
	if (philo->info->philo % 2 == 0)
	{
		if (philo->index % 2 == 0)
			ft_usleep(30000, philo);
	}
	else
	{
		if (philo->index % 2 == 0)
			philo_think(philo, time, start_time);
	}
}
