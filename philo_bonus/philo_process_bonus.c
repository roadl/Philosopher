/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:49:10 by yojin             #+#    #+#             */
/*   Updated: 2024/09/23 03:42:12 by yojin            ###   ########.fr       */
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

void	try_eat(t_philo *philo)
{
	sem_wait(philo->fork->sema);
	print_philo(philo, 1);
	sem_wait(philo->fork->sema);
	print_philo(philo, 1);
	philo->state = EAT;
	gettimeofday(&philo->time, NULL);
	gettimeofday(&philo->eat_time, NULL);
	print_philo(philo, 2);
}

int	sleep_philo(t_arg *arg, t_philo *philo)
{
	sem_post(philo->fork->sema);
	sem_post(philo->fork->sema);
	sem_wait(arg->end_philo.sema);
	if (arg->max_eat != -1)
		philo->eat_count++;
	if (philo->eat_count == arg->max_eat)
		sem_wait(arg->end_philo.sema);
	philo->state = SLEEP;
	gettimeofday(&philo->time, NULL);
	print_philo(philo, 3);
	sem_post(arg->end_philo.sema);
	return (0);
}
