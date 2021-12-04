/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:19:42 by aignacz           #+#    #+#             */
/*   Updated: 2021/06/10 22:25:21 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>

int		ft_printf(const char *str, ...);
void	ft_get_flags(const char *arr, int *i, int *flag);
void	ft_get_width(const char *arr, int *i, int *flag, va_list *list);
void	ft_get_precision(const char *arr, int *i, int *flag, va_list *list);
void	ft_get_conversion(const char *arr, int *i, int *flag);
int		ft_print_handler(const char *str, int *i, va_list *alist, int *flags);
int		ft_print_xXp(va_list *arg_list, int *flags, char c);
int		ft_print_diu(va_list *arg_list, int *flag, char c);
int		ft_print_s(va_list *arg_list, int *flags);
int		ft_print_c(va_list *arg_list, int *flags);
void	ft_print_n(va_list *arg_list, int *flags);
char	*ft_putnbr_base(unsigned long long nbr, char *base, char *pre);
int		ft_padding_nbr(char *str, int *flags);
int		ft_padding_str(char *str, int *flags, int len, char c);
int		ft_putstr(char *str, int len);
char	*ft_print_handle_prec(char *str, int *flags);
char	*ft_putnbr_ll(long long nbr, char *pre);
char	*ft_putnbr_ull(unsigned long long nbr, char *pre);
char	*ft_itoa_ll(long long n);
char	*ft_itoa_ull(unsigned long long n);
int		ft_print_nulls(int *flags);
int		ft_print_nullp(int *flags);

#endif
