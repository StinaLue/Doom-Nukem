/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:35 by afonck            #+#    #+#             */
/*   Updated: 2019/07/14 09:13:42 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <wchar.h>

# define HASHTAG  1
# define MINUS  2
# define PLUS  4
# define SPACE  8
# define ZERO  16
# define HH  32
# define H  64
# define L  128
# define LL  256
# define PREC  512
# define BIGL  1024

# define HASH_FLAG flags->state & HASHTAG
# define MIN_FLAG flags->state & MINUS
# define PLUS_FLAG flags->state & PLUS
# define SPACE_FLAG flags->state & SPACE
# define ZERO_FLAG flags->state & ZERO
# define HH_FLAG flags->state & HH
# define H_FLAG flags->state & H
# define L_FLAG flags->state & L
# define LL_FLAG flags->state & LL
# define PREC_FLAG flags->state & PREC
# define BIGL_FLAG flags->state & BIGL

# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define COLORLEN 7
# define RESET "\e[0m"

# define NBFORMATS 14

typedef	struct	s_flags
{
	int	state;
	int	field_width;
	int	precision;
	int	color;
}				t_flags;

typedef struct	s_converter
{
	char		format;
	int			(*fun_ptr)(va_list args, int fd, t_flags *flags);
}				t_converter;

/*
**int		pad_percent(int number, t_flags *flags, int fd);
*/

/*
** FUNCTIONS ////////////////////////////////////////////
*/

/*
** check functions -------------------------------------
*/

void			check_flags(const char **fmt, t_flags *flags);

void			check_field_width(const char **fmt, t_flags *flags);

void			check_precision(const char **fmt, t_flags *flags);

void			check_lmod(const char **fmt, t_flags *flags);

void			check_color(const char **fmt, t_flags *flags);

/*
** flags functions -------------------------------------
*/

t_flags			*init_flags(void);

int				is_flag(char c);

void			activate_flags(t_flags *flags, char c);

int				is_activated(t_flags *flags);

void			flush_flags(t_flags *flags);

/*
** convert functions ------------------------------------
*/

int				convert_float(va_list args, int fd, t_flags *flags);

int				convert_percent(va_list args, int fd, t_flags *flags);

int				convert_string(va_list args, int fd, t_flags *flags);

int				convert_wstring(va_list args, int fd, t_flags *flags);

int				convert_char(va_list args, int fd, t_flags *flags);

int				convert_wchar(va_list args, int fd, t_flags *flags);

int				convert_cap_hex(va_list args, int fd, t_flags *flags);

int				convert_hex(va_list args, int fd, t_flags *flags);

int				convert_pointer(va_list args, int fd, t_flags *flags);

int				convert_int(va_list args, int fd, t_flags *flags);

int				convert_uint(va_list args, int fd, t_flags *flags);

int				convert_oct(va_list args, int fd, t_flags *flags);

int				convert_bin(va_list args, int fd, t_flags *flags);

/*
** pad functions ----------------------------------------
*/

int				pad_float(double number, t_flags *flags, int fd);

int				pad_int(intmax_t number, t_flags *flags, int fd);

int				pad_str(int number, t_flags *flags, int fd);

int				pad_uint(uintmax_t number, t_flags *flags, int fd);

int				pad_hex_prec_mincap(int hexlen, t_flags *flags, int fd, \
				uintmax_t hex);

int				pad_int_prec(intmax_t number, t_flags *flags, int fd);

int				pad_uint_prec(uintmax_t number, t_flags *flags, int fd);

int				pad_oct(int octlen, t_flags *flags, int fd);

int				pad_oct_prec(int octlen, t_flags *flags, int fd);

int				pad_float_prec(double number, int preclen, t_flags *flags, \
				int fd);

/*
** utils functions -------------------------------------
*/

void			flags_spec(t_flags *flags, int nbpad, int fd, intmax_t number);

int				special_hexzero(int fd, t_flags *flags);

int				special_convert_hex(uintmax_t hex, int fd, t_flags *flags, \
				char letter);

void			choose_color(int fd, int color);

void			pad_zero(int nbzero, int fd);

void			pad_space(int nbpad, int fd);

#endif
