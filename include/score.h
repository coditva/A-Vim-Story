#ifndef SCORE_H_4BSUNFM1
#define SCORE_H_4BSUNFM1

/**
 * Get the score for the user
 * @return The score
 */
score_t score_get();


/**
 * Add the given amount to the score
 * @param The score to be added
 * @return The updated score
 */
score_t score_add(score_t);


/**
 * Update the score with the given value
 * @param The score to be set
 * @return The updated score
 */
score_t score_update(score_t);


#endif /* end of include guard: SCORE_H_4BSUNFM1 */
