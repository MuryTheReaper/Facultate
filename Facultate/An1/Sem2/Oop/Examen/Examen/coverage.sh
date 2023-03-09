#!/bin/bash

g++ teste.cpp main_test.cpp muzica.cpp repository.cpp services.cpp -o test --coverage

./test

gcovr
