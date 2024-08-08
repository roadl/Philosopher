/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:01:09 by yojin             #+#    #+#             */
/*   Updated: 2024/08/08 16:46:28 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_mutex *m, int value)
{
	m->value = value;
	return (pthread_mutex_init(&(m->mutex), NULL));
}

void	destroy_mutexes(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
		pthread_mutex_destroy(&(arg->forks + i++)->mutex);
	pthread_mutex_destroy(&arg->finish.mutex);
	pthread_mutex_destroy(&arg->dead.mutex);
}

int	access_mutex(t_mutex *m, int n)
{
	int	value;

	pthread_mutex_lock(&m->mutex);
	m->value += n;
	value = m->value;
	pthread_mutex_unlock(&m->mutex);
	return (value);
}
