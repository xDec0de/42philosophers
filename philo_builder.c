/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:55:03 by danimart          #+#    #+#             */
/*   Updated: 2023/10/01 13:22:42 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

u_int64_t	get_current_ms(t_philo_info *info)
{
	struct timeval	time;
	u_int64_t		current_ms;

	if (gettimeofday(&time, NULL) != 0)
		return ((int) print_error(GET_TIME_ERR, info, NULL));
	current_ms = ((time.tv_sec * (u_int64_t) 1000) + (time.tv_usec / 1000));
	if (info->start_date == 0)
		info->start_date = current_ms;
	return (current_ms - info->start_date);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	if (get_current_ms(philo->prog_info) - philo->last_interacion >= 10) // This kills the philosopher at 10ms since program execution
		philo->state = DEAD;
	if (philo->state == DEAD)
		return (philo_ptr);
	usleep(100);
	return (philo_routine(philo_ptr));
}

pthread_t	create_philo_thread(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, &philo_routine, philo);
	return (thread);
}

t_philo_info	*build_philosophers(t_philo_info *info)
{
	t_philo	*philo;
	int		id;

	id = 0;
	philo = (t_philo *) malloc(sizeof(t_philo));
	while (id < info->amount)
	{
		philo->prog_info = info;
		philo->id = id;
		philo->fork = FK_NONE;
		philo->state = INACTIVE;
		philo->meals = 0;
		philo->last_interacion = get_current_ms(info);
		philo->th_id = create_philo_thread(philo);
		info->philo_lst[id] = philo;
		id++;
	}
	return (test_philosophers(info));
}
