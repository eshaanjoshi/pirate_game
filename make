#!/bin/bash

# Initialize variables
clean_flag=false
files_to_clean=""

# Function to perform cleanup
perform_cleanup() {
    echo "Performing cleanup..."
    # Actual cleanup commands go here
    # Example: rm -rf /path/to/clean
}

# Parse command line options
while [[ $# -gt 0 ]]; do
    case "$1" in
        --clean)
            clean_flag=true
            shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

# Main script logic
if $clean_flag; then
    perform_cleanup
    echo "Cleanup completed."
    rm -rf build/
    exit 0
else
    echo "No operation specified."
    mkdir -p build
    g++ -c main.cpp src/*
    mv *.o build/
    cd build
    mkdir -p target
    g++ *.o -o target/sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lX11 -lpthread
    exit 1
fi
 g++ test.cpp -lsfml-graphics -lsfml-window -lsfml-system -lX11 -lpthread