/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:45:06 by daniema3          #+#    #+#             */
/*   Updated: 2025/07/30 19:44:49 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define MUTEX_INIT_SUCCESS 0

pthread_mutex_t	*mutex_init(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
	{
		printf(MALLOC_ERR);
		return (NULL);
	}
	if (pthread_mutex_init(mutex, NULL) == MUTEX_INIT_SUCCESS)
		return (mutex);
	printf(MUTEX_ERR);
	return (NULL);
}
