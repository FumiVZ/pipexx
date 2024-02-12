/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:25:31 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/12 15:19:48 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>

int				ft_printf(int fd, const char *format, ...);
long long int	ft_digits(long long int n);
long long int	ft_putstrfd_count(char *str, int fd);
long long int	ft_putcharfd_count(char c, int fd);
long long int	print_pointer(size_t adress);
long long int	ft_putnbrfd_count(long long int n, int fd);
long long int	ft_putx(long long int nbr, char *base, int fd);

#endif
