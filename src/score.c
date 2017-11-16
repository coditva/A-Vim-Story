#include "datatypes.h"
#include "score.h"

score_t score;

score_t score_get()
{
    return score;
}

score_t score_add(score_t newscore)
{
    score += newscore;
    return score;
}

score_t score_update(score_t newscore)
{
    score = newscore;
    return score;
}
