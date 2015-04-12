# Tree++

A Red Black Tree Implemented in C++

## Usage

At this point, this project is an experiment, but it may be fun to tinker
with and optimize. Here is a basic usage example.

```c++
#include "tree.hpp"

int main()
{
    Tree<double> stellarMass = Tree<double>();
    double delta;

    stellarMass.set("Sun", 1.0);
    stellarMass.set("Sirius", 2.02);
    stellarMass.set("R136a1", 256.0);

    delta = stellarMass.get("R136a1") - stellarMass.get("Sun");

    // ...

    return 0;
}

```

## Run the tests

Validate output:

```
$ scripts/test.sh
```

Check for memory leaks - you must have `valgrind` installed on your system:

```
$ scripts/memtest.sh
```

![Tree gif](http://i.giphy.com/ygUwDJOjip2.gif)
