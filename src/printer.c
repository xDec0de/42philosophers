/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:53:04 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/01 21:24:25 by daniema3         ###   ########.fr       */
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

static void	write_unum(unsigned int nb)
{
	char	buffer[10];
	int		i;

	i = 10;
	if (nb == 0)
	{
		write(STDOUT_FILENO, "0", 1);
		return ;
	}
	while (nb > 0)
	{
		i--;
		buffer[i] = '0' + (nb % 10);
		nb /= 10;
	}
	write(STDOUT_FILENO, &buffer[i], 10 - i);
}

void	write_arg(va_list args, char ch)
{
	if (ch == 'u')
		write_unum(va_arg(args, unsigned int));
	else
		write(STDOUT_FILENO, &ch, 1);
}

static void	write_segment(const char *str, size_t start, size_t end)
{
	if (end > start)
		write(STDOUT_FILENO, &str[start], end - start);
}

void	p_printf(const char *str, ...)
{
	va_list			args;
	t_philo_info	*info;
	size_t			i;
	size_t			start;

	info = get_info();
	va_start(args, str);
	pthread_mutex_lock(info->m_print);
	i = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1])
		{
			write_segment(str, start, i);
			i++;
			write_arg(args, str[i]);
			start = ++i;
		}
		else
			i++;
	}
	write_segment(str, start, i);
	pthread_mutex_unlock(info->m_print);
	va_end(args);
}
