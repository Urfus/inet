//
// Copyright (C) 2020 OpenSim Ltd.
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

package inet.power.base;

import inet.power.contract.ICcEnergySource;

//
// This is an abstract base module for current based energy source models.
// It defines shared signals and statistics.
//
// @see ~CcEnergyConsumerBase, ~CcEnergyGeneratorBase, ~CcEnergySinkBase, ~CcEnergyStorageBase
//
simple CcEnergySourceBase like ICcEnergySource
{
    parameters:
        @display("i=block/plug");
        @signal[currentConsumptionChanged];
        @statistic[currentConsumption](title="Current consumption"; source=currentConsumptionChanged; record=vector; interpolationmode=sample-hold);
}

