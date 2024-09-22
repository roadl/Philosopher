/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:10:20 by yojin             #+#    #+#             */
/*   Updated: 2024/08/15 19:44:06 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;
	size_t	len;

	len = 0;
	while (*(s + len) != '\0')
		len++;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (*(s + i))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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

void	free_all(t_philo *philo, pthread_t *t)
{
	free(philo);
	free(t);
}

void	print_philo(t_philo *philo, int type)
{
	t_arg	*arg;

	arg = philo->arg;
	if (access_sema(&arg->finish, 0))
		return ;
	sem_wait(arg->print.sema);
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
	sem_post(arg->print.sema);
}
