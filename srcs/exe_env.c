# include "myshell.h"

int     main(int ac, char **av, char **ev)
{
    int     index = 0;

    if (ac != 1 || av[1])
    {
        printf("This program don't support arguments\n exiting\n");
        return (1);
    }
    while (ev[index])
        printf("%s\n", ev[index++]);
    return (0);
}