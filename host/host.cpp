// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <openenclave/host.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <vector>

// Include the untrusted helloworld header that is generated
// during the build. This file is generated by calling the
// sdk tool oeedger8r against the helloworld.edl file.
#include "er_u.h"

namespace boomerang {

constexpr size_t kMacSize = 16;
constexpr size_t kContentSize = 256;


struct PktHead {
  uint64_t signal;
  bool ___read_write;
  bool is_dummy;
  bool ___is_exceed;
  uint8_t ___enode_id;
};

struct Pkt {
  PktHead head;
  uint8_t content[kContentSize]{};
  uint8_t mac[kMacSize]{};
};

constexpr size_t kPktSize = sizeof(Pkt); // 285
}

std::vector<uint8_t> generateNPkts(int n) {
  std::vector<uint8_t> result;
  for (int i = 0; i < n; ++i) {
    // 创建一个Pkt
    boomerang::Pkt pkt;
    pkt.head.signal = i; // 使用循环变量作为signal值（示例）
    pkt.head.___read_write = true;
    pkt.head.is_dummy = false;
    pkt.head.___is_exceed = false;
    pkt.head.___enode_id = i % 256; // 使用循环变量模256作为enode_id值（示例）
    
    // 将Pkt结构体转换为uint8_t数组并添加到结果中
    uint8_t* pktBytes = reinterpret_cast<uint8_t*>(&pkt);
    result.insert(result.end(), pktBytes, pktBytes + sizeof(boomerang::Pkt));
  }
  return result;
}

bool check_simulate_opt(int* argc, const char* argv[])
{
    for (int i = 0; i < *argc; i++)
    {
        if (strcmp(argv[i], "--simulate") == 0)
        {
            fprintf(stdout, "Running in simulation mode\n");
            memmove(&argv[i], &argv[i + 1], (*argc - i) * sizeof(char*));
            (*argc)--;
            return true;
        }
    }
    return false;
}

// This is the function that the enclave will call back into to
// print a message.

void host_testOcall(uint8_t* buffer, size_t buffer_size) {
    uint8_t array[buffer_size];
    std::fill_n(array, buffer_size, 1);
    memcpy(buffer, array, buffer_size);
    fprintf(stdout, "ocall\n");
}

void host_helloworld()
{
    fprintf(stdout, "Enclave called into host to print: Hello World!\n");
}

void host_swapIn(int bigOhtIndex, uint8_t* inDataBuffer, size_t DataBufferSize) {
    fprintf(stdout, "host_swapIn\n");
}

int main(int argc, const char* argv[])
{
    oe_result_t result;
    int ret = 1;
    oe_enclave_t* enclave = NULL;

    uint32_t flags = OE_ENCLAVE_FLAG_DEBUG;
    if (check_simulate_opt(&argc, argv))
    {
        flags |= OE_ENCLAVE_FLAG_SIMULATE;
    }

    if (argc != 2)
    {
        fprintf(
            stderr, "Usage: %s enclave_image_path [ --simulate  ]\n", argv[0]);
    }

    // Create the enclave
    result = oe_create_er_enclave(
        argv[1], OE_ENCLAVE_TYPE_AUTO, flags, NULL, 0, &enclave);
    if (result != OE_OK)
    {
        fprintf(
            stderr,
            "oe_create_helloworld_enclave(): result=%u (%s)\n",
            result,
            oe_result_str(result));
    }
    // 写入：
    // std::vector<uint8_t> testBatch = generateNPkts(4502);
    // size_t index_small;
    // er_writeBatch(enclave, &index_small, testBatch.data(), testBatch.size());
    // fprintf(stdout, "write index %d\n", index_small);
    // er_readBatch(enclave, testBatch.data(), testBatch.size());

    // Call into the enclave
    // auto start_test = std::chrono::high_resolution_clock::now();
    result = enclave_helloworld(enclave);
    // auto end_test = std::chrono::high_resolution_clock::now();
    // auto duration_test = std::chrono::duration_cast<std::chrono::milliseconds>(end_test - start_test);
    // std::cout << "Execution time: " << duration_test.count() << " milliseconds" << std::endl;
    
    if (result != OE_OK)
    {
        fprintf(
            stderr,
            "calling into enclave_helloworld failed: result=%u (%s)\n",
            result,
            oe_result_str(result));
    }

    auto start = std::chrono::high_resolution_clock::now();
    size_t buffer_size = 3440000;
    uint8_t* buffer = new uint8_t[3440000];
    er_testin(enclave, buffer, buffer_size);
    delete[] buffer;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
    ret = 0;

    // Clean up the enclave if we created one
    if (enclave)
        oe_terminate_enclave(enclave);

    return ret;
}
