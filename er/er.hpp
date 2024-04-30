#include <cstdint>
#include "oht.h"
/*
    pkt:
    sizeBoomerangPkt = 285;
    sizeBoomerangPktHead = 13;
    sizeBoomerangPktMac = 16;
    sizeBoomerangPktContent = 256;

    batch:
    numUser = 0;
    numEnode = 0;
    numBnode = 0;
    numBatch = 0;

    Elem:
    kKsize = 8;
    kVsize = 256;
    sizeElem = 272;

    oht:
    正常：
    kBound = std::exp(3 * kLogLambdaPowEpsilon);
    is_small = (numBatch < kBound) ? true : false;
    kZ = is_small ? 25 : uint32_t(std::ceil(5.0 * kLogLambdaPowEpsilon));
    kB = is_small ? std::ceil(uint32_t(5 * batch_num / kZ)): uint32_t(std::ceil(double(batch_num) / kLogLambdaPowEpsilon));
    实验：
    numBatch = 4502;
    kZSmall = 25
    kBSmall = std::ceil(uint32_t(5 * batch_num / kZ)) = 901
    sizeOhtSmall = 901 * 2 * 272 = 490,144 B

    merageTrager = 10;
    kZBig = 17
    kBBig = std::ceil(uint32_t(batch_num / kZ))
    sizeOhtBig = 


    other:

    kLambda = 128;
    kEpsilon = 0.75;
    kLogLambdaPowEpsilon = std::pow(std::log(kLambda), kEpsilon);
    
*/

template <size_t Ksize, size_t Vsize>
class ReadList {
public:
    ReadList() : head(nullptr), smalltail(nullptr), tail(nullptr) {}

    // 插入到 BigOht 区域末尾
    void insertIntoBigOht(OhtHead* oht) {
        if (!head) {
            head = oht;
            tail = oht;
        } else {
            tail->next = oht;
            oht->pre = tail;
            tail = oht;
        }
        id_map[oht->id] = oht;
    }

    // 插入到 SmallOht 区域末尾
    void insertIntoSmallOht(OhtHead* oht) {
        if (!head) {
            head = oht;
            tail = oht;
            smalltail = oht;
        } else {
            oht->next = smalltail->next;
            if (smalltail->next) {
                smalltail->next->pre = oht;
            }
            smalltail->next = oht;
            oht->pre = smalltail;
            if (smalltail == tail) {
                tail = oht;
            }
            smalltail = oht;
        }
        id_map[oht->id] = oht;
    }

    // 删除指定 id 的 OhtHead
    Oht* deleteById(size_t id) {
        auto it = id_map.find(id);
        Oht* res;
        if (it != id_map.end()) {
            OhtHead* oht = it->second;
            
            if (oht->pre) {
                oht->pre->next = oht->next;
            }
            if (oht->next) {
                oht->next->pre = oht->pre;
            }
            if (head == oht) {
                head = oht->next;
            }
            if (tail == oht) {
                tail = oht->pre;
            }
            if (smalltail == oht) {
                smalltail = oht->pre;
            }
            id_map.erase(it);
            res = oht->oht_p;
            delete oht;
        }
        return res;
    }

    size_t nextSmall() {
        if (!smalltail) {
            return 0;
        } else {
            return smalltail->id + 1;
        }
    }

    size_t nextBig() {
        if (!tail) {
            return 0;
        } else {
            return tail->id + 1;
        }
    }

    // 迭代器的 begin 函数
    OhtHead* begin() const {
        return head;
    }

    // 迭代器的 end 函数
    OhtHead* end() const {
        return nullptr; // 结束迭代的标志，通常为 nullptr
    }

private:
    OhtHead* head;       // 队列头部指针
    OhtHead* smalltail;  // BigOht区域开始位置前一个位置，也可以理解为small区域结尾
    OhtHead* tail;       // 队列尾部指针
    std::map<size_t, OhtHead*> id_map;  // 方便删除用的
};

