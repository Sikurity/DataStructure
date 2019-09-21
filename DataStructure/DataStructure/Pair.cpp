//
//  Pair.cpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

#include "Pair.hpp"

Pair::Pair(int first, int second) : first(first), second(second) {

}

Pair::Pair() {
    Pair(0, 0);
}

bool Pair::operator<(const Pair &p) const {
    if (first == p.first)
        return second < p.second;

    return first < p.first;
}

bool Pair::operator==(const Pair &p) const {
    return second == p.second && first == p.first;
}

bool Pair::operator<=(const Pair &p) const {
    return (*this) < p || (*this) == p;
}
