#include "./tools.h"
void test_mult64mod() {
    i64 a = 12345678903333ll;
    i64 b = 9876543210099999ll;
    i64 mod = 76500432846598793ll;
    assert(mult64mod(a,b, mod) == 75964974573502168ll);
}

void test_strong_pseudo() {
    assert(strong_pseudo_test(561) == false);
    assert(strong_pseudo_test(15485863) == true);
}

int main(){
    test_mult64mod();
    test_strong_pseudo();
    return 0;
}
