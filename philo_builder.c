/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:55:03 by danimart          #+#    #+#             */
/*   Updated: 2023/10/06 18:18:24 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

u_int64_t	get_current_ms(t_philo_info *info)
{
	struct timeval	time;
	u_int64_t		current_ms;

	if (gettimeofday(&time, NULL) != 0)
		return ((int) free_info(GET_TIME_ERR, info, NULL));
	current_ms = ((time.tv_sec * (u_int64_t) 1000) + (time.tv_usec / 1000));
	if (info->start_date == 0)
		info->start_date = current_ms;
	return (current_ms - info->start_date);
}

pthread_t	create_philo_thread(t_philo *philo, int *errors)
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

t_philo	*buid_philo(int id)
{
	t_philo	*philo;
	int		errors;

	philo = (t_philo *) malloc(sizeof(t_philo));
	if (philo == NULL)
		return (free_info(MALLOC_ERR, NULL, NULL));
	errors = 0;
	philo->id = id;
	philo->r_fork = 0;
	philo->l_fork = 0;
	philo->state = THINKING;
	philo->meals = 0;
	philo->th_id = create_philo_thread(philo, &errors);
	philo->m_state = mutex_init(&errors);
	philo->m_fork = mutex_init(&errors);
	philo->m_meal = mutex_init(&errors);
	if (errors != 0)
		return (NULL);
	return (philo);
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
		philo->last_meal = get_current_ms(info);
		philo->prog_info = info;
		info->philo_lst[id] = philo;
		id++;
	}
	return (info);
}
