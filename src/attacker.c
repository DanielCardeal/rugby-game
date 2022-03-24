// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(position_t attacker_position,
                                      Spy defender_spy) {
  // The implemented strategy is very simplistic and works as follows:
  //
  //   1) At the attacker's turn, he tries the first direction in the direction
  //      attempt list.
  //   2) If the movement fail (i.e. the attacker_position hasn't changed), the
  //      attacker tries the next direction in the attempt list.
  //   3) If the movement doesn't fail (i.e. the attacker_position has changed),
  //      the function returns to step 1.
  //
  // Note that, although simple, this strategy should be capable to avoid
  // obstacles and enable the attacker to cross the board, even if not
  // efficiently.
  UNUSED(defender_spy);

  const direction_t dir_attempt_sequence[8] = {
      DIR_DOWN_RIGHT, DIR_RIGHT, DIR_UP_RIGHT,  DIR_UP,
      DIR_UP_LEFT,    DIR_LEFT,  DIR_DOWN_LEFT, DIR_DOWN};

  static position_t last_pos = {0, 0};
  static int last_attempt_idx = 7;

  // Choose new direction to try based on result of the last movement (failed or
  // success)
  last_attempt_idx = equal_positions(last_pos, attacker_position)
                         ? (last_attempt_idx + 1) % 8 // Failed to move
                         : 0;
  const direction_t next_dir = dir_attempt_sequence[last_attempt_idx];

  last_pos = attacker_position;
  return next_dir;
}

/*----------------------------------------------------------------------------*/
