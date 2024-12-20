/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:14:33 by marvin            #+#    #+#             */
/*   Updated: 2024/10/20 20:14:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

int	ft_printf(const char *fmt, ...);
int	ft_handle_hex(va_list ap, char fmt);
int	ft_handle_unsigned(va_list ap);
int	ft_handle_pointer(va_list ap);
int	ft_handle_int(va_list ap);
int	ft_handle_char(va_list ap);
int	ft_handle_string(va_list ap);
int	ft_handle_conversion(const char *fmt, va_list ap);
int	ft_putchar(char c);
int	ft_putnbr_base(long long nbr, const char *base);
int	ft_len_putnbr_base(long long nbr, const char *base);
int	ft_putstr(char *s);
int	ft_p(void *ptr);
int	ft_putnbr_pointer(uint64_t nbr, const char *base);

#endif