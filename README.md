# Tree

A Red Black Tree Implemented in C++

## Usage

At this point, this project is an experiment, but it may be fun to tinker
with and optimize. Here are basic usage instructions.

```c++
#include "tree.hpp"

int main(int argc, const char* argv[])
{
    Tree<int> gdp = Tree<int>();
    int delta;

    gdp.set("united states", 16768100);
    gdp.set("china", 9181204);

    delta = gdp.get("united states") - gdp.get("china");

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
