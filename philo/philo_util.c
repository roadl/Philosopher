/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:10:20 by yojin             #+#    #+#             */
/*   Updated: 2024/09/23 02:25:23 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	while (*(s + len) != '\0')
		len++;
	if (write(fd, s, len) == -1)
		return (-1);
	return (len);
}

int	get_time_diff(struct timeval last_time)
{
	int				time;
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	time = (cur_time.tv_sec - last_time.tv_sec) * 1000 \
		+ (cur_time.tv_usec - last_time.tv_usec) / 1000;
	return (time);
}

void	free_all(t_arg *arg, t_philo *philo, pthread_t *t)
{
	free(arg->forks);
	free(philo);
	free(t);
}

void	print_philo(t_philo *philo, int type)
{
	t_arg	*arg;

	arg = philo->arg;
	pthread_mutex_lock(&arg->finish.mutex);
	if (arg->finish.value > 0)
	{
		pthread_mutex_unlock(&arg->finish.mutex);
		return ;
	}
	pthread_mutex_lock(&arg->print.mutex);
	printf("%d %d ", get_time_diff(arg->start_time), philo->num + 1);
	if (type == 1)
		printf("has taken a fork\n");
	else if (type == 2)
		printf("is eating\n");
	else if (type == 3)
		printf("is sleeping\n");
	else if (type == 4)
		printf("is thinking\n");
	else if (type == 5)
		printf("died\n");
	pthread_mutex_unlock(&arg->print.mutex);
	pthread_mutex_unlock(&arg->finish.mutex);
}
