#include "team.h"
#include "teamlist.h"
#include <stdio.h>
#include <string.h>

static int utf8_continuation_bytes(const char *s) {
    int n = 0;
    if (s == NULL) {
        return 0;
    }
    for (const unsigned char *p = (const unsigned char *)s; *p; p++) {
        if ((*p & 0xC0) == 0x80) {
            n++;
        }
    }
    return n;
}

int main(void) {
    TeamList *tl = tl_create();
    if (tl == NULL) {
        return 1;
    }

    FILE *f = fopen("teams.csv", "rt");
    if (f == NULL) {
        tl_free(tl);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') {
            continue;
        }

        int id;
        char name[100];
        if (sscanf(line, "%d,%99[^\r\n]", &id, name) == 2) {
            Team *t = team_create(id, name);
            if (t != NULL) {
                tl_append(tl, t);
            }
        }
    }
    fclose(f);

    printf("ID  Time       V  E  D  GM  GS  S  PG\n");
    int total = tl_size(tl);
    for (int i = 0; i < total; i++) {
        Team *t = tl_get(tl, i);
        if (t == NULL) {
            continue;
        }

        int goal_diff = team_goals_scored(t) - team_goals_conceded(t);
        int points = 3 * team_wins(t) + team_draws(t);

        printf("%-4d%-11s", team_id(t), team_name(t));
        int extra = utf8_continuation_bytes(team_name(t));
        for (int j = 0; j < extra; j++) {
            putchar(' ');
        }
        printf("%-3d%-3d%-3d%-4d%-4d%-3d%d\n",
               team_wins(t), team_draws(t), team_losses(t),
               team_goals_scored(t), team_goals_conceded(t),
               goal_diff, points);
    }

    tl_free(tl);
    return 0;
}
