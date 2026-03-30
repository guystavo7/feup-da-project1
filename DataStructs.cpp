//
// Created by gustavobastos on 22/03/26.
//
#include "DataStructs.h"

bool operator== (const int_node& i1,const int_node& i2) {
    return (i1.integer==i2.integer) && (i2.is_sub==i1.is_sub);
}

bool operator== (const assignment& a,const assignment& b) {
    return a.a==b.a && a.rw==b.rw;
}

bool operator< (const int_node& i1,const int_node& i2)  {
    if (i1.integer==i2.integer) {
        return i1.is_sub<i2.is_sub;
    }
    return i1.integer<i2.integer;
}

int int_node_hash::operator () (const int_node  &in) const
{
    return std::hash<int>()(in.integer);
}