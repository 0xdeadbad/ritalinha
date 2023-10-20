#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cJSON/cJSON.h"
#include "parser/ast.h"

typedef void(*fn)(void);

int32_t
main(int32_t argc, const char **argv)
{
    const char *filename;
    char *buffer = NULL;
    FILE *f = NULL;
    cJSON *json = NULL;
    File *ast = NULL;

    fn quit = (fn)&&exitlabel;

    quit();

    if(argc != 2)
    {
        (void)fprintf(stderr, "%s\n", "Wrong number of arguments");
        return EXIT_FAILURE;
    }
        
    filename = argv[1];

    if(strlen(filename) == 1 && filename[0] == '-')
    {
        f = stdin;
    }
    else
    {
        struct stat s;
        if(stat(filename, &s) != 0 || (f = fopen(filename, "rt")) == NULL)
        {
            (void)fprintf(stderr, "Error trying opening file %s: %s\n", filename, strerror(errno));

            return EXIT_FAILURE;
        }

        if((buffer = (char*)malloc(s.st_size + 1)) == NULL)
        {
            (void)fprintf(stderr, "Error allocating memory for file contents of %s: %s\n", filename, strerror(errno));
            if(fclose(f) != 0)
                (void)fprintf(stderr, "Error closing file %s: %s\n", filename, strerror(errno));
            free(buffer);
            
            return EXIT_FAILURE;
        }

        (void)fread((void *restrict)buffer, s.st_size, 1, f);
        buffer[s.st_size] = 0;
    }

    if((json = cJSON_Parse(buffer)) == NULL)
    {
        (void)fprintf(stderr, "Error parsing JSON from file %s: %s\n", filename, cJSON_GetErrorPtr());
        if(fclose(f) != 0)
            (void)fprintf(stderr, "Error closing file %s: %s\n", filename, strerror(errno));
        free(buffer);

        return EXIT_FAILURE;
    }

    /* ---- | ----*/

    cJSON *term = cJSON_GetObjectItem(json, "expression");
    json_iter(term);
    (void)ast;

    /* ---- | ----*/

    if(f != NULL && f != stdin)
        if(fclose(f) != 0)
            (void)fprintf(stderr, "Error closing file %s: %s\n", filename, strerror(errno));
    if(buffer != NULL)
        free(buffer);
    if(json != NULL)
        cJSON_Delete(json);


exitlabel:
    return EXIT_SUCCESS;
}
