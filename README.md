# listdiff-cpp
This project is still in development and is not complete. It aims to
solve comparing a list and it's previous state at any point of time,
therefore enabling to fire animations on demand and/or on request.

This is particurally useful when i.e. switching between different 
user interface views, you may want to fire all animations in the
list (additions, removals and index changes) all at once when the 
view appears as opposed to it happening in background and user not
seeing the animations. There are many potential use cases I will
elloboate at later stages of this project.

The library is very flexible where any collection of objects can 
be used to compare itself with previous state as long an adapter
implements `list_interface` and the list is copyable.

### Example of use
```
std::set<int> v;
v.insert(1);
v.insert(4);
v.insert(5);

auto adapter = create_list_adapter(v);
auto differ = create_differ(adapter);

v.insert(0);
v.erase(4);
v.erase(5);
v.insert(9);
v.insert(10);

differ.flush_events();

while (differ.count_events(ITEM_REMOVED) > 0)
{
    auto event = differ.top_event(ITEM_REMOVED);
    printf("item at index %zu was removed\n", event.index);
    differ.pop_event(ITEM_REMOVED);
}

while (differ.count_events(ITEM_INSERTED) > 0)
{
    auto event = differ.top_event(ITEM_INSERTED);
    printf("value of %i was inserted at index %zu!\n", adapter.at(event.index), event.index);
    differ.pop_event(ITEM_INSERTED);
}
```

## License

The MIT License (MIT)

Copyright (c) 2015 Konrad Wieczorek.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
