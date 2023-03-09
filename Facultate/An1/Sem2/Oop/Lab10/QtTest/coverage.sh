#!/bin/bash

g++ contract.cpp disciplina.cpp main_test.cpp raport.cpp repository.cpp services.cpp teste.cpp undo.cpp validator.cpp -o test --coverage

./test


gcovr
