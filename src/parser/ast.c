#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON/cJSON.h"
#include "parser/ast.h"

File*
ast_new(const char *name, const char *filename, size_t len)
{
    File *root;
    size_t filename_l, name_l;

    name_l = strlen(name);
    filename_l = strlen(filename);

    if((root = (File*)malloc(sizeof(File) + name_l + 1)) == NULL)
        return NULL;

    (void)strncpy(root->name, name, name_l);
    root->name[name_l] = 0;

    root->expression.term = NULL;
    root->expression.tag = Nothing;
    root->expression.eval = NULL;

    if((root->location = (Location*)malloc(sizeof(Location) + filename_l + 1)) == NULL)
    {
        free(root);
        
        return NULL;
    }

    root->location->start = 0;
    root->location->end = len;

    (void)strncpy(root->location->filename, filename, filename_l);
    root->location->filename[filename_l] = 0;

    return root;
}

File*
ast_from_json(cJSON *json)
{
    File *root;
    cJSON *clocation = cJSON_GetObjectItem(json, "location");
    const char *name = cJSON_GetStringValue(cJSON_GetObjectItem(json, "name"));
    const char *filename = cJSON_GetStringValue(cJSON_GetObjectItem(clocation, "filename"));

    root = ast_new(name, filename, (size_t)cJSON_GetNumberValue(clocation));

    return root;
}

void
json_iter(cJSON *json)
{
    cJSON *node = NULL;

    cJSON_ArrayForEach(node, json)
    {
        char *str = cJSON_Print(node);
        
        printf("%s\n\n", str);
        free(str);
    }
}
