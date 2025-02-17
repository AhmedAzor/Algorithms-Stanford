# Vertex Cover ( min K tree )
[https://en.wikipedia.org/wiki/Vertex_cover](https://en.wikipedia.org/wiki/Vertex_cover)

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture
[Video](https://www.coursera.org/lecture/algorithms-npcomplete/the-vertex-cover-problem-fxmkY)

## Lecture Slides
![](documentation/cover_01.png)
---
![](documentation/cover_02.png)
---
![](documentation/cover_03.png)
---
![](documentation/cover_04.png)
---
![](documentation/cover_05.png)
---
![](documentation/cover_06.png)
---
![](documentation/cover_07.png)
---
![](documentation/cover_08.png)
---
![](documentation/cover_09.png)
---


## Solution
```cpp

    /**
     *
     * Modern C++ implementation to find minimum vertex cover k on a binary tree
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include <iostream>
    #include <memory>
    
    
    using namespace std;
    using Type = int;
    struct TreeNode;
    using HTreeNode = shared_ptr< TreeNode >;
    struct TreeNode
    {
        Type value;
        HTreeNode left, right;
        TreeNode( Type value ) : value{ value }, left{ nullptr }, right{ nullptr } {}
    };
    
    
    class Solution
    {
    public:
    
        size_t vertex_cover_k( HTreeNode root )
        {
            return go( root );
        }
    
    private:
    
        size_t go( HTreeNode root )
        {
            if( ! root || ( ! root->left && ! root->right ))
                return 0;
            //
            // recursively find minimum vertex cover K by including XOR excluding the root
            //
            // case 1: root is included, therefore +1 for root, and recurse upon the root's subtrees
            //
            // case 2: root is excluded, therefore, if root has a left/right subtree,
            //         then those subtree roots MUST be included ( per vertex cover definition ),
            //         +1 for each direct left/right subtree root ( if they exist )
            //         and recursively skip past direct left/right subtrees roots which MUST be included,
            //         since they are NOT future exclude candidates ( they MUST be included if they exist )
            //
            auto include = 1 + go( root->left ) + go( root->right ),
                 exclude = ( ( root->left )? 1 + go( root->left->left ) + go( root->left->right ) : 0 )
                         + ( ( root->right )? 1 + go( root->right->left ) + go( root->right->right ) : 0 );
            return min( include, exclude );
        }
    
    }; // class Solution
    
    
    HTreeNode generateTree()
    {
    // K = 3 expected: { 2, 3, 5 }
    //
    //             1
    //            / \
    //           2   3
    //          / \   \
    //         4   5   6
    //            / \
    //           7   8
    
        auto root = make_shared< TreeNode >( 1 );
        root->left = make_shared< TreeNode >( 2 );
        root->right = make_shared< TreeNode >( 3 );
        root->left->left = make_shared< TreeNode >( 4 );
        root->left->right = make_shared< TreeNode >( 5 );
        root->right->right = make_shared< TreeNode >( 6 );
        root->left->right->left = make_shared< TreeNode >( 7 );
        root->left->right->right = make_shared< TreeNode >( 8 );
        return root;
    }
    
    int main()
    {
        Solution solution;
        auto tree = generateTree();
        auto K = solution.vertex_cover_k( tree );
        cout << "minimum of " << K << " vertices needed to cover tree" << endl;
    
        // minimum of 3 vertices needed to cover tree
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target vertex_cover_k_tree -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
