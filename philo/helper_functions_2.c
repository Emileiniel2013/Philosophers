/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:57:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/08/17 20:24:16 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_threads(pthread_t *threads, t_info *philo)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * philo->philo);
	i = 0;
	while (i < philo->philo)
	{
		philos[i].index = i;
		philos[i].info = philo;
		assign_variables(&philos[i]);
		if (philo->philo == 1)
		{
			pthread_create(&threads[0], NULL, philo_solo, &philos[0]);
			pthread_create(&philos->info->checker, NULL, philo_check, philos);
			return (philos);
		}
		pthread_create(&threads[i], NULL, philo_main, &philos[i]);
		i++;
	}
	pthread_create(&philos->info->checker, NULL, philo_check, philos);
	pthread_mutex_lock(&philo->ready_mutex);
	philo->ready = true;
	pthread_mutex_unlock(&philo->ready_mutex);
	return (philos);
}

void	join_threads(pthread_t *threads, t_info *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_lock(&philo->finish_mutex);
	philo->finished = true;
	pthread_mutex_unlock(&philo->finish_mutex);
}

void	ft_usleep(long usecs, t_philo *philo)
{
	long long		start;
	long long		rem;
	struct timeval	time;

	gettimeofday(&time, NULL);
	start = ((time.tv_sec * 1000000) + time.tv_usec);
	while (1)
	{
		if (check_time(philo, &time, start, usecs) == 1)
			break ;
		rem = usecs - (((time.tv_sec * 1000000) + time.tv_usec) - start);
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (1)
			{
				gettimeofday(&time, NULL);
				if (((time.tv_sec * 1000000) + time.tv_usec) - start > usecs)
					break ;
			}
		}
	}
}

void	print_action(int timestamp, char *action, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	if (check_finished(philo->info) != true)
	{
		if (ft_strcmp(action, "fork") == 0)
			printf("%d %d has taken a fork\n", timestamp, philo->index + 1);
		else if (ft_strcmp(action, "eat") == 0)
			printf("%d %d is eating\n", timestamp, philo->index + 1);
		else if (ft_strcmp(action, "sleep") == 0)
			printf("%d %d is sleeping\n", timestamp, philo->index + 1);
		else if (ft_strcmp(action, "think") == 0)
			printf("%d %d is thinking\n", timestamp, philo->index + 1);
		else if (ft_strcmp(action, "die") == 0)
			printf("%d %d died\n", timestamp, philo->index + 1);
	}
	pthread_mutex_unlock(&philo->info->printf_mutex);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
