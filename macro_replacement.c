//macro_replacement.c

#include "header.h"
#include <ctype.h>

#define MAX_MACROS 50

struct Macro
{
    char name[50];
    char value[150];
};

void *replace_macros(char (*line)[200])
{
    struct Macro macro[MAX_MACROS];
    int count = 0;
    char *p, *q;

    // First pass: collect #define directives 
    for (int i = 0; i < cnt; i++)
    {
        p = line[i];

        while (*p == ' ' || *p == '\t')
            p++;

        if (*p != '#')
            continue;

        p++;
        while (*p == ' ' || *p == '\t')
            p++;

        if (strncmp(p, "define", 6) != 0 ||
            (isalnum((unsigned char)p[6]) || p[6] == '_'))
            continue;

        p += 6;

        while (*p == ' ' || *p == '\t')
            p++;

        if (!(isalpha((unsigned char)*p) || *p == '_'))
            continue;

        if (count >= MAX_MACROS)
            break;

        q = macro[count].name;
        while (isalnum((unsigned char)*p) || *p == '_')
        {
            if (q - macro[count].name < 49)
                *q++ = *p;
            p++;
        }
        *q = '\0';

        while (*p == ' ' || *p == '\t')
            p++;

        q = macro[count].value;
        int j = 0;

        while (*p != '\0' && *p != '\n' && j < 149)
            macro[count].value[j++] = *p++;

        while (j > 0 &&
              (macro[count].value[j - 1] == ' ' ||
               macro[count].value[j - 1] == '\t'))
            j--;

        macro[count].value[j] = '\0';

        count++;

        // Mark the #define line for removal 
        line[i][0] = '\0';
    }

    // Second pass: replace macro names 
    for (int i = 0; i < cnt; i++)
    {
        if (line[i][0] == '\0')
            continue;

        char temp[200];
        int j = 0, k = 0;
        int in_string = 0, in_char = 0, escape = 0;

        while (line[i][j] != '\0' && k < 199)
        {
            char ch = line[i][j];

            if (escape)
            {
                temp[k++] = ch;
                escape = 0;
                j++;
                continue;
            }

            if ((in_string || in_char) && ch == '\\')
            {
                temp[k++] = ch;
                escape = 1;
                j++;
                continue;
            }

            if (!in_char && ch == '"')
                in_string = !in_string;
            else if (!in_string && ch == '\'')
                in_char = !in_char;

            if (!in_string && !in_char &&
                (isalpha((unsigned char)ch) || ch == '_'))
            {
                int start = j;
                char word[200];
                int n = 0;

                while (isalnum((unsigned char)line[i][j]) ||
                       line[i][j] == '_')
                {
                    if (n < 199)
                        word[n++] = line[i][j];
                    j++;
                }
                word[n] = '\0';

                int found = 0;

                for (int m = 0; m < count; m++)
                {
                    if (strcmp(word, macro[m].name) == 0)
                    {
                        int v = 0;

                        while (macro[m].value[v] != '\0' &&
                               k < 199)
                            temp[k++] = macro[m].value[v++];

                        found = 1;
                        break;
                    }
                }

                if (!found)
                {
                    for (int x = start; x < j && k < 199; x++)
                        temp[k++] = line[i][x];
                }
            }
            else
            {
                temp[k++] = line[i][j++];
            }
        }

        temp[k] = '\0';
        strcpy(line[i], temp);
    }

    return line;
}

