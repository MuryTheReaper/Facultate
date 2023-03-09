#!/bin/bash

g++ tests.cpp main_test.cpp device.cpp repository.cpp services.cpp -o test --coverage

./test

gcovr
