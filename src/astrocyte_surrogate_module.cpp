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

#include "astrocyte_surrogate_module.h"

// Generated includes:
#include "config.h"

// include headers with your own stuff
#include "astrocyte_surrogate.h"

// Includes from nestkernel:
#include "connection_manager_impl.h"
#include "connector_model_impl.h"
#include "dynamicloader.h"
#include "exceptions.h"
#include "genericmodel.h"
#include "genericmodel_impl.h"
#include "io_manager_impl.h"
#include "kernel_manager.h"
#include "model.h"
#include "model_manager_impl.h"
#include "nest.h"
#include "nest_impl.h"
#include "nestmodule.h"
#include "target_identifier.h"

// Includes from sli:
#include "booldatum.h"
#include "integerdatum.h"
#include "sliexceptions.h"
#include "tokenarray.h"

// -- Interface to dynamic module loader ---------------------------------------

/*
 * There are three scenarios, in which astrocyte_surrogate_module can be loaded by NEST:
 *
 * 1) When loading your module with `Install`, the dynamic module loader must
 * be able to find your module. You make the module known to the loader by
 * defining an instance of your module class in global scope. (LTX_MODULE is
 * defined) This instance must have the name
 *
 * <modulename>_LTX_mod
 *
 * The dynamicloader can then load modulename and search for symbol "mod" in it.
 *
 * 2) When you link the library dynamically with NEST during compilation, a new
 * object has to be created. In the constructor the DynamicLoaderModule will
 * register your module. (LINKED_MODULE is defined)
 *
 * 3) When you link the library statically with NEST during compilation, the
 * registration will take place in the file `static_modules.h`, which is
 * generated by cmake.
 */
#if defined( LTX_MODULE ) | defined( LINKED_MODULE )
astrocyte_surrogate::AstrocyteSurrogateModule astrocyte_surrogate_module_LTX_mod;
#endif
// -- DynModule functions ------------------------------------------------------

astrocyte_surrogate::AstrocyteSurrogateModule::AstrocyteSurrogateModule()
{
#ifdef LINKED_MODULE
  // register this module at the dynamic loader
  // this is needed to allow for linking in this module at compile time
  // all registered modules will be initialized by the main app's dynamic loader
  nest::DynamicLoaderModule::registerLinkedModule( this );
#endif
}

astrocyte_surrogate::AstrocyteSurrogateModule::~AstrocyteSurrogateModule() = default;

const std::string
astrocyte_surrogate::AstrocyteSurrogateModule::name() const
{
  return std::string( "astrocyte_surrogate_module" ); // Return name of the module
}

//-------------------------------------------------------------------------------------

void
astrocyte_surrogate::AstrocyteSurrogateModule::init( SLIInterpreter* i )
{
  /* Register a neuron or device model.
     Give node type as template argument and the name as second argument.
  */
  register_astrocyte_surrogate( "astrocyte_surrogate" );
} // AstrocyteSurrogateModule::init()
