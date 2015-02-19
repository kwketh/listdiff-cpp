//
//  main.cpp
//  listdiff-cpp
//
//  Created by Konrad Wieczorek on 13/02/2015.
//  Copyright (c) 2015 kwketh.com. All rights reserved.
//

#include <iostream>
#include <tests/list_differ_tests.h>

int main(int argc, const char * argv[])
{    
    ldcpp::differ_tests tests;
    tests.run_tests();
    
    return 0;
}
