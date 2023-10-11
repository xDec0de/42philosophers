/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:33:26 by danimart          #+#    #+#             */
/*   Updated: 2023/10/11 17:12:09 by danimart         ###   ########.fr       */
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

int	mutex_unlock(pthread_mutex_t *mutex, int destroy)
{
	int	err;
	int	attempts;

	attempts = 0;
	err = 1;
	while (err != 0 && attempts < 10)
	{
		err = pthread_mutex_unlock(mutex);
		attempts++;
	}
	if (err != 0 || !destroy)
		return (err);
	attempts = 0;
	err = 1;
	while (err != 0 && attempts < 10)
	{
		err = pthread_mutex_destroy(mutex);
		attempts++;
	}
	free(mutex);
	return (err);
}

int	mutex_lock(pthread_mutex_t *mutex)
{
	int	err;
	int	attempts;

	attempts = 0;
	err = 1;
	while (err != 0 && attempts < 10)
	{
		err = pthread_mutex_lock(mutex);
		attempts++;
	}
	return (err);
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
