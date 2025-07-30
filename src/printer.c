/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:53:04 by daniema3          #+#    #+#             */
/*   Updated: 2025/07/30 19:40:34 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_print(const char *str)
{
	t_philo_info	*info;
	unsigned int	len;

	len = p_strlen(str);
	if (len == 0)
		return ;
	info = get_info();
	pthread_mutex_lock(info->m_print);
	write(STDOUT_FILENO, str, len);
	pthread_mutex_unlock(info->m_print);
}

void	write_str(const char *str)
{
	if (str == NULL)
		write(STDOUT_FILENO, "(null)", 6);
	else
		write(STDOUT_FILENO, str, p_strlen(str));
}

void	write_arg(va_list args, char ch)
{
	if (ch == 's')
		write_str(va_arg(args, char *));
	else
		write(STDOUT_FILENO, &ch, 1);
}

void	p_printf(const char *str, ...)
{
	va_list			args;
	t_philo_info	*info;
	size_t			i;

	if (str == NULL)
		return ;
	i = 0;
	info = get_info();
	va_start(args, str);
	pthread_mutex_lock(info->m_print);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			write_arg(args, str[i]);
		}
		else
			write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
	pthread_mutex_unlock(info->m_print);
	va_end(args);
}
