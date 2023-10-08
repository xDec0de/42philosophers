/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:33:26 by danimart          #+#    #+#             */
/*   Updated: 2023/10/08 19:53:16 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

pthread_mutex_t	*mutex_init(int *errors)
{
	pthread_mutex_t	*mutex;
	int				result;

	mutex = malloc(sizeof(pthread_mutex_t));
	result = pthread_mutex_init(mutex, NULL);
	if (result == 0)
		return (mutex);
	printf(MUTEX_ERR);
	if (errors != NULL)
		*errors += 1;
	return (NULL);
}

void	*mutex_unlock(pthread_mutex_t *mutex, void *res, int destroy)
{
	pthread_mutex_unlock(mutex);
	if (destroy)
	{
		pthread_mutex_destroy(mutex);
		free(mutex);
	}
	return (res);
}

void	*lock_fork(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(philo->m_dead);
	dead = philo->dead;
	pthread_mutex_unlock(philo->m_dead);
	if (dead)
		return (NULL);
	pthread_mutex_lock(philo->m_fork);
	return (philo);
}
