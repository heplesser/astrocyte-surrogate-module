Astrocyte Surrogate Module
==========================

This module provides the ``astrocyte_surrogate`` neuron model used as a benchmarking reference in ...

.. attention::

   This version of the extension module code requires NEST 3.7 or later.


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
