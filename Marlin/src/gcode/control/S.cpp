#include "../gcode.h"
#include "../../feature/spindle_laser.h"

void GcodeSuite::S() {
  if (parser.seenval('S')) {
    const float spwr = parser.value_float();
    cutter.unitPower = TERN(SPINDLE_LASER_PWM,
                            cutter.power_to_range(cutter_power_t(round(spwr))),
                            spwr > 0 ? 255 : 0);
    cutter.set_power(cutter.upower_to_ocr(cutter.unitPower));
  }
}