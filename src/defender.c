// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

// Enums
enum { UPWARD = -1, DOWNWARD = 1 };

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

int invert_mov_direction(int direction);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(position_t defender_position,
                                      Spy attacker_spy) {
  // The implemented strategy just move the defender upward and downward at the
  // starting column.
  UNUSED(attacker_spy);

  const direction_t upward_attempt_sequence[3] = {
      DIR_UP,
      DIR_UP_LEFT,
      DIR_UP_RIGHT,
  };
  const direction_t downward_attempt_sequence[3] = {
      DIR_DOWN,
      DIR_DOWN_RIGHT,
      DIR_DOWN_LEFT,
  };

  static position_t last_pos = {0, 0};
  static int last_attempt_idx = 0;
  static int mov_direction = UPWARD;

  // Choose new direction to try based on result of the last movement (failed or
  // success)
  last_attempt_idx = equal_positions(last_pos, defender_position)
                         ? last_attempt_idx + 1 // Failed to move
                         : 0;

  // No more ways to move to this direction
  if (last_attempt_idx == 3) {
    mov_direction = invert_mov_direction(mov_direction);
    last_attempt_idx = 0;
  }

  const direction_t next_dir =
      mov_direction == UPWARD ? upward_attempt_sequence[last_attempt_idx]
                              : downward_attempt_sequence[last_attempt_idx];

  last_pos = defender_position;
  return next_dir;
}

/*----------------------------------------------------------------------------*/

int invert_mov_direction(int direction) { return -direction; }
