/*
 *  astrocyte_surrogate.cpp
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


#include "astrocyte_surrogate.h"

#ifdef HAVE_GSL

// C++ includes:
#include <cmath> // in case we need isnan() // fabs
#include <cstdio>
#include <iostream>

// Includes from libnestutil:
#include "dict_util.h"
#include "numerics.h"

// Includes from nestkernel:
#include "exceptions.h"
#include "kernel_manager.h"
#include "nest_impl.h"
#include "universal_data_logger_impl.h"

// Includes from sli:
#include "dictutils.h"


nest::RecordablesMap< astrocyte_surrogate_module::AstrocyteSurrogate > astrocyte_surrogate_module::AstrocyteSurrogate::recordablesMap_;

namespace astrocyte_surrogate_module
{
  
void
register_astrocyte_surrogate( const std::string& name )
{
  register_node_model< AstrocyteSurrogate >( name );
}



/* ----------------------------------------------------------------
 * Default constructors defining default parameters and state
 * ---------------------------------------------------------------- */

AstrocyteSurrogate::Parameters_::Parameters_()
  : sic_( 1.0 )
{
}

AstrocyteSurrogate::State_::State_()
{
}

/* ----------------------------------------------------------------
 * Parameter and state extractions and manipulation functions
 * ---------------------------------------------------------------- */

void
AstrocyteSurrogate::Parameters_::get( DictionaryDatum& d ) const
{
  def< double >( d, "SIC", sic_ );
}

void
AstrocyteSurrogate::Parameters_::set( const DictionaryDatum& d, Node* node )
{
  updateValueParam< double >( d, "SIC", sic_, node );

  if ( sic_ < 0.0 )
  {
    throw BadProperty( "SIC value must be >= 0" );
  }
}

void
AstrocyteSurrogate::State_::get( DictionaryDatum& d ) const
{
}

void
AstrocyteSurrogate::State_::set( const DictionaryDatum& d, const Parameters_&, Node* node )
{
}

AstrocyteSurrogate::Buffers_::Buffers_( AstrocyteSurrogate& n )
  : logger_( n )
{
}

AstrocyteSurrogate::Buffers_::Buffers_( const Buffers_&, AstrocyteSurrogate& n )
  : logger_( n )
{
}

/* ----------------------------------------------------------------
 * Default and copy constructor for node, and destructor
 * ---------------------------------------------------------------- */

AstrocyteSurrogate::AstrocyteSurrogate()
  : StructuralPlasticityNode()
  , P_()
  , S_()
  , B_( *this )
{
}

AstrocyteSurrogate::AstrocyteSurrogate( const AstrocyteSurrogate& n )
  : StructuralPlasticityNode( n )
  , P_( n.P_ )
  , S_( n.S_ )
  , B_( n.B_, *this )
{
}

/* ----------------------------------------------------------------
 * Node initialization functions
 * ---------------------------------------------------------------- */

void
AstrocyteSurrogate::init_buffers_()
{
  B_.sic_values.resize( kernel().connection_manager.get_min_delay(), 0.0 );

  B_.logger_.reset();
}

void
AstrocyteSurrogate::pre_run_hook()
{
  // ensures initialization in case mm connected after Simulate
  B_.logger_.init();
}

/* ----------------------------------------------------------------
 * Update and spike handling functions
 * ---------------------------------------------------------------- */

inline void
AstrocyteSurrogate::update( Time const& origin, const long from, const long to )
{
  for ( long lag = from; lag < to; ++lag )
  {
    //B_.lag_ = lag;

    // Fake SIC values
    B_.sic_values[ lag ] = P_.sic_;

    // log state data
    B_.logger_.record_data( origin.get_steps() + lag );

  } // end for loop

  // send SIC event
  SICEvent sic;
  sic.set_coeffarray( B_.sic_values );
  kernel().event_delivery_manager.send_secondary( *this, sic );
}

void
AstrocyteSurrogate::handle( SpikeEvent& e )
{
}

void
AstrocyteSurrogate::handle( DataLoggingRequest& e )
{
  B_.logger_.handle( e );
}

} // namespace astrocyte_surrogate_module

#endif // HAVE_GSL
