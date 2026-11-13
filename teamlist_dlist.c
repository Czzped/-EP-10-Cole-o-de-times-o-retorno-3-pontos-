#include "teamlist.h"
#include <stdlib.h>

typedef struct node Node;

struct node {
    Team *team;
    Node *prev;
    Node *next;
};

struct teamlist {
    Node *first;
    Node *last;
    int size;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));
    if (tl == NULL) {
        return NULL;
    }

    tl->first = NULL;
    tl->last = NULL;
    tl->size = 0;

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    if (tl == NULL || t == NULL) {
        return;
    }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }

    new_node->team = t;
    new_node->next = NULL;
    new_node->prev = tl->last;

    if (tl->last != NULL) {
        tl->last->next = new_node;
    } else {
        tl->first = new_node;
    }

    tl->last = new_node;
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

    Node *curr = tl->first;
    for (int count = 0; count < i && curr != NULL; count++) {
        curr = curr->next;
    }

    return (curr != NULL) ? curr->team : NULL;
}

void tl_free(TeamList *tl) {
    if (tl == NULL) {
        return;
    }

    Node *curr = tl->first;
    while (curr != NULL) {
        Node *next = curr->next;
        team_free(curr->team);
        free(curr);
        curr = next;
    }

    free(tl);
}
