#pragma once
#include "Fragment.h"
#include <vector>

template <typename T>
class HeftyDatum {
public:

    //Fragment<T>* frags;
    std::vector<Fragment> fragments;
    //std::vector<Fragment> chunks;
    size_t frag_overhead ;
    size_t data_size;
    int num_frags;

// Re-Building
    bool built;
    int present_frags;

    HeftyDatum(T& data) {
        //this->frags = data;
        //this->data = new T[data.size()];
        this->frags = nullptr;
        this.size = sizeof(data);
    }



    HeftyDatum() {
        this->data = nullptr;
        this->size = 0;
    }



    ~HeftyDatum() {
        delete fragments;
    }


    Fragment<T>* fragment_data(int max_payload_size) {
        return PacketHandler::fragment_data(data, size, max_payload_size);
    }



};
