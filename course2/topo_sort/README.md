# Topological Sort ( DFS - Recursive )
[https://en.wikipedia.org/wiki/Topological_sorting](https://en.wikipedia.org/wiki/Topological_sorting)

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

# Lecture
* [Video](https://www.coursera.org/lecture/algorithms-graphs-data-structures/topological-sort-yeKm7)

## Lecture Slides
![](documentation/dfs_01.png)
---
![](documentation/dfs_02.png)
---
![](documentation/dfs_03.png)
---
![](documentation/dfs_04.png)
---
![](documentation/dfs_05.png)
---
![](documentation/dfs_06.png)
---
![](documentation/dfs_07.png)
---
![](documentation/dfs_08.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Topological Sort algorithm
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
     
    
    #include <iostream>
    #include <unordered_map>
    #include <unordered_set>
    #include <set>
    #include <vector>
    
    
    using namespace std;
    
    
    class Solution
    {
    public:
    
        using Vertex = unsigned char;
        using AdjacencyList = vector< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        using Seen = unordered_set< Vertex >;
        using OrderedList = vector< Vertex >;
    
        OrderedList topo_sort( Graph& G, Seen seen={} )
        {
            auto N{ G.size() };
            OrderedList L( N + 1 );
            for( auto cur: AdjacencyList{ 'v','t','s','w' } ) // force order to exactly follow example section 8.5.5 on page 50-51 of Algorithms Illuminated: Part 2
                if( seen.insert( cur ).second )
                    go( L, G, cur, N, seen );
            return { L.cbegin() + 1, L.cend() }; // return buckets as 0-based index of [ 1 : N+1 )
        }
    
        void go( OrderedList& L, Graph& G, Vertex cur, // (cur)rent vertex at the top of the callstack
                 size_t& N, Seen& seen )
        {
            for( auto adj: G[ cur ] )              // (adj)acent neighbor vertices of the (G)raph's (cur)rent vertex
                if( seen.insert( adj ).second )    // if this is the first time the (adj)acent neighbor vertex has been seen
                    go( L, G, adj, N, seen );      // go further process (adj)acent neighbor vertex
            L[ N-- ] = cur;                        // update ordered-(L)ist entries in reverse order as the callstack returns from [ N : 1 ]
        }
    
    };
    
    int main()
    {
        //
        // graph from Quiz 8.3 on page 45 of Algorithms Illuminated: Part 2
        //
        Solution::Graph G{
            { 's', { 'v', 'w' } },
            { 'v', { 't' } },
            { 'w', { 't' } },
            { 't', {} },
        };
        Solution s;
        auto list = s.topo_sort( G );
        copy( list.cbegin(), list.cend(), ostream_iterator< Solution::Vertex >( cout, " " ) );
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target topo_sort -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
