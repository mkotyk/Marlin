/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../../inc/MarlinConfig.h"

#if ENABLED(CNC_COORDINATE_SYSTEMS)

#include "../gcode.h"
#include "../../module/motion.h"

/**
 * 'G10 P' for tool settings and 'G10 L' for workspace settings
 */
void GcodeSuite::G10() {
    if (parser.seenval('L')) {
        int l  = parser.value_int();
        if (parser.seenval('P')) {
            int p = parser.value_int();
            switch(l) {
                case 1:         // Set Tool Table - Absolute (machine position) (Not yet supported)
                case 10:        // Set Tool Table - Relative (Not yet supported)
                case 11:        // Set Tool Table - Coordinates (Not yet supported)
                    break;
                case 2:         // Set Coordinate System - Absolute (machine position)
                case 20:        // Set Coordinate System - Relative
                    if (WITHIN(p, 0, MAX_COORDINATE_SYSTEMS - 1)) {
                        if (p == 0) p = active_coordinate_system; else p--;
                        LOOP_XYZ(i) {
                            if (parser.seenval(axis_codes[i])) {
                                const float v = LOGICAL_TO_NATIVE(parser.value_axis_units((AxisEnum)i), i),
                                            d = v - current_position[i];
                                if (l == 2) {
                                    coordinate_system[p].pos[i] = v;
                                } else if (l == 20) {
                                    coordinate_system[p].pos[i] = d;
                                }
                            }
                        }
                    }
                    break;
            }
        }
    }
}

#endif // CNC_COORDINATE_SYSTEMS
