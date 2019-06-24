#include "tests.cpp"

int main() {

	Tests *tests = new Tests();
    tests->test_AvgTest1();
    tests->test_AvgTest2();
    tests->test_PropTest1();
    tests->test_PropTest2();
    tests->test_VarTest1();
    tests->test_VarTest2();

    return 0;
}
