#include <sys/time.h>
#include <time.h>

#include <iostream>
#include <random>
#include <string>
#include <thread>

#include "ConcurrentPrimitives.hpp"
#include "HarnessUtils.hpp"
// #include "RSTMRBTreeMap.hpp"

// #include "RSTMRBTree.hpp"
// #include "RSTMLinkList.hpp"
// #include "RSTMHMap.hpp"

#if !defined(MNEMOSYNE) and !defined(PRONTO)
// #include "MCASRBTree.hpp"
// #include "MCASLinkList.hpp"
// #include "MCASHMap.hpp"
#include "CLevelHashTable.hpp"
#include "MODQueue.hpp"
#include "MSQueue.hpp"
#include "MontageMSQueue.hpp"
#include "MontageQueue.hpp"
#include "NVMMSQueue.hpp"
#include "PriorityQueue.hpp"
#include "Queue.hpp"

// #include "LinkedList.hpp"
// #include "HOHHashTable.hpp"
#include "DaliUnorderedMap.hpp"
#include "FriedmanQueue.hpp"
#include "HashTable.hpp"
#include "LockfreeHashTable.hpp"
#include "LockfreeSkipList.hpp"
#include "MODHashTable.hpp"
#include "MontageHashTable.hpp"
#include "MontageLfHashTable.hpp"
#include "MontageLfSkipList.hpp"
#include "MontageNatarajanTree.hpp"
#include "MontageSSHashTable.hpp"
#include "NVMGraph.hpp"
#include "NVMLockfreeHashTable.hpp"
#include "NVMLockfreeSkipList.hpp"
#include "NVMNatarajanTree.hpp"
#include "NVMSOFTHashTable.hpp"
#include "NVTHashTable.hpp"
#include "NVTLockfreeSkipList.hpp"
#include "NVTNatarajanTree.hpp"
#include "NatarajanTree.hpp"
#include "PLockfreeHashTable.hpp"
#include "PLockfreeSkipList.hpp"
#include "PNatarajanTree.hpp"
#include "SOFTHashTable.hpp"
#include "SSHashTable.hpp"
#include "TGraph.hpp"
#include "UnbalancedTree.hpp"
// #include "DLGraph.hpp"
#include "MontageGraph.hpp"
#endif

#ifdef MNEMOSYNE
#include "MneHashTable.hpp"
#include "MneQueue.hpp"
#endif

#ifdef PRONTO
#include "ProntoHashTable.hpp"
#include "ProntoQueue.hpp"
#endif
// #include "Toy.hpp"
#include "GraphTest.hpp"
#include "HeapChurnTest.hpp"
#include "KVTest.hpp"
#include "MapChurnTest.hpp"
#include "MapTest.hpp"
#include "MapVerify.hpp"
#include "QueueChurnTest.hpp"
#include "QueueTest.hpp"
#include "SetChurnTest.hpp"
#include "SyncTest.hpp"
#include "YCSBTest.hpp"
#ifndef MNEMOSYNE
#include "ActualRecoveryTest.hpp"
#include "GraphRecoveryTest.hpp"
#include "RecoverVerifyTest.hpp"
#include "TGraphConstructionTest.hpp"
#include "ToyTest.hpp"
#endif /* !MNEMOSYNE */
#include "AllocTest.hpp"
#include "CustomTypes.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    GlobalTestConfig gtc;
    const int numVertices = 1000000;
    const int meanEdgesPerVertex = 32;
    const int vertexLoad = 50;

    /* queues */

