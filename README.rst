Astrocyte Surrogate Module
==========================

This module provides the ``astrocyte_surrogate`` neuron model used as a benchmarking reference in ...

.. attention::

   This version of the extension module code will not work with NEST 3.6 or earlier.
   It is adapted to NEST Master as of 15 December 2023.

   To use this extension module with NEST with OpenMP threads, you
   need a NEST version that has PR #3051 integrated, i.e.,
   b8b2347f38947c042f88857c369c94c3bb6f6ee4 or later (5 Feb 2024).

   


Building the module
-------------------

To build the module manually, proceed as follows:

#. Install NEST from source.
#. Clone this repository to a location outside NEST's source code or build directories.
#. Create a build directory for the module outside its source
   directory and outside NEST source or build directories.
#. In the build directory, run

   .. code-block:: sh
		   
      cmake -Dwith-nest=<PATH TO NEST INSTALLATION>/bin/nest-config <PATH TO MODULE SOURCE DIR>
      make install

Using the module
----------------

In NEST, run

.. code-block:: python
		
   nest.Install("astrocyte_surrogate_module")

Model ``astrocyte_surrogate`` will now be available in NEST.
