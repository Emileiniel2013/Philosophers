/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:41:37 by temil-da          #+#    #+#             */
/*   Updated: 2024/08/17 21:12:41 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_finished(t_info *info)
{
	bool	finished;

	pthread_mutex_lock(&info->finish_mutex);
	finished = info->finished;
	pthread_mutex_unlock(&info->finish_mutex);
	return (finished);
}