#if !defined(MNEMOSYNE) and !defined(PRONTO)
    gtc.addRideableOption(new MSQueueFactory<string>(),
                          "MSQueue");                              // transient
    gtc.addRideableOption(new NVMMSQueueFactory(), "NVMMSQueue");  // transient
    gtc.addRideableOption(new FriedmanQueueFactory(),
                          "FriedmanQueue");  // comparison
    gtc.addRideableOption(new MontageMSQueueFactory<string>(),
                          "MontageMSQueue");
    gtc.addRideableOption(new QueueFactory<string, PLACE_DRAM>(),
                          "TransientQueue<DRAM>");
    gtc.addRideableOption(new QueueFactory<string, PLACE_NVM>(),
                          "TransientQueue<NVM>");
    gtc.addRideableOption(new MontageQueueFactory<string>(), "MontageQueue");
    gtc.addRideableOption(new MODQueueFactory(), "MODQueue");

    /* mappings */
    gtc.addRideableOption(new LockfreeHashTableFactory<string>(),
                          "LfHashTable");  // transient
    gtc.addRideableOption(new NVMLockfreeHashTableFactory<string>(),
                          "NVMLockfreeHashTable");
    gtc.addRideableOption(new PLockfreeHashTableFactory(),
                          "PLockfreeHashTable");
    gtc.addRideableOption(new MontageLfHashTableFactory<string>(),
                          "MontageLfHashTable");
    gtc.addRideableOption(new DaliUnorderedMapFactory<string>(),
                          "Dali");  // comparison
    gtc.addRideableOption(new SOFTHashTableFactory<string>(), "SOFT");
    gtc.addRideableOption(new MODHashTableFactory<string>(), "MODHashTable");
    gtc.addRideableOption(new NVMSOFTHashTableFactory<string>(), "NVMSOFT");
    gtc.addRideableOption(new NVTHashTableFactory(), "NVTraverseHashTable");
    gtc.addRideableOption(new CLevelHashFactory(), "CLevelHashTable");
    gtc.addRideableOption(new SSHashTableFactory<std::string>(), "SSHashTable");
    gtc.addRideableOption(new MontageSSHashTableFactory<std::string>(),
                          "MontageSSHashTable");
    gtc.addRideableOption(new NatarajanTreeFactory<string>(),
                          "NataTree");  // transient
    gtc.addRideableOption(new NVMNatarajanTreeFactory(),
                          "NVMNataTree");  // transient
    gtc.addRideableOption(new HashTableFactory<string, PLACE_DRAM>(),
                          "TransientHashTable<DRAM>");
    gtc.addRideableOption(new HashTableFactory<string, PLACE_NVM>(),
                          "TransientHashTable<NVM>");
    gtc.addRideableOption(new MontageHashTableFactory<string>(),
                          "MontageHashTable");

    gtc.addRideableOption(new PNatarajanTreeFactory(), "PNataTree");
    gtc.addRideableOption(new MontageNatarajanTreeFactory<string>(),
                          "MontageNataTree");
    gtc.addRideableOption(new NVTNatarajanTreeFactory(), "NVTraverseNataTree");
    gtc.addRideableOption(new LockfreeSkipListFactory<std::string>(),
                          "LockfreeSkipList");
    gtc.addRideableOption(new MontageLfSkipListFactory<std::string>(),
                          "MontageLfSkipList");
    gtc.addRideableOption(new NVMLockfreeSkipListFactory<std::string>(),
                          "NVMLockfreeSkipList");
    gtc.addRideableOption(new PLockfreeSkipListFactory<std::string>(),
                          "PLockfreeSkipList");
    gtc.addRideableOption(new NVTLockfreeSkipListFactory<std::string>(),
                          "NVTLockfreeSkipList");

    /* graphs */
    gtc.addRideableOption(
        new TGraphFactory<numVertices, meanEdgesPerVertex, vertexLoad>(),
        "TGraph");
    gtc.addRideableOption(
        new NVMGraphFactory<numVertices, meanEdgesPerVertex, vertexLoad>(),
        "NVMGraph");
    // gtc.addRideableOption(new DLGraphFactory<numVertices>(), "DLGraph");
    gtc.addRideableOption(
        new MontageGraphFactory<numVertices, meanEdgesPerVertex, vertexLoad>(),
        "MontageGraph");

    gtc.addRideableOption(new MontageGraphFactory<3072627>(), "Orkut");
    gtc.addRideableOption(new TGraphFactory<3076727, 0, 100>(),
                          "TransientOrkut");

    /* LF hash tables */
    gtc.addRideableOption(new MontageLfHashTableFactory<uint64_t>(),
                          "MontageLfHashTable<uint64_t>");
    gtc.addRideableOption(new LockfreeHashTableFactory<uint64_t>(),
                          "LfHashTable<uint64_t>");
    gtc.addRideableOption(new NVMLockfreeHashTableFactory<uint64_t>(),
                          "NVMLockfreeHashTable<uint64_t>");

#endif /* !defined(MNEMOSYNE) and !defined(PRONTO) */
#ifdef MNEMOSYNE
    gtc.addRideableOption(new MneQueueFactory<string>(), "MneQueue");
    gtc.addRideableOption(new MneHashTableFactory<string>(), "MneHashTable");
#endif
#ifdef PRONTO
    gtc.addRideableOption(new ProntoQueueFactory(), "ProntoQueue");
    gtc.addRideableOption(new ProntoHashTableFactory(), "ProntoHashTable");
