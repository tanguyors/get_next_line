/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torsini <torsini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:15 by torsini           #+#    #+#             */
/*   Updated: 2024/03/13 10:48:30 by torsini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/// Cette fonction remplit le tampon de ligne à partir du fichier ou du reste de la ligne précédente.
static char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
{
    ssize_t	b_read;
    char	*tmp;

    b_read = 1;
    while (b_read > 0)
    {
        // Lire le fichier dans le tampon
        b_read = read(fd, buffer, BUFFER_SIZE);
        if (b_read == -1)
        {
            // En cas d'erreur de lecture, libérer la mémoire et retourner NULL
            free(left_c);
            return (NULL);
        }
        else if (b_read == 0)
            // Si la fin du fichier est atteinte, arrêter la boucle
            break ;
        // Ajouter un caractère de fin de chaîne à la fin du tampon
        buffer[b_read] = 0;
        if (!left_c)
            // Si left_c est NULL, le définir comme une chaîne vide
            left_c = ft_strdup("");
        // Concaténer left_c et buffer et stocker le résultat dans left_c
        tmp = left_c;
        left_c = ft_strjoin(tmp, buffer);
        free(tmp);
        tmp = NULL;
        // Si un caractère de nouvelle ligne est trouvé dans le tampon, arrêter la boucle
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    // Retourne la chaîne de caractères left_c qui contient soit le reste de la ligne précédente, soit le contenu lu du fichier
    return (left_c);
}

// Cette fonction définit la ligne à partir du tampon de ligne.
static char	*_set_line(char *line_buffer)
{
    char	*left_c;
    ssize_t	i;

    i = 0;
    // Trouver l'index du premier caractère de nouvelle ligne ou de fin de chaîne
    while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
        i++;
    if (line_buffer[i] == 0 || line_buffer[1] == 0)
        // Si le premier caractère est un caractère de fin de chaîne ou si la chaîne est vide, retourner NULL
        return (NULL);
    // Créer une sous-chaîne à partir de l'index du premier caractère de nouvelle ligne
    left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
    if (*left_c == 0)
    {
        // Si la sous-chaîne est vide, libérer la mémoire et définir left_c sur NULL
        free(left_c);
        left_c = NULL;
    }
    // Ajouter un caractère de fin de chaîne à la fin de la ligne
    line_buffer[i + 1] = 0;
    // Retourne la chaîne de caractères left_c qui contient le reste de la ligne après le premier caractère de nouvelle ligne
    return (left_c);
}

// Cette fonction renvoie la prochaine ligne à partir du descripteur de fichier.
char	*get_next_line(int fd)
{
    static char	*left_c;
    char		*line;
    char		*buffer;

    // Allouer de la mémoire pour le tampon
    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
    {
        // Si le descripteur de fichier est invalide, la taille du tampon est inférieure ou égale à 0, ou la lecture échoue, libérer la mémoire et retourner NULL
        free(left_c);
        free(buffer);
        left_c = NULL;
        buffer = NULL;
        return (NULL);
    }
    if (!buffer)
        // Si l'allocation de mémoire pour le tampon échoue, retourner NULL
        return (NULL);
    // Remplir le tampon de ligne
    line = _fill_line_buffer(fd, left_c, buffer);
    free(buffer);
    buffer = NULL;
    if (!line)
        // Si le remplissage du tampon de ligne échoue, retourner NULL
        return (NULL);
    // Définir la ligne à partir du tampon de ligne
    left_c = _set_line(line);
    // Retourne la ligne lue à partir du fichier
    return (line);
}

// Cette fonction recherche le caractère c dans la chaîne s et renvoie un pointeur vers la première occurrence de c, ou NULL si c n'est pas trouvé.
char	*ft_strchr(char *s, int c)
{
    unsigned int i;
    char cc;

    cc = (char)c;
    i = 0;
    // Parcourir la chaîne s
    while (s[i])
    {
        // Si le caractère actuel est égal à c, retourner un pointeur vers ce caractère
        if (s[i] == cc)
            return ((char *)&s[i]);
        i++;
    }
    // Si le dernier caractère est égal à c, retourner un pointeur vers ce caractère
    if (s[i] == cc)
        return ((char *)&s[i]);
    // Si c n'est pas trouvé dans s, retourner NULL
    return (NULL);
}
