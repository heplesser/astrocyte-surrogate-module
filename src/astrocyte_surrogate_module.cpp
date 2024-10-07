/*
 *  astrocyte_surrogate_module.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// Headers specific to module
#include "astrocyte_surrogate.h"

// Includes from NEST
#include "nest_extension_interface.h"

namespace astrocyte_surrogate_module
{
  class AstrocyteSurrogateModule : public nest::NESTExtensionInterface
  {
  public:
    AstrocyteSurrogateModule() {}
    virtual ~AstrocyteSurrogateModule() {}

    void initialize() override;
  };
}

// Define module instance outside of namespace to avoid name-mangling problems
astrocyte_surrogate_module::AstrocyteSurrogateModule astrocyte_surrogate_module_LTX_module;

void astrocyte_surrogate_module::AstrocyteSurrogateModule::initialize()
{
  register_astrocyte_surrogate( "astrocyte_surrogate" );
}
