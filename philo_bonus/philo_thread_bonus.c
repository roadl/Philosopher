/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:49:10 by yojin             #+#    #+#             */
/*   Updated: 2024/08/15 19:44:53 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wake_up(t_philo *philo)
{
	philo->state = THINK;
	gettimeofday(&philo->time, NULL);
	print_philo(philo, 4);
	usleep(200);
}

int	take_fork(t_philo *philo, t_sema *fork)
{
	sem_wait(fork->sema);
	if (fork->value != 0)
	{
		fork->value--;
		philo->holding_fork++;
		sem_post(fork->sema);
		return (1);
	}
	sem_post(fork->sema);
	return (0);
}

void	put_fork(t_philo *philo, t_sema *fork)
{
	sem_wait(fork->sema);
	fork->value++;
	philo->holding_fork--;
	sem_post(fork->sema);
}

void	try_eat(t_philo *philo)
{
	if (!take_fork(philo, philo->fork))
		return ;
	if (!take_fork(philo, philo->fork))
	{
		put_fork(philo, philo->fork);
		return ;
	}
	if (philo->holding_fork == 2)
	{
		philo->state = EAT;
		gettimeofday(&philo->time, NULL);
		gettimeofday(&philo->eat_time, NULL);
		print_philo(philo, 2);
	}
}

int	sleep_philo(t_arg *arg, t_philo *philo)
{
	put_fork(philo, philo->fork);
	put_fork(philo, philo->fork);
	philo->holding_fork = 0;
	sem_wait(arg->end_philo.sema);
	if (arg->max_eat != -1)
		philo->eat_count++;
	if (philo->eat_count == arg->max_eat)
		arg->end_philo.value++;
	philo->state = SLEEP;
	gettimeofday(&philo->time, NULL);
	print_philo(philo, 3);
	sem_post(arg->end_philo.sema);
	return (0);
}
