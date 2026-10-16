#include "header.h"

void *include_headers(char (*line)[200])
{
    char (*result)[200] = NULL;
    char filename[200];
    char buffer[200];
    char *p;
    int old_cnt = cnt;
    int new_cnt = 0;

    for (int i = 0; i < old_cnt; i++)
    {
        p = line[i];

        // Skip leading spaces and tabs
        while (*p == ' ' || *p == '\t')
            p++;
        if (strncmp(p, "#include", 8) == 0 && (p[8] == ' ' || p[8] == '\t' || p[8] == '"' || p[8] == '<'))
        {
            p += 8;

            while (*p == ' ' || *p == '\t')
                p++;

            // Process only double-quoted headers
            if (*p == '"' &&
                sscanf(p, "\"%199[^\"]\"", filename) == 1)
            {
                FILE *fp = fopen(filename, "r");

                if (fp == NULL)
                {
                    fprintf(stderr,
                            "Cannot open header file: %s\n",
                            filename);

                    // Preserve the original include line
                    result = realloc(
                        result,
                        (new_cnt + 1) * sizeof(*result));

                    if (result == NULL)
                    {
                        free(line);
                        return NULL;
                    }

                    strcpy(result[new_cnt++], line[i]);
                    continue;
                }

                // Copy header contents into result 
                while (fgets(buffer, sizeof(buffer), fp) != NULL)
                {
                    result = realloc(
                        result,
                        (new_cnt + 1) * sizeof(*result));

                    if (result == NULL)
                    {
                        fclose(fp);
                        free(line);
                        return NULL;
                    }

                    strcpy(result[new_cnt++], buffer);
                }

                fclose(fp);
                continue;
            }
        }

        // Keep ordinary source lines unchanged 
        result = realloc(
            result,
            (new_cnt + 1) * sizeof(*result));

        if (result == NULL)
        {
            free(line);
            return NULL;
        }

        strcpy(result[new_cnt++], line[i]);
    }

    free(line);
    cnt = new_cnt;

    return result;
}
