//
//  Pair.hpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

#ifndef Pair_hpp
#define Pair_hpp

struct Pair {
    int first;
    int second;

    Pair(int first, int second);
    Pair();
    bool operator<(const Pair &p) const;
    bool operator==(const Pair &p) const;
    bool operator<=(const Pair &p) const;
};

#endif /* Pair_hpp */