#endif
    gtc.addTestOption(new QueueChurnTest(50, 50, 2000),
                      "QueueChurn:eq50dq50:prefill=2000");
    gtc.addTestOption(new QueueTest(5000000, 50), "Queue:5m");
    gtc.addTestOption(
        new MapChurnTest<string, string>(0, 0, 50, 50, 1000000, 500000),
        "MapChurnTest<string>:g0p0i50rm50:range=1000000:prefill=500000");
    gtc.addTestOption(
        new MapChurnTest<string, string>(50, 0, 25, 25, 1000000, 500000),
        "MapChurnTest<string>:g50p0i25rm25:range=1000000:prefill=500000");
    gtc.addTestOption(
        new MapChurnTest<string, string>(90, 0, 5, 5, 1000000, 500000),
        "MapChurnTest<string>:g90p0i5rm5:range=1000000:prefill=500000");
    gtc.addTestOption(
        new MapTest<string, string>(0, 0, 50, 50, 1000000, 500000, 10000000),
        "MapTest<string>:g0p0i50rm50:range=1000000:prefill=500000:op=10000000");
    gtc.addTestOption(
        new MapTest<string, string>(50, 0, 25, 25, 1000000, 500000, 10000000),
        "MapTest<string>:g50p0i25rm25:range=1000000:prefill=500000:op="
        "10000000");
    gtc.addTestOption(
        new MapTest<string, string>(90, 0, 5, 5, 1000000, 500000, 10000000),
        "MapTest<string>:g90p0i5rm5:range=1000000:prefill=500000:op=10000000");
    gtc.addTestOption(
        new MapSyncTest<string, string>(0, 0, 50, 50, 1000000, 500000),
        "MapSyncTest<string>:g0p0i50rm50:range=1000000:prefill=500000");
    gtc.addTestOption(
        new MapSyncTest<string, string>(50, 0, 25, 25, 1000000, 500000),
        "MapSyncTest<string>:g50p0i25rm25:range=1000000:prefill=500000");
    gtc.addTestOption(new QueueSyncTest(50, 50, 2000),
                      "QueueSync:eq50dq50:prefill=2000");

    gtc.addTestOption(
        new MapChurnTest<uint64_t, uint64_t>(50, 0, 25, 25, 1000000, 500000),
        "MapChurnTest<uint64_t>:g50p0i25rm25:range=1000000:prefill=500000");
    gtc.addTestOption(
        new MapVerify<string, string>(50, 0, 25, 25, 1000000, 10000),
        "MapVerify");
#ifndef MNEMOSYNE
    gtc.addTestOption(new RecoverVerifyTest<string, string>(),
                      "RecoverVerifyTest");

    gtc.addTestOption(new ActualRecoveryTest<string, string>(),
                      "ActualRecoveryTest");
    gtc.addTestOption(
        new GraphTest(numVertices, meanEdgesPerVertex, vertexLoad, 8000),
        "GraphTest:80edge20vertex:degree32");
    gtc.addTestOption(
        new GraphTest(numVertices, meanEdgesPerVertex, vertexLoad, 9980),
        "GraphTest:99.8edge.2vertex:degree32");
    // gtc.addTestOption(new GraphRecoveryTest("graph_data/",
    // "orkut-edge-list_", 28610, 5, true), "GraphRecoveryTest:Orkut:verify");
    gtc.addTestOption(new GraphRecoveryTest("graph_data/", "orkut-edge-list_",
                                            28610, 5, false),
                      "GraphRecoveryTest:Orkut:noverify");
    gtc.addTestOption(
        new TGraphConstructionTest("graph_data/", "orkut-edge-list_", 28610, 5),
        "TGraphConstructionTest:Orkut");
#endif /* !MNEMOSYNE */
    gtc.addTestOption(new AllocTest(1024 * 1024, DO_JEMALLOC_ALLOC),
                      "AllocTest-JEMalloc");
    gtc.addTestOption(new AllocTest(1024 * 1024, DO_RALLOC_ALLOC),
                      "AllocTest-Ralloc");
    gtc.addTestOption(new AllocTest(1024 * 1024, DO_MONTAGE_ALLOC),
                      "AllocTest-Montage");

    gtc.parseCommandLine(argc, argv);
    omp_set_num_threads(gtc.task_num);
    gtc.runTest();

    // print out results
    if (gtc.verbose) {
        printf("Operations/sec: %ld\n",
               (uint64_t)(gtc.total_operations / gtc.interval));
    } else {
        string rideable_name = gtc.getRideableName().c_str();
        if (gtc.getEnv("PersistStrat") == "No") {
            rideable_name = "NoPersist" + rideable_name;
        }
        if (gtc.getEnv("Liveness") == "Nonblocking") {
            rideable_name = "nb" + rideable_name;
        }
#ifdef PRONTO
#ifdef PRONTO_SYNC
        rideable_name = "Sync" + rideable_name;
#else
        rideable_name = "Full" + rideable_name;
#endif
#endif
        printf("%d,%ld,%s,%s\n", gtc.task_num,
               (uint64_t)(gtc.total_operations / gtc.interval),
               rideable_name.c_str(), gtc.getTestName().c_str());
    }
}