template<size_t Ksize, size_t Vsize>
class EnclaveRead {
public:
    EnclaveRead() : ReadList(){
        configBatchNum = 1024
        // configItemSize = sizeof(boomerang::Pkt)
        configItemSize = 

        configBatchSize = 6880;
        configItemSize = 256;
        configBatchNum = configBatchSize / configItemSize;
        configPktSize = 288;
        configSmallSize = 688;
        configBigOhtSize = 6880;
    }
    /* wyh:
    readBatch
    介绍：
        readBatch是read data到来时 host 直接发给er的部分，用于读取一个batch中所有提到的read请求
    输入：
        dataBatch（兼作输出）：到来的数据格式为加密后的pkt list，由于输出结果只是更改了pkt list中pkt的一些成员，所以是在原地进行替换的
    输出：
        见输入
    */
    void readBatch(uint8_t *dataBatch, size_t dataBatchSize) {
        // 解密，转换为elems
        std::vector<Elem<kKsize, kVsize>> elems{};
        elems.reserve(configBatchNum);
        std::vector<uint8_t> pkt_dec_buf{};
        pkt_dec_buf.reserve(configPktSize);
        for (auto pkt_start = dataBatch; pkt_start + configPktSize <= dataCache + dataBatchSize; pkt_start += configPktSize) {
            elems.push_back(pkt_const_buf_to_elem<kKsize, kVsize>(pkt_start, pkt_dec_buf));
        }
        // 对每个elem调用
        for (auto& elem : elems) {
            readSingle(elem)
        }
        // 加密，转换为uint8_t
        for (auto i = 0; i < elems.size(); i++) {
            auto pkt_start = dataBatch + configPktSize * i;
            val_elem_to_pkt<kVsize>(pkt_start, elems[i].val);
        }
        // 返回
        return;
    }
    
    /* wyh:
    writeBatch
    介绍：
        writeBatch 是write data到来时host直接发给er的部分，用于将一个batch转换为一个小oht
    输入：
        dataBatch：host接收到的write batch原始数据，是加密后的boomerang pkt数据，需要转换为elems后进行后续处理
    输出：
        indexesInEnclave：用于指示这一batch对应的oht是哪些，因为小oht可能会有堆积所以不能是直接把所有的都合并了。
        （这一块还在考虑，感觉最好的方案是在host中保持一个map，用于指示哪个batch对应哪些小oht，这样merage的时候就可以比较简单了。需要注意的是实际上只有exchangeOht 中是需要index数据的，ew的merage步骤并不需要这个数据，因此由host完成可能是比较好的选择（但会有安全问题））
        （indexesInEnclave直接使用from、to 两个进行算了，这会强依赖于单线程的假设，因为插入ReadList的顺序必须是一定的，两个batch之间不能穿插）
    */
    void writeBatch(const uint8_t *dataBatch, size_t dataBatchSize, size_t *index) {
        // 解密，转换为elems
        std::vector<Elem<kKsize, kVsize>> elems{};
        elems.reserve(configBatchNum);
        std::vector<uint8_t> pkt_dec_buf{};
        pkt_dec_buf.reserve(configPktSize);
        for (auto pkt_start = dataBatch; pkt_start + configPktSize <= dataCache + dataBatchSize; pkt_start += configPktSize) {
            elems.push_back(pkt_const_buf_to_elem<kKsize, kVsize>(pkt_start, pkt_dec_buf));
        }
        // oht prepare build
        // 分配到堆上，避免被删除，注意自己删除
        auto ohtP = new Oht();
        ohtWrite(ohtP, std::move(elems), kPrfKey, kJobs);
        // 构造oht head 放进read_list
        auto ohtHead = new OhtHead();
        // 注意，delete在exchange 和 退出函数中
        ohtHead->id = read_list.nextSmall()
        ohtHead->oht_p = ohtP;
        ohtHead->size = configSmallSize;
        ohtHead->is_in = true;
        read_list.insertIntoSmallOht(OhtHead);
        // 设置oht index
        *index = ohtHead->id;
        // 返回
        return;
    }
    
