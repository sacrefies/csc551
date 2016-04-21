// -----------------------------------------------------------------------------
// Filename:    main.cpp
// Revision:    $Id$
// Description: this file contains the demo runs for the Kruskal implementation.
// Created:     04/20/2016 01:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------
//
//   ______                           _        _____                   _
//  |  ____|                         | |      |_   _|                 | |
//  | |__  __  ____ _ _ __ ___  _ __ | | ___    | |  _ __  _ __  _   _| |_
//  |  __| \ \/ / _` | '_ ` _ \| '_ \| |/ _ \   | | | '_ \| '_ \| | | | __|
//  | |____ >  < (_| | | | | | | |_) | |  __/  _| |_| | | | |_) | |_| | |_
//  |______/_/\_\__,_|_| |_| |_| .__/|_|\___| |_____|_| |_| .__/ \__,_|\__|
//                             | |                        | |
//                             |_|                        |_|
//
// Example input file from: http://algs4.cs.princeton.edu/43mst/
// tinyEWG.txt contains 8 vertices and 16 edges.
// note:  vertices start at 0.
//
// 8
// 16
// 4 5 0.35
// 4 7 0.37
// 5 7 0.28
// 0 7 0.16
// 1 5 0.32
// 0 4 0.38
// 2 3 0.17
// 1 7 0.19
// 0 2 0.26
// 1 2 0.36
// 1 3 0.29
// 2 7 0.34
// 6 2 0.40
// 3 6 0.52
// 6 0 0.58
// 6 4 0.93
// -----------------------------------------------------------------------------

// cpp includes
#include <iostream> // for cout, endl
// homemade headers
#include  "headers/kruskal.hpp"


using std::cout;
using std::endl;


//---------------------------------------------------------------------------
int main ( int argc, char* argv[] ) {
    //one test
    Kruskal  k1( 10 );
    k1.addEdge( 4, 5, 0.35 );
    k1.addEdge( 4, 7, 0.37 );
    k1.addEdge( 5, 7, 0.28 );
    k1.addEdge( 0, 7, 0.16 );
    k1.addEdge( 1, 5, 0.32 );
    k1.addEdge( 0, 4, 0.38 );
    k1.addEdge( 2, 3, 0.17 );
    k1.addEdge( 1, 7, 0.19 );
    k1.addEdge( 0, 2, 0.26 );
    k1.addEdge( 1, 2, 0.36 );
    k1.addEdge( 1, 3, 0.29 );
    k1.addEdge( 2, 7, 0.34 );
    k1.addEdge( 6, 2, 0.40 );
    k1.addEdge( 3, 6, 0.52 );
    k1.addEdge( 6, 0, 0.58 );
    k1.addEdge( 6, 4, 0.93 );
    k1.process();
    cout << "after: " << k1;
    cout << "cost = " << k1.getMSTCost() << endl;

    //another test
    Kruskal  k2( "tinyEWG.txt" );
    cout << "before: " << k2;
    k2.process();
    cout << "after: " << k2;
    cout << "cost = " << k2.getMSTCost() << endl;

    return 0;
}
