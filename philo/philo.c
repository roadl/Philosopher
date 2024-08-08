/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:02:12 by yojin             #+#    #+#             */
/*   Updated: 2024/08/08 17:06:12 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// time_diff 확인
// die 시간 넘었는지 확인, 넘었으면 올리고 끝
// sleep일때는 sleep 시간 넘었으면 think로 바꾸고 last_time 초기화
// think일때는 포크 들 수 있는지 확인, 들 수 있으면 든다 -> mutex 사용법 생각해야됨
// eat일때는 eat 시간 넘었으면 eat count 늘려주고 포크 내려놓고 sleep으로 바꾸고 last_time 초기화
void	*philo_thread(void *info)
{
	int		time_diff;
	t_philo	*philo;
	t_arg	*arg;

	philo = (t_philo *)info;
	arg = philo->arg;
	if (philo->num % 2 == 1)
		usleep(100);
	while (1)
	{
		if (access_mutex(&arg->finish, 0))
			break ;
		time_diff = get_time_diff(philo->time);
		if (time_diff >= arg->die_time)
		{
			philo->state = DIE;
			access_mutex(&arg->finish, 1);
			print_philo(philo, 5);
			break ;
		}
		else if (philo->state == SLEEP && time_diff >= arg->sleep_time)
		{
			philo->state = THINK;
			gettimeofday(&philo->time, NULL);
			// 바로 먹을 수 있으면 EAT이랑 똑같이 처리
			print_philo(philo, 4);
		}
		else if (philo->state == THINK)
		{
			pthread_mutex_lock(&philo->l_fork->mutex);
			print_philo(philo, 1);
			philo->l_fork->value--;
			pthread_mutex_lock(&philo->r_fork->mutex);
			print_philo(philo, 1);
			philo->r_fork->value--;
			philo->state = EAT;
			gettimeofday(&philo->time, NULL);
			print_philo(philo, 2);
		}
		else if (philo->state == EAT && time_diff >= arg->eat_time)
		{
			philo->l_fork->value++;
			philo->r_fork->value++;
			pthread_mutex_unlock(&philo->l_fork->mutex);
			pthread_mutex_unlock(&philo->r_fork->mutex);
			philo->state = SLEEP;
			gettimeofday(&philo->time, NULL);
			print_philo(philo, 3);
		}
		usleep(500);
		//printf("time_diff: %d\n", time_diff);
	}
	return (0);
}

int	philo(t_arg *arg)
{
	int			i;
	int			num;
	t_philo		*p;
	pthread_t	t;

	num = arg->philo_num;
	p = (t_philo *)malloc(sizeof(t_philo) * num);
	arg->forks = (t_mutex *)malloc(sizeof(t_mutex) * num);
	if (!p || !arg->forks)
	{
		free_all(arg, p);
		return (-1);
	}
	i = 0;
	while (i < num)
	{
		init_philo(p + i, arg, i);
		if (init_mutex(arg->forks + i, 1) != 0)
			return (-1);
		pthread_create(&t, NULL, philo_thread, p + (i++));
	}
	pthread_join(t, NULL);
	destroy_mutexes(arg);
	free_all(arg, p);
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: argc must be 5 or 6.\n", STDERR_FILENO);
		return (0);
	}
	if (!init_arg(argc, argv, &arg))
	{
		ft_putstr_fd("Error: argument must be positive integer", STDERR_FILENO);
		return (-1);
	}
	return (philo(&arg));
}
