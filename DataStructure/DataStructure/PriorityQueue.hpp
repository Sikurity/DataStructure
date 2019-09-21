//
//  PriorityQueue.hpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp

//
//  PriorityQueue.cpp
//  DataStructure
//
//  Created by YeongsikLee on 2018. 9. 9..
//  Copyright © 2018년 Hanyang Osori. All rights reserved.
//

template <typename T>
struct PriorityQueue {
private:
    static const int MAX_QUEUE_SIZE = 100000;
    T datas[MAX_QUEUE_SIZE + 1];
    int last;

public:
    PriorityQueue();

    bool isFull();
    bool isEmpty();
    void push(T data);
    void pop();

    T getTop();
};

#include "PriorityQueue.tpp"

#endif /* PriorityQueue_hpp */
