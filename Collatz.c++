// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair

#include "Collatz.h"
#include <unordered_map>

std::unordered_map<int, int> lazycache;
// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
    return std::make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
//    assert(i>0);
//    assert(j>0);
    int max = 0;
    int a,b;
    if (j<i) {
        a=j;b=i;
    } else {
        a=i;b=j;
    }
    while( a<=b ) {
        int length = 1;
        unsigned t = a;
        while( t!=1 ) {
            if(lazycache[t]) {
                length+=lazycache[t]-1;
                break;
            }
            if(t&1) {//t is odd
                t=3*t+1;
                t>>=1;
                length+=2;
            } else {
                t>>=1;
                length+=1;
            }
        }
        lazycache[a]=length;
        if(length>max) {
            max = length;
        }
        a++;
     }
    return max;}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0))
            return;
        const int i = p.first;
        const int j = p.second;
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
