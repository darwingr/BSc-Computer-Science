#ifndef _coordinate_h
#define _coordinate_h

/* Line Segment
 *
 * This struct has to be some of the worst semantics I've ever seen.
 * It was originally defined as a coordinate (mispelled I might add).
 * WTF is this? A coordinate, a vector, a box, a segment?
 * Sure it can be all these things but that does not make it clever.
 *
 * This is dirty code.
 * Code is not just meant for the compiler but for the reader.
 * C can still be a beautiful language with proper semantics and just as fast.
 * Do better than this.
 */
typedef struct line_segment {
    float x0;
    float x1;
    float y0;
    float y1;
} lsegment_t;

/* A struct useful for the global simulation box
 * and to each process managing a subsection of the simulation box.
 */
typedef struct CoordinateBox {
    float width;
    float height;
    // x0 is the left side of the box, x1 is the right side
    // y0 is the bottom side of the box, y1 is the top side
    lsegment_t coord;
} box_t;

/* Particle Coordinate
 *  has a location in the plane (x, y)
 *  has a velocity as two vectors (vx, vy)
 */
typedef struct particle_coordinate {
    float x;
    float y;
    float vx;
    float vy;
} pcoord_t;


/* Particle: particle are defined by physics */
typedef struct particle {
    pcoord_t  pcoord;
    /* Used to simulate mixing of gases */
    int ptype;
    double temp_0;
} particle_t;

#endif  /* _coordinate_h */
