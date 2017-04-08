#include <assert.h>
#include <stdlib.h>
#include "project.h"

char *_project_title = NULL;

/*
 * @return project_title if not empty
 */
char *project_get_title()
{
    assert(_project_title != NULL);
    return _project_title;
}

/*
 * Set project title
 */
void project_set_title(char *title)
{
    assert(title != NULL);
    _project_title = title;
}
