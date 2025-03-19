/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:55:03 by danimart          #+#    #+#             */
/*   Updated: 2023/10/17 18:01:26 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo	*buid_philo(int id)
{
	t_philo	*philo;
	int		errors;

	philo = (t_philo *) malloc(sizeof(t_philo));
	if (philo == NULL)
		return (free_info(MALLOC_ERR, NULL, NULL));
	errors = 0;
	philo->id = id + 1;
	philo->ended = 0;
	philo->meals = 0;
	philo->last_meal = 0;
	philo->ready = 0;
	philo->m_ended = mutex_init(&errors);
	philo->m_fork = mutex_init(&errors);
	philo->m_meal = mutex_init(&errors);
	philo->m_ready = mutex_init(&errors);
	if (errors != 0)
		return (NULL);
	return (philo);
}

pthread_t	start_thread(t_philo *philo, int *errors)
{
	pthread_t	thread;
	int			result;

	result = pthread_create(&thread, NULL, &philo_routine, philo);
	if (result == 0)
		return (thread);
	printf(THREAD_ERR);
	if (errors != NULL)
		*errors += 1;
	return (thread);
}

t_philo_info	*create_threads(t_philo_info *info)
{
	int		id;
	int		errors;
	t_philo	*philo;

	id = 0;
	errors = 0;
	while (id < info->amount || errors != 0)
	{
		philo = info->philo_lst[id];
		philo->th_id = start_thread(philo, &errors);
		id++;
	}
	if (errors != 0)
		return (NULL);
	return (info);
}

void	await_prog_ready(t_philo_info *info)
{
	int	ready;
	int	id;

	ready = 0;
	while (ready != info->amount)
	{
		id = 0;
		ready = 0;
		while (id < info->amount)
		{
			mutex_lock(info->philo_lst[id]->m_ready);
			ready += info->philo_lst[id]->ready;
			mutex_unlock(info->philo_lst[id]->m_ready, 0);
			id++;
		}
	}
}

t_philo_info	*build_philosophers(t_philo_info *info)
{
	t_philo	*philo;
	int		id;

	id = 0;
	while (id < info->amount)
	{
		philo = buid_philo(id);
		if (philo == NULL)
			return (free_info(NULL, info, NULL));
		philo->prog_info = info;
		info->philo_lst[id] = philo;
		id++;
	}
	create_threads(info);
	await_prog_ready(info);
	info->start_date = get_current_time(info);
	mutex_lock(info->m_ready);
	info->ready = 1;
	mutex_unlock(info->m_ready, 0);
	return (info);
}
