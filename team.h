#ifndef TEAM_H
#define TEAM_H

typedef struct team Team;

Team *team_create(int id, const char *name);

int team_id(Team *t);
const char *team_name(Team *t);
int team_wins(Team *t);
int team_draws(Team *t);
int team_losses(Team *t);
int team_goals_scored(Team *t);
int team_goals_conceded(Team *t);

void team_free(Team *t);

#endif
