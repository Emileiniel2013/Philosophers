/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:28:34 by temil-da          #+#    #+#             */
/*   Updated: 2024/08/17 20:29:26 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_variables(t_philo *philo)
{
	philo->forks = 0;
	philo->full = false;
	philo->meals = 0;
	philo->alive = true;
	if ((philo->index) % 2 == 0)
	{
		philo->first_fork = philo->index;
		philo->second_fork = (philo->index + 1) % philo->info->philo;
	}
	else
	{
		philo->first_fork = (philo->index + 1) % philo->info->philo;
		philo->second_fork = philo->index;
	}
}

void	set_last_meal(t_philo *philo, long long start_time)
{
	pthread_mutex_lock(&philo->info->last_meal_mutex);
	philo->last_meal = start_time;
	pthread_mutex_unlock(&philo->info->last_meal_mutex);
}

void	philo_routine(t_philo *philo, struct timeval *time, long long start)
{
	while (check_finished(philo->info) != true)
	{
		philo_eat(philo, time, start);
		if (philo->full == true)
			return ;
		print_action(get_curent_time(time, start), "sleep", philo);
		ft_usleep(philo->info->sleep * 1000, philo);
		philo_think(philo, time, start);
	}
}

void	set_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->finish_mutex);
	philo->info->finished = true;
	pthread_mutex_unlock(&philo->info->finish_mutex);
}

int	check_time(t_philo *philo, struct timeval *time, long long s, long u)
{
	gettimeofday(time, NULL);
	if (((time->tv_sec * 1000000) + time->tv_usec) - s > u \
	|| check_finished(philo->info) == true)
		return (1);
	return (0);
}
