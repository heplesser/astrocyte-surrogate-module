Astrocyte Surrogate Module
==========================

.. attention::

   This version of the extension module code will not work with NEST
   3.6 or earlier. It is adapted to NEST Master as of 15
   December 2023.

This module provides the ``astrocyte_surrogate`` neuron model used as a benchmarking reference in ...

Building the module
-------------------

The `build.sh` script included is currently untested—no guarantees
given.

To build the module manually, proceed as follows.

1. Install NEST from source.
1. Clone this repository to a location outside NEST's source code or
   build directories.
1. Create a build directory for the module outside its source
   directory and outside NEST source or build directories.
1. In the build directory, run

   cmake -Dwith-nest=<PATH TO NEST INSTALLATION>/bin/nest-config <PATH TO MODULE SOURCE DIR>
   make install

Using the module
----------------

In NEST, run

   nest.Install("astrocyte_surrogate_module")

Model `astrocyte_surrogate` will now be available in NEST.
