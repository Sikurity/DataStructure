//
//  Comparable.hpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

#ifndef Comparable_hpp
#define Comparable_hpp

struct Comparable {
    int key;
    int value;
    
    Comparable(int k, int v);
    Comparable();
    bool operator<(const Comparable &obj) const;
};

#endif /* Comparable_hpp */