    /* wyh:
    exchangeOht
    介绍：
        是write过程中host接收到ew merage结果后调用er的过程；实际进行的是将指示的几个ohtHead删除，然后在队尾插入一个bigOhtHea
    输入：
        indexes: 用于指示替换哪些小oht
        （在纠结是否保留全部oht（实际上也就10个），还是只有是开始结尾两个（这样强依赖于单线程））
        bigOhtHead：用于替换掉readlist中的
    输出：
        无，不需要
    */
    void exchangeOht(size_t indexFrom, size_t indexTo, uint8_t *bigOhtHead, size_t bigOhtHeadSize) {
        // 解密bigOhtHead
        std::vector<Elem<kKsize, kVsize>> elems{};
        elems.reserve(configBatchNum);
        std::vector<uint8_t> pkt_dec_buf{};
        pkt_dec_buf.reserve(configPktSize);
        for (auto pkt_start = dataBatch; pkt_start + configPktSize <= dataCache + dataBatchSize; pkt_start += configPktSize) {
            elems.push_back(pkt_const_buf_to_elem<kKsize, kVsize>(pkt_start, pkt_dec_buf));
        }
        // 从indexFrom到indexTo 遍历删除（或许可以写个函数简单点）
        for (size_t i = indexFrom; i < indexTo; i++) {
            auto ohtInHeap = read_list.deleteById(i);
            delete ohtInHeap;
        }
        // 把bigOhtHead岔道bigOht区域后面
        // void insertIntoBigOht(OhtHead* oht)
        auto bigOht = new OhtHead();
        memcpy(bigOht, bigOhtHead, bigOhtHeadSize);
        read_list.insertIntoBigOht(bigOht);
        // 返回
        return;
    }

private:
    /* wyh:
    readSingle
    介绍：
        readSingle是readBatch的辅助函数，是实际进行读的部分
    输入：
        elem（兼作输出）单独一个elem，直接对所有read list中的oht调用lookup就行了
    输出：
        见输入
    */
    void readSingle(Elem &elem) {
//template <size_t Ksize, size_t Vsize>
// struct OhtHead {
//     size_t oht_p;
//     size_t size;
//     bool is_in;
//     OhtHead* next;
//     OhtHead* pre;
// };
        // 对所有oht
        // Oht* oht;
        for (auto it = ReadList.begin(); it != ReadList.end(); it = it->next) {
            Oht *oht;
            // 如果在内部，就在oht_in中找对应位置的oht
            if (it->is_in) {
                oht = it->oht_p;
            } else {
            // 如果在外部，就调用swap in 找对应位置的oht进来
                uint8_t* tmp = new uint8_t[configBigOhtSize]
                // void swapIn(int bigOhtIndex, uint8_t* inDataBuffer, size_t inDataBufferSize)
                ocallSwapIn(it->id, tmp, configBigOhtSize);
                // TODO, 很烦，直接重写算了
                oht = &Oht(tmp, configBigOhtSize);
                delete tmp
            }
            // 使用oht lookup
            oht->lookup(elem, &kPrfKey);
        }
        return;    
        // 返回
    }

    void ohtWrite(Oht *oht, std::vector<Elem> &&elems, const std::vector<uint8_t> &prf_key, unsigned jobs) {
        for (auto &&elem : elems) {
            oht->prepare(std::move(elem));
        }
        oht->build(prf_key, jobs);
        // todo 这个key到底是用来干啥的 fuck！！直接设置成全局一致了
        // ohtHead.prf_key = prf_key;
    }

    std::vector<Oht> oht_in;
    ReadList read_list;
    std::vector<uint8_t> kPrfKey{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // from config
    size_t configBatchSize;
    size_t configItemSize;
    size_t configBatchNum;
    size_t configPktSize;
    size_t configSmallSize;
    size_t configBigOhtSize;
};

