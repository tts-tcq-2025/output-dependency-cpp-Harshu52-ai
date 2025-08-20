#include <iostream>
#include <assert.h>
 
char size(int cms) {
    char sizeName = '\0';
    if(cms < 38) {
        sizeName = 'S';
    }
    else if(cms > 38 && cms < 42) {
        sizeName = 'M';
    }
    else {
        sizeName = 'L';
    }
    return sizeName;
}
 
void testTshirtSize() {
    std::cout << "\nTshirt size test\n";
    assert(size(37) == 'S');
    assert(size(38) == 'L');
    assert(size(40) == 'M');
    assert(size(42) == 'M');
    std::cout << "All is well (maybe!)\n";
}

