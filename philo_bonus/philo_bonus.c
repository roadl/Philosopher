/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:02:12 by yojin             #+#    #+#             */
/*   Updated: 2024/09/23 04:38:24 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_thread(void *info)
{
	t_philo	*philo;
	t_arg	*arg;

	philo = info;
	arg = philo->arg;
	while (1)
	{
		if (get_time_diff(philo->eat_time) >= arg->die_time)
		{
			sem_wait(arg->check.sema);
			sem_post(arg->check.sema);
			exit(EXIT_SUCCESS);
		}
		usleep(200);
	}
}

void	philo_process(t_philo *philo)
{
	int			time_diff;
	t_arg		*arg;
	pthread_t	t;

	arg = philo->arg;
	if (pthread_create(&t, NULL, monitor_thread, philo) != 0)
	{
		sem_wait(arg->finish.sema);
		sem_post(arg->check.sema);
		exit(EXIT_FAILURE);
	}
	usleep(philo->num % 2 * 1000);
	print_philo(philo, 4);
	while (1)
	{
		end_check(arg, philo);
		time_diff = get_time_diff(philo->time);
		if (philo->state == SLEEP && time_diff >= arg->sleep_time)
			wake_up(philo);
		else if (philo->state == THINK)
			try_eat(philo);
		else if (philo->state == EAT && time_diff >= arg->eat_time)
			sleep_philo(arg, philo);
		usleep(200);
	}
}

int	create_philo_process(t_philo *p, pid_t *pids, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		while (i >= 0)
			kill(pids[i--], SIGKILL);
		return (0);
	}
	else if (pid == 0)
		philo_process(p + i);
	else
		pids[i] = pid;
	return (1);
}

int	philo(t_arg *arg, t_philo *p, pid_t *pids)
{
	int		i;
	int		status;

	i = -1;
	while (++i < arg->philo_num)
		init_philo(p + i, arg, i);
	i = -1;
	while (++i < arg->philo_num)
		if (!create_philo_process(p, pids, i))
			break ;
	i = -1;
	while (1)
		if (waitpid(-1, &status, 0) <= 0)
			break ;
	destroy_semas(arg);
	free_all(p, pids);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*p;
	pid_t	*p_ids;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: argc must be 5 or 6.\n", STDERR_FILENO);
		return (-1);
	}
	if (!init_arg(argc, argv, &arg))
	{
		ft_putstr_fd("Error: argument must be positive integer\n", \
			STDERR_FILENO);
		return (-1);
	}
	p = (t_philo *)malloc(sizeof(t_philo) * arg.philo_num);
	p_ids = (pid_t *)malloc(sizeof(pid_t) * arg.philo_num);
	if (!p || !p_ids || !init_semas(&arg))
	{
		free_all(p, p_ids);
		destroy_semas(&arg);
		return (-1);
	}
	return (philo(&arg, p, p_ids));
}
