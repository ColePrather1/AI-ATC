#pragma once

struct FragmentHeader {
  uint8_t sequence_id;
  uint8_t total_fragments;
  uint8_t fragment_number;
};



template <typename T>
class Fragment {
public:
    int sequence_id;
    T* data;
    size_t size;
    int total_frags;
    bool is_last;

};



template <typename T>
class Fragment {
public:
    FragmentHeader* header;
    T* data;

};





/*
template <typename T>
class Fragment {
public:
    int sequence_id;
    T* data;
    size_t size;
    int total_frags;
    bool is_last;

};


struct Fragment {
    int id;
    int offset;
    int total_fragments;
    bool more_fragments;
    //std::vector<char> payload;
    std::vector<char> payload;
};
*/
