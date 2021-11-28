// Copyright 2021 Your Name vlados2003

#include "investigation.hpp"

Investigation::Investigation(std::string travel_variant)
    : _travel_variant(travel_variant),
      _duration()
{
  for (size_t i = 0.5 * cache_size[0]; i < 1.5 * cache_size[2]; i *= 2) {
    _buffer_size.push_back(i);
  }
  _buffer_size.push_back(1.5 * cache_size[2]);
}

Investigation::~Investigation(){
}

void Investigation::direction(){
  [[maybe_unused]] int k = 0;
  for (const size_t size : _buffer_size) {
    int* arr = new int[size / 4];
    for (size_t i = 0; i < size / 4; i += 16) {  //прогрев
      k = arr[i];
    }
    clock_t start = clock();
    for (size_t it = 0; it < iteration; it++) {  //чтение
      for (size_t j = 0; j < size / 4; j += 16) {
        k = arr[j];
      }
    }
    clock_t stop = clock();
    delete[] arr;
    _duration.push_back(static_cast<double>(stop - start) / CLOCKS_PER_SEC *
                        1000);
  }
}

void Investigation::reverse(){
  [[maybe_unused]] int k = 0;
  for (const size_t size : _buffer_size) {
    int* arr = new int[size / 4];
    for (int i = size / 4; i >= 0; i -= 16) {  //прогрев
      k = arr[i];
    }
    clock_t start = clock();
    for (size_t it = 0; it < iteration; it++) {  //чтение
      for (int j = size / 4; j >= 0; j -= 16) {
        k = arr[j];
      }
    }
    clock_t stop = clock();
    delete[] arr;
    _duration.push_back(static_cast<double>(stop - start) / CLOCKS_PER_SEC *
                        1000);
  }
}

void Investigation::random(){
  [[maybe_unused]] int k = 0;
  for (const size_t size : _buffer_size) {
    int* arr = new int[size / 4];
    for (size_t i = 0; i < size / 4; i += 16) {  //прогрев
      unsigned int seed = i;
      k = arr[(rand_r(&seed) % (size / 4 / 16)) * 16];
    }
    clock_t start = clock();
    for (size_t it = 0; it < iteration; it++) {  //чтение
      for (size_t j = 0; j < size / 4; j += 16) {
        unsigned int seed = j;
        k = arr[(rand_r(&seed) % (size / 4 / 16)) * 16];
      }
    }
    clock_t stop = clock();
    delete[] arr;
    _duration.push_back(static_cast<double>(stop - start) / CLOCKS_PER_SEC *
                        1000);
  }
}

void Investigation::print(std::ostream& os){
  os << "Investigation:\n";
  os << "\ttravel order: \"" << _travel_variant << "\"\n";
  os << "\texperiments: \n";
  for (size_t i = 0; i < _duration.size(); i ++){
    os << "\t- experiment: \n";
    os << "\t\tnumber: " << i + 1 << "\n";
    os << "\t\tinput data: \n";
    int n = _buffer_size[i] >= 1024 * 1024 ? _buffer_size[i] / 1024 / 1024
                                           : _buffer_size[i] / 1024;
    std::string str = _buffer_size[i] >= 1024 * 1024 ? "Mb" : "Kb";
    os << "\t\t\tbuffer size: \"" << n << str << "\"\n";
    double d = _duration[i] > 1000 ? _duration[i] / 1000 : _duration[i];
    str = _duration[i] > 1000 ? "s" : "ms";
    os << "\t\tresults: \n";
    os << "\t\t\tduration: \"" << d << str << "\"\n";
  }
  os << "\n";
}
