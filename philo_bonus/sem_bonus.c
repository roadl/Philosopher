/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:01:09 by yojin             #+#    #+#             */
/*   Updated: 2024/08/15 19:46:47 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sema(t_sema *m, const char *name, int value, int count)
{
	m->name = ft_strdup(name);
	if (!m->name)
		return (1);
	m->value = value;
	m->sema = sem_open(name, O_CREAT, count);
	if (!m->sema)
		return (1);
	return (0);
}

int	init_semas(t_arg *arg)
{
	int	i;

	i = 0;
	arg->forks.value = -1;
	arg->end_philo.value = -1;
	arg->finish.value = -1;
	arg->print.value = -1;
	i = 0;
	if (init_sema(&arg->end_philo, "end_philo", 0, 1) \
		|| init_sema(&arg->finish, "finish", 0, 1) \
		|| init_sema(&arg->print, "print", 0, 1) \
		|| init_sema(&arg->forks, "forks", arg->philo_num, arg->philo_num))
		return (0);
	return (1);
}

void	destroy_sema(t_sema *sema)
{
	if (sema->value != -1)
	{
		sem_unlink(sema->name);
		free(sema->name);
	}
}

void	destroy_semas(t_arg *arg)
{
	int	i;

	i = 0;
	destroy_sema(&arg->forks);
	destroy_sema(&arg->finish);
	destroy_sema(&arg->end_philo);
	destroy_sema(&arg->print);
}

int	access_sema(t_sema *t, int n)
{
	int	value;

	sem_wait(t->sema);
	t->value += n;
	value = t->value;
	sem_post(t->sema);
	return (value);
}
