#!/bin/bash
g++ server.cpp -lboost_system -lssl -lcrypto -ldl -lpthread -o server