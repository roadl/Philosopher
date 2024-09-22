/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:01:09 by yojin             #+#    #+#             */
/*   Updated: 2024/09/23 00:12:08 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_mutex *m, int value)
{
	m->value = value;
	return (pthread_mutex_init(&(m->mutex), NULL));
}

int	init_mutexes(t_arg *arg)
{
	int	i;

	arg->end_philo.value = -1;
	arg->finish.value = -1;
	arg->print.value = -1;
	if (!arg->forks)
		return (0);
	i = 0;
	while (i < arg->philo_num)
		arg->forks[i++].value = -1;
	i = 0;
	while (i < arg->philo_num)
		if (init_mutex(&arg->forks[i++], 1))
			return (0);
	if (init_mutex(&arg->end_philo, 0) \
		|| init_mutex(&arg->finish, 0) \
		|| init_mutex(&arg->print, 0))
		return (0);
	return (1);
}

void	destroy_mutex(t_mutex *mutex)
{
	if (mutex->value != -1)
		pthread_mutex_destroy(&mutex->mutex);
}

void	destroy_mutexes(t_arg *arg)
{
	int	i;

	i = 0;
	if (arg->forks)
		while (i < arg->philo_num)
			destroy_mutex(arg->forks + i++);
	destroy_mutex(&arg->finish);
	destroy_mutex(&arg->end_philo);
	destroy_mutex(&arg->print);
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
