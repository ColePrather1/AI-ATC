#pragma once
#include "Fragment.h"

#include <vector>
#include <cstring>
#include <algorithm>



class PacketHandler {
public:
    std::vector<Fragment> fragment_data(const std::vector<char>& data, int max_payload_size) {
        std::vector<Fragment> fragments;
        int total_fragments = (data.size() + max_payload_size - 1) / max_payload_size;
        
        for (int i = 0; i < total_fragments; ++i) {
            Fragment f;
            f.id = rand(); // In practice, use a more robust ID generation
            f.offset = i * max_payload_size;
            f.total_fragments = total_fragments;
            f.more_fragments = (i < total_fragments - 1);
            
            int start = i * max_payload_size;
            int end = std::min((i + 1) * max_payload_size, (int)data.size());
            f.payload = std::vector<char>(data.begin() + start, data.begin() + end);
            
            fragments.push_back(f);
        }
        return fragments;
    }

    std::vector<char> reassemble_fragments(const std::vector<Fragment>& fragments) {
        if (fragments.empty()) return {};

        std::vector<Fragment> sorted_fragments = fragments;
        std::sort(sorted_fragments.begin(), sorted_fragments.end(), 
                  [](const Fragment& a, const Fragment& b) { return a.offset < b.offset; });

        std::vector<char> reassembled_data;
        for (const auto& fragment : sorted_fragments) {
            reassembled_data.insert(reassembled_data.end(), fragment.payload.begin(), fragment.payload.end());
        }

        return reassembled_data;
    }
};
