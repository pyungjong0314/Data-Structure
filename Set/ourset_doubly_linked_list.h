#pragma once

#ifndef __OURSET_DOUBLY_LINKED_LIST_H__
#define __OURSET_DOUBLY_LINKED_LIST_H__

#include <cstdlib>
#include "dnode.h"

class ourset {
public:
    typedef std::size_t size_type;
    typedef dnode::value_type value_type;

    ourset();
    ourset(const ourset& source);
    ~ourset();

    void operator = (const ourset& source);

    void operator += (const ourset& addend);

    bool operator== (const ourset& right);

    bool operator!= (const ourset& right);

    bool erase_one(const value_type& target);

    size_type count(const value_type& target) const;

    value_type grab();

    size_type size() const { return many_nodes; }

    void insert(const value_type& insert_data);

    void show_contents();

    void sort();

private:
    dnode* head_ptr;
    dnode* tail_ptr;
    size_type many_nodes;
};

ourset operator +(const ourset& set1, const ourset& set2);

#endif