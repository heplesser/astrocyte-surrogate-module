/*
 *  astrocyte_surrogate.h
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

#ifndef ASTROCYTE_SURROGATE_H
#define ASTROCYTE_SURROGATE_H

#include "config.h"

#ifdef HAVE_GSL

// C includes:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <gsl/gsl_sf_exp.h>

// Includes from nestkernel:
#include "archiving_node.h"
#include "connection.h"
#include "event.h"
#include "nest_types.h"
#include "node.h"
#include "recordables_map.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"


/* BeginUserDocs: astrocyte_surrogate

Short description
+++++++++++++++++

Surrogate model for astrocyte

Description
+++++++++++

``astrocyte_surrogate`` is a surrogate model for astrocytes. It sends pre-defined
constant slow inward current (SIC), while skipping the numerical update of astrocyte dynamics.
It can be used for benchmarking of neuron-astrocyte networks.

Parameters
++++++++++

The following parameters can be set in the status dictionary.

=== ======= ======================================================
SIC pA      Value of constant slow inward current
=== ======= ======================================================

Sends
+++++

SICEvent

Receives
++++++++

SpikeEvent, DataLoggingRequest

EndUserDocs */

namespace astrocyte_surrogate_module
{
  
using namespace nest;
  
void register_astrocyte_surrogate( const std::string& name );

class AstrocyteSurrogate : public StructuralPlasticityNode
{

public:
  AstrocyteSurrogate();
  AstrocyteSurrogate( const AstrocyteSurrogate& );
  ~AstrocyteSurrogate() override = default;

  /**
   * Import sets of overloaded virtual functions.
   * @see Technical Issues / Virtual Functions: Overriding, Overloading, and
   * Hiding
   */
  using Node::handle;
  using Node::handles_test_event;
  using Node::sends_secondary_event;


  void handle( SpikeEvent& ) override;
  void handle( DataLoggingRequest& ) override;

  size_t handles_test_event( SpikeEvent&, size_t ) override;
  size_t handles_test_event( DataLoggingRequest&, size_t ) override;

  void
  sends_secondary_event( SICEvent& ) override
  {
  }

  void get_status( DictionaryDatum& ) const override;
  void set_status( const DictionaryDatum& ) override;

private:
  void init_buffers_() override;
  void pre_run_hook() override;

  void update( Time const&, const long, const long ) override;

  friend class RecordablesMap< AstrocyteSurrogate >;
  friend class UniversalDataLogger< AstrocyteSurrogate >;

  //! Model parameters
  struct Parameters_
  {
    /** SIC value in pA. */
    double sic_;

    Parameters_(); //!< Sets default parameter values

    void get( DictionaryDatum& ) const; //!< Store current values in dictionary
    void set( const DictionaryDatum&, Node* node ); //!< Set values from dicitonary
  };

public:
  /**
   * State variables of the model.
   * @note Copy constructor required because of C-style array.
   */
  struct State_
  {
    State_(); //!< Default initialization

    void get( DictionaryDatum& ) const;
    void set( const DictionaryDatum&, const Parameters_&, Node* );
  };

  /**
   * Buffers of the model.
   */
  struct Buffers_
  {
    Buffers_( AstrocyteSurrogate& ); //!< Sets buffer pointers to 0
    Buffers_( const Buffers_&, AstrocyteSurrogate& ); //!< Sets buffer pointers to 0

    //! Logger for all analog data
    UniversalDataLogger< AstrocyteSurrogate > logger_;

    // remembers current lag for piecewise interpolation
    //long lag_;

    // values to be sent by SIC event
    std::vector< double > sic_values;
  };

  //! Read out state vector elements, used by UniversalDataLogger
  //template < State_::StateVecElems elem >
  //double
  //get_y_elem_() const
  //{
  //  return S_.y_[ elem ];
  //}

  Parameters_ P_;
  State_ S_;
  Buffers_ B_;

  //! Mapping of recordables names to access functions
  static RecordablesMap< AstrocyteSurrogate > recordablesMap_;
};

inline size_t
AstrocyteSurrogate::handles_test_event( SpikeEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
AstrocyteSurrogate::handles_test_event( DataLoggingRequest& dlr, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return B_.logger_.connect_logging_device( dlr, recordablesMap_ );
}

inline void
AstrocyteSurrogate::get_status( DictionaryDatum& d ) const
{
  P_.get( d );
  S_.get( d );
  StructuralPlasticityNode::get_status( d );

  ( *d )[ names::recordables ] = recordablesMap_.get_list();
}

inline void
AstrocyteSurrogate::set_status( const DictionaryDatum& d )
{
  Parameters_ ptmp = P_;     // temporary copy in case of errors
  ptmp.set( d, this );       // throws if BadProperty
  State_ stmp = S_;          // temporary copy in case of errors
  stmp.set( d, ptmp, this ); // throws if BadProperty

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  StructuralPlasticityNode::set_status( d );

  // if we get here, temporaries contain consistent set of properties
  P_ = ptmp;
  S_ = stmp;
}

} // namespace

#endif // HAVE_GSL
#endif // ASTROCYTE_SURROGATE_H
