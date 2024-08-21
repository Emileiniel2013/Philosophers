/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:41:21 by temil-da          #+#    #+#             */
/*   Updated: 2024/08/19 14:44:54 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info		philo;
	pthread_t	*threads;
	t_philo		*philos;

	if (argc != 5 && argc != 6)
	{
		return (printf("\nUsage: %s <number_of_philosofers> <time_to_die> " \
		"<time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_" \
		"must_eat(OPTIONAL)\n\n", argv[0]), 1);
	}
	init_info(&philo, argv);
	if (argc == 6)
		philo.cycles = ft_atoi(argv[5]);
	if (philo.philo <= 0 || philo.cycles == 0)
		return (1);
	if (init_mutexes(&philo) == 1)
		return (1);
	threads = malloc(sizeof(pthread_t) * philo.philo);
	if (!threads)
		return (free_struct(&philo), 1);
	philos = init_threads(threads, &philo);
	join_threads(threads, &philo);
	pthread_join(philo.checker, NULL);
	return (free_struct(&philo), free(threads), free(philos), 0);
}
