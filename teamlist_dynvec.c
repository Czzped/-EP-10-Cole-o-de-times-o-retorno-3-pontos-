#include "teamlist.h"
#include <stdlib.h>

#define TL_INITIAL_CAPACITY 4

struct teamlist {
    Team **teams;
    int size;
    int capacity;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    if (tl == NULL) {
        return NULL;
    }

    tl->capacity = TL_INITIAL_CAPACITY;
    tl->size = 0;
    tl->teams = malloc(tl->capacity * sizeof(Team *));
    if (tl->teams == NULL) {
        free(tl);
        return NULL;
    }

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    if (tl == NULL || t == NULL) {
        return;
    }

    if (tl->size >= tl->capacity) {
        int new_capacity = (tl->capacity == 0) ? TL_INITIAL_CAPACITY : tl->capacity * 2;
        Team **new_teams = realloc(tl->teams, new_capacity * sizeof(Team *));
        if (new_teams == NULL) {
            return;
        }
        tl->teams = new_teams;
        tl->capacity = new_capacity;
    }

    tl->teams[tl->size] = t;
    tl->size++;
}

int tl_size(TeamList *tl) {
    if (tl == NULL) {
        return 0;
    }
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    if (tl == NULL || i < 0 || i >= tl->size) {
        return NULL;
    }
    return tl->teams[i];
}

void tl_free(TeamList *tl) {
    if (tl == NULL) {
        return;
    }

    for (int i = 0; i < tl->size; i++) {
        team_free(tl->teams[i]);
    }

    free(tl->teams);
    free(tl);
}
