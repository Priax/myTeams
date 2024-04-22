/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** my_utils
*/
#include <stdlib.h>
#include <unistd.h>

int my_strlen(char const *str)
{
    int i = 0;

    if (!str)
        return i;
    while (str[i])
        i++;
    return i;
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
}

void my_putstr_fd(char const *str, int fd)
{
    write(fd, str, my_strlen(str));
}

void my_putnbr_base(int nb, char const *base)
{
    int digit;

    if (base == NULL || *base == '\0') {
        my_putstr("Invalid base.\n");
        return;
    }
    if (nb < 0) {
        my_putchar('-');
        nb *= -1;
    }
    if (nb > 0) {
        digit = nb % my_strlen(base);
        my_putnbr_base(nb / my_strlen(base), base);
        my_putchar(base[digit]);
    }
}
