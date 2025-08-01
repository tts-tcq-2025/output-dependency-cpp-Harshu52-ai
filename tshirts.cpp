#include <iostream>
#include <assert.h>

char size(int cms) {
    char sizeName = '\0';
    if(cms < 38) {
        sizeName = 'S';
    } else if( cms < 42) {
        sizeName = 'M';
    } else  {
        sizeName = 'L';
    }
    return sizeName;
}

void testTshirtSize() {
    std::cout << "\nTshirt size test\n";
    assert(size(37) == 'S');
    assert(size(40) == 'M');
    assert(size(43) == 'L');
    std::cout << "All is well (maybe!)\n";
}
