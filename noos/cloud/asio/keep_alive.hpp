#ifndef RAPP_KEEP_ALIVE
#define RAPP_KEEP_ALIVE
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "includes.ihh"

namespace rapp 
{
namespace cloud 
{
/**
 * \class keep_alive
 * \brief class to know if it's a persistent connection 
 * \version 0.7.3
 * \date March 2017
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class keep_alive 
{
public: 

    /// \brief Constructor
    keep_alive(bool keep_alive = false)
    :keep_alive__(keep_alive)
    {};

    /// \return keep_alive value
    bool get_value()
    {
        return keep_alive__;
    }

    /// \brief set keep_alive value
    void set_value(bool keep_alive)
    {
        keep_alive__ = keep_alive;
    }

    ///TODO: timers to check connection
    
private:
    bool keep_alive__ = false;
};

}
}
#endif
