#!/bin/bash
echo "Compiling..."
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -o TaskManager *.cpp

# Loop from 1 to 6
for i in {1..6}; do
    echo "Running test for TaskManager with input $i under Valgrind..."
    
    # Run Valgrind with TaskManager and redirect output to test{i}.out
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="valgrind$i.log" ./TaskManager "$i" > "test$i.out"
    
    # Compare output with the expected file
    diff --strip-trailing-cr -B -Z "test$i.out" "tests/test$i.expected"
    
    # Check if the diff command succeeded
    if [ $? -eq 0 ]; then
        echo "Test $i passed!"
    else
        echo "Test $i failed!"
    fi
    
    echo # Blank line for readability
done
