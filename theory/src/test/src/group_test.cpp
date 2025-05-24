#include<iostream>
#include<vector>
#include<memory>


#include "../include/group_test.h"
#include "../../maths/include/group.h"


void GroupTest::test_all() {
    check_constructor();
}


void GroupTest::check_constructor() {


    std::vector<ull> g = {1, 2, 3};
    OperationRules op = OperationRules::Modulo;


    
    std::shared_ptr<Group>  sp(new Group(g, op));
    sp->print_group();
}