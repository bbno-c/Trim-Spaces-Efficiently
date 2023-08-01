#include <iostream>

void TrimRight(char* s) {
    if (s == nullptr) {
        return;
    }

    size_t length = strlen(s);
    if (length == 0) {
        return;
    }

    char* end = s + length - 1;
    while (end >= s && *end == ' ') {
        *end = '\0';
        --end;
    }
}

void RunTest(const char* input, const char* expectedOutput) {
    char* copy = new char[strlen(input) + 1];
    strcpy(copy, input);

    std::cout << "Input: \"" << copy << "\"\n";
    TrimRight(copy);
    std::cout << "Output: \"" << copy << "\"\n";

    assert(strcmp(copy, expectedOutput) == 0);

    delete[] copy;
    std::cout << std::endl;
}

constexpr int LENGTH = 100000000;  // Length of the string
constexpr const int NUM_SPACES = 50000000;  // Number of spaces at the end

void RunStressTest() {
    char* input = new char[LENGTH + 1];
    memset(input, 'A', LENGTH);  // Fill the string with 'A's
    input[LENGTH - NUM_SPACES] = '\0';  // Add null character at the position of the first space

    auto start = std::chrono::high_resolution_clock::now();

    TrimRight(input);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Stress test completed in " << duration.count() << " seconds.\n";
    assert(strlen(input) == LENGTH - NUM_SPACES);

    delete[] input;
}

int main() {
    // Test cases
    RunTest("", "");                                    // Empty string
    RunTest("Hello", "Hello");                          // No trailing spaces
    RunTest("Hello     ", "Hello");                     // Trailing spaces
    RunTest("   Hello", "   Hello");                    // Leading spaces
    RunTest("   Hello     ", "   Hello");               // Leading and trailing spaces
    RunTest("   Hello  World   ", "   Hello  World");   // Multiple leading and trailing spaces

    // Stress test
    RunStressTest();

    std::cin.get();
    return 0;
}
