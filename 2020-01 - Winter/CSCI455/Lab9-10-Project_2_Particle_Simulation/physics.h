#ifndef _physics_h
#define _physics_h

#include "coordinate.h"

/* the step size use in the integration */
#define STEP_SIZE 1.0

/*
 * Used to move a particle.
 */
int feuler(pcoord_t *a, float time_step);

/*
 * Checks if a particle has exceeded the boundary and returns a momentum.
 *
 * Use this momentum to calculate the pressure.
 */
float wall_collide(pcoord_t *p, lsegment_t wall);

/*
 * Checks if there will be no collision at this time step, returning -1,
 * otherwise it will return when the collision occurs.
 *
 * Can be used as one of input parameter to the routine interact.
 */
float collide(pcoord_t *p1, pcoord_t *p2);

/*
 * The routine interact moves two particles involved in a collision, at a
 * particular time.
 * Do not move these particles again.
 */
void interact(pcoord_t *p1, pcoord_t *p2, float t);

#endif /* _physics_h */
