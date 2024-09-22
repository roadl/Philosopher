/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:49:10 by yojin             #+#    #+#             */
/*   Updated: 2024/09/23 00:20:14 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wake_up(t_philo *philo)
{
	philo->state = THINK;
	gettimeofday(&philo->time, NULL);
	print_philo(philo, 4);
	usleep(200);
}

int	take_fork(t_mutex *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->value == 1)
	{	
		fork->value--;
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

void	put_fork(t_mutex *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->value == 0)
		fork->value++;
	pthread_mutex_unlock(&fork->mutex);
}

void	try_eat(t_philo *philo)
{
	if (philo->num % 2 == 0)
		if (!take_fork(philo->l_fork))
			return ;
	if (!take_fork(philo->r_fork))
	{
		if (philo->num % 2 == 0)
			put_fork(philo->l_fork);
		return ;
	}
	if (philo->num % 2 == 1)
	{
		if (!take_fork(philo->l_fork))
		{
			put_fork(philo->r_fork);
			return ;
		}
	}
	philo->state = EAT;
	gettimeofday(&philo->time, NULL);
	gettimeofday(&philo->eat_time, NULL);
	print_philo(philo, 2);
}

int	sleep_philo(t_arg *arg, t_philo *philo)
{
	put_fork(philo->l_fork);
	put_fork(philo->r_fork);
	pthread_mutex_lock(&arg->end_philo.mutex);
	if (arg->max_eat != -1)
		philo->eat_count++;
	if (philo->eat_count == arg->max_eat)
		arg->end_philo.value++;
	philo->state = SLEEP;
	gettimeofday(&philo->time, NULL);
	print_philo(philo, 3);
	pthread_mutex_unlock(&arg->end_philo.mutex);
	return (0);
}
