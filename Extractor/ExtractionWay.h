/*

Copyright (c) 2013, Project OSRM, Dennis Luxen, others
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef EXTRACTION_WAY_H
#define EXTRACTION_WAY_H

#include "../DataStructures/HashTable.h"
#include "../DataStructures/TravelMode.h"
#include "../typedefs.h"

#include <string>
#include <vector>

struct ExtractionWay
{
    ExtractionWay() { Clear(); }

    inline void Clear()
    {
        id = SPECIAL_NODEID;
        nameID = INVALID_NAMEID;
        path.clear();
        keyVals.Clear();
        speed = -1;
        backward_speed = -1;
        duration = -1;
        type = -1;
        access = true;
        roundabout = false;
        isAccessRestricted = false;
        ignoreInGrid = false;
        travel_mode = TravelMode::Default;
        backward_travel_mode = TravelMode::Default;
    }

    enum Directions
    { notSure = 0,
      oneway,
      bidirectional,
      opposite };
    
    inline void set_direction(const Directions m)
    {
        if (Directions::oneway == m )
        {
            travel_mode = TravelMode::Default;
            backward_travel_mode = TravelMode::Inaccessible;
        }
        else if (Directions::opposite == m )
        {
          travel_mode = TravelMode::Inaccessible;
          backward_travel_mode = TravelMode::Default;
        }
        else if (Directions::bidirectional == m )
        {
          travel_mode = TravelMode::Default;
          backward_travel_mode = TravelMode::Default;
        }
    }

    inline const Directions get_direction()
    {
        if (TravelMode::Inaccessible != travel_mode && TravelMode::Inaccessible != backward_travel_mode )
        {
            return Directions::bidirectional;
        }
        else if (TravelMode::Inaccessible != travel_mode )
        {
            return Directions::oneway;
        }
        else if (TravelMode::Inaccessible != backward_travel_mode )
        {
            return Directions::opposite;
        }
        else
        {
            return Directions::notSure;
        }
    }

    inline void set_mode(const TravelMode m) { travel_mode = m; }
    inline const TravelMode get_mode() { return travel_mode; }
    inline void set_backward_mode(const TravelMode m) { backward_travel_mode = m; }
    inline const TravelMode get_backward_mode() { return backward_travel_mode; }

    unsigned id;
    unsigned nameID;
    double speed;
    double backward_speed;
    double duration;
    std::string name;
    short type;
    bool access;
    bool roundabout;
    bool isAccessRestricted;
    bool ignoreInGrid;
    std::vector<NodeID> path;
    HashTable<std::string, std::string> keyVals;
    TravelMode travel_mode : 4;
    TravelMode backward_travel_mode : 4;
};

#endif // EXTRACTION_WAY_H
