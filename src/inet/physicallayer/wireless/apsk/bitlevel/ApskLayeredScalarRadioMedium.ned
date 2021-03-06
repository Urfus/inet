//
// Copyright (C) 2014 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

package inet.physicallayer.wireless.apsk.bitlevel;

import inet.physicallayer.wireless.common.medium.RadioMedium;

//
// This medium model is used by a simple hypothetical layered radio.
//
// @see ~ApskLayeredScalarRadio, ~ApskLayeredTransmitter, ~ApskLayeredReceiver.
//
module ApskLayeredScalarRadioMedium extends RadioMedium
{
    parameters:
        analogModel.typename = default("LayeredScalarAnalogModel");
        backgroundNoise.typename = default("IsotropicScalarBackgroundNoise");
        backgroundNoise.power = default(-110dBm);
        mediumLimitCache.centerFrequency = default(2.4GHz);
        mediumLimitCache.minReceptionPower = default(-85dBm);
        mediumLimitCache.minInterferencePower = default(-110dBm);
}

