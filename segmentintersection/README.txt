To run code, simply make it and then run ./intersect n, where n is an
integer that reflects the amount of segments to be drawn.

There are no bugs we know of, except with some of the test cases 
where n is really large. The intersections go off the screen so it doesn't
work well. Other than that it should work fine. We are pretty sure we
are implementing a rangesearch when using the multimap, but we aren't 100% sure
Also, we decrement the sweep line to deal with degenerate cases.

Thanks,
Duncan and Dustin
