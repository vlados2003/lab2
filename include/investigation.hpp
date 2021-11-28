// Copyright 2021 Your Name vlados2003

#ifndef INCLUDE_INVESTIGATION_HPP_
#define INCLUDE_INVESTIGATION_HPP_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <ctime>

const std::vector <size_t> cache_size { 512 * 1024,          // L1
                                  2 * 1024 * 1024,      // L2
                                  48 * 1024 * 1024 };   // L3

const size_t iteration = 1000;

class Investigation
{
 private:
  std::string _travel_variant;
  std::vector <size_t> _buffer_size;      // объём буфера
  std::vector <double> _duration;         // время
 public:
  explicit Investigation(std::string travel_variant = "");
  ~Investigation();
  void direction();
  void reverse();
  void random();
  void print(std::ostream& os);
};

#endif // INCLUDE_INVESTIGATION_HPP_
