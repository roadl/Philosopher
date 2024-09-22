/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:02:12 by yojin             #+#    #+#             */
/*   Updated: 2024/08/15 19:40:55 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_end(t_arg *arg, t_philo *philo)
{
	if (access_sema(&arg->finish, 0) \
		|| access_sema(&arg->end_philo, 0) == arg->philo_num)
	{
		access_sema(&arg->finish, 1);
		return (1);
	}
	if (get_time_diff(philo->eat_time) >= arg->die_time)
	{
		philo->state = DIE;
		sem_wait(arg->finish.sema);
		if (arg->finish.value == 0)
			printf("%d %d died\n", \
				get_time_diff(arg->start_time), philo->num + 1);
		arg->finish.value = 1;
		sem_wait(arg->finish.sema);
		return (1);
	}
	return (0);
}

void	*philo_thread(void *info)
{
	int		time_diff;
	t_philo	*philo;
	t_arg	*arg;

	philo = (t_philo *)info;
	arg = philo->arg;
	if (philo->num % 2 == 1)
		usleep(1000);
	print_philo(philo, 4);
	while (1)
	{
		if (is_end(arg, philo))
			break ;
		time_diff = get_time_diff(philo->time);
		if (philo->state == SLEEP && time_diff >= arg->sleep_time)
			wake_up(philo);
		else if (philo->state == THINK)
			try_eat(philo);
		else if (philo->state == EAT && time_diff >= arg->eat_time)
			sleep_philo(arg, philo);
		usleep(200);
	}
	return (0);
}

int	philo(t_arg *arg, t_philo *p, pthread_t *t)
{
	int			i;

	i = -1;
	while (++i < arg->philo_num)
		init_philo(p + i, arg, i);
	i = -1;
	while (++i < arg->philo_num)
		pthread_create(&t[i], NULL, philo_thread, p + i);
	i = -1;
	while (++i < arg->philo_num)
		pthread_join(t[i], NULL);
	destroy_semas(arg);
	free_all(p, t);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg		arg;
	t_philo		*p;
	pthread_t	*t;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: argc must be 5 or 6.\n", STDERR_FILENO);
		return (-1);
	}
	if (!init_arg(argc, argv, &arg))
	{
		ft_putstr_fd("Error: argument must be positive integer", STDERR_FILENO);
		return (-1);
	}
	p = (t_philo *)malloc(sizeof(t_philo) * arg.philo_num);
	t = (pthread_t *)malloc(sizeof(t_philo) * arg.philo_num);
	if (!p || !t || !init_semas(&arg))
	{
		free_all(p, t);
		destroy_semas(&arg);
		return (-1);
	}
	return (philo(&arg, p, t));
}
