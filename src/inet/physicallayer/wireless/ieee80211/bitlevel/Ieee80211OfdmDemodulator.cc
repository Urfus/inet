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

#include "inet/physicallayer/wireless/ieee80211/bitlevel/Ieee80211OfdmDemodulator.h"

#include "inet/physicallayer/wireless/apsk/bitlevel/ApskSymbol.h"
#include "inet/physicallayer/wireless/common/modulation/BpskModulation.h"
#include "inet/physicallayer/wireless/common/modulation/Qam16Modulation.h"
#include "inet/physicallayer/wireless/common/modulation/Qam64Modulation.h"
#include "inet/physicallayer/wireless/common/modulation/QpskModulation.h"
#include "inet/physicallayer/wireless/common/radio/bitlevel/SignalBitModel.h"

namespace inet {
namespace physicallayer {

Ieee80211OfdmDemodulator::Ieee80211OfdmDemodulator(const Ieee80211OfdmModulation *subcarrierModulation) :
    subcarrierModulation(subcarrierModulation)
{
}

std::ostream& Ieee80211OfdmDemodulator::printToStream(std::ostream& stream, int level, int evFlags) const
{
    stream << "Ieee80211OfdmDemodulator";
    if (level <= PRINT_LEVEL_TRACE)
        stream << EV_FIELD(subcarrierModulation, printFieldToString(subcarrierModulation, level + 1, evFlags));
    return stream;
}

BitVector Ieee80211OfdmDemodulator::demodulateSymbol(const Ieee80211OfdmSymbol *signalSymbol) const
{
    std::vector<const ApskSymbol *> apskSymbols = signalSymbol->getSubCarrierSymbols();
    const ApskModulationBase *demodulationScheme = subcarrierModulation->getSubcarrierModulation();
    BitVector field;
    for (unsigned int i = 0; i < apskSymbols.size(); i++) {
        if (!isPilotOrDcSubcarrier(i)) {
            const ApskSymbol *apskSymbol = apskSymbols.at(i);
            ShortBitVector bits = demodulationScheme->demapToBitRepresentation(apskSymbol);
            for (unsigned int j = 0; j < bits.getSize(); j++)
                field.appendBit(bits.getBit(j));
        }
    }
    EV_DEBUG << "The field symbols has been demodulated into the following bit stream: " << field << endl;
    return field;
}

const IReceptionBitModel *Ieee80211OfdmDemodulator::createBitModel(const BitVector *bitRepresentation, int signalFieldLength, bps signalFieldBitRate, int dataFieldLength, bps dataFieldBitRate) const
{
    return new ReceptionBitModel(b(signalFieldLength), signalFieldBitRate, b(dataFieldLength), dataFieldBitRate, bitRepresentation, NaN);
}

bool Ieee80211OfdmDemodulator::isPilotOrDcSubcarrier(int i) const
{
    return i == 5 || i == 19 || i == 33 || i == 47 || i == 26; // pilots are: 5,19,33,47, 26 (0+26) is a dc subcarrier
}

const IReceptionBitModel *Ieee80211OfdmDemodulator::demodulate(const IReceptionSymbolModel *symbolModel) const
{
    const std::vector<const ISymbol *> *symbols = symbolModel->getSymbols();
    BitVector *bitRepresentation = new BitVector();
    for (auto& symbols_i : *symbols) {
        const Ieee80211OfdmSymbol *symbol = dynamic_cast<const Ieee80211OfdmSymbol *>(symbols_i);
        BitVector bits = demodulateSymbol(symbol);
        for (unsigned int j = 0; j < bits.getSize(); j++)
            bitRepresentation->appendBit(bits.getBit(j));
    }
    return createBitModel(bitRepresentation, -1, bps(NaN), -1, bps(NaN)); // TODO
}

} // namespace physicallayer
} // namespace inet

