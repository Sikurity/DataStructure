//
//  Comparable.cpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

#include "Comparable.hpp"

Comparable::Comparable(int k, int v) : key(k), value(v) {

}

Comparable::Comparable() {
    Comparable(-1, -1);
}

bool Comparable::operator<(const Comparable &obj) const {
    if (value != obj.value)
        return value < obj.value;

    return key < obj.key;
}
