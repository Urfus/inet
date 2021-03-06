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

#include "inet/common/packet/Message.h"

namespace inet {

Register_Class(Message);

Message::Message(const char *name, short kind) :
    cMessage(name, kind)
{
}

Message::Message(const Message& other) :
    cMessage(other),
    tags(other.tags)
{
}

std::ostream& Message::printToStream(std::ostream& stream, int level, int evFlags) const
{
    std::string className = getClassName();
    auto index = className.rfind("::");
    if (index != std::string::npos)
        className = className.substr(index + 2);
    if (level <= PRINT_LEVEL_DETAIL)
        stream << EV_FAINT << "(" << className << ")" << EV_NORMAL;
    stream << EV_ITALIC << getName() << EV_NORMAL;
    return stream;
}

Request::Request(const char *name, short kind) :
    Message(name, kind)
{
}

Request::Request(const Request& other) :
    Message(other)
{
}

Indication::Indication(const char *name, short kind) :
    Message(name, kind)
{
}

Indication::Indication(const Indication& other) :
    Message(other)
{
}

} // namespace

