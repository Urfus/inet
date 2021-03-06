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

#ifndef __INET_LAYEREDTRANSMISSION_H
#define __INET_LAYEREDTRANSMISSION_H

#include "inet/physicallayer/wireless/common/base/packetlevel/TransmissionBase.h"
#include "inet/physicallayer/wireless/common/contract/bitlevel/ISignalAnalogModel.h"
#include "inet/physicallayer/wireless/common/contract/bitlevel/ISignalBitModel.h"
#include "inet/physicallayer/wireless/common/contract/bitlevel/ISignalPacketModel.h"
#include "inet/physicallayer/wireless/common/contract/bitlevel/ISignalSampleModel.h"
#include "inet/physicallayer/wireless/common/contract/bitlevel/ISignalSymbolModel.h"

namespace inet {
namespace physicallayer {

class INET_API LayeredTransmission : public TransmissionBase
{
  protected:
    const ITransmissionPacketModel *packetModel;
    const ITransmissionBitModel *bitModel;
    const ITransmissionSymbolModel *symbolModel;
    const ITransmissionSampleModel *sampleModel;
    const ITransmissionAnalogModel *analogModel;

  public:
    LayeredTransmission(const ITransmissionPacketModel *packetModel, const ITransmissionBitModel *bitModel, const ITransmissionSymbolModel *symbolModel, const ITransmissionSampleModel *sampleModel, const ITransmissionAnalogModel *analogModel, const IRadio *transmitter, const Packet *packet, const simtime_t startTime, const simtime_t endTime, const simtime_t preambleDuration, const simtime_t headerDuration, const simtime_t dataDuration, const Coord& startPosition, const Coord& endPosition, const Quaternion& startOrientation, const Quaternion& endOrientation);
    virtual ~LayeredTransmission();

    virtual std::ostream& printToStream(std::ostream& stream, int level, int evFlags = 0) const override;

    virtual const ITransmissionPacketModel *getPacketModel() const { return packetModel; }
    virtual const ITransmissionBitModel *getBitModel()    const { return bitModel; }
    virtual const ITransmissionSymbolModel *getSymbolModel() const { return symbolModel; }
    virtual const ITransmissionSampleModel *getSampleModel() const { return sampleModel; }
    virtual const ITransmissionAnalogModel *getAnalogModel() const override { return analogModel; }

    virtual const Packet *getPacket() const override { return packetModel->getPacket(); }
};

} // namespace physicallayer
} // namespace inet

#endif

