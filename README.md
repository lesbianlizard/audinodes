A node system comprised of three types of **nodes**:

* **Source**: "input" nodes which don't have inputs of their own, but either generate or use external sources to provide an output.
* **Filter**: "standard" nodes which take inputs and DoStuff™ to make outputs.
* **Sink**: "output" nodes which only take inputs. Typically for exporting data to an external location (such as a file).


# Compile

Run:
   make


# Usage

   ./audinodes <input audio file> <output audio file>

Mess with `main.cpp` to adjust node setup ;)
