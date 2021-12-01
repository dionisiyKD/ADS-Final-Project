QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BTree/btree.cpp \
    BTree/btree_add.cpp \
    DFS_BFS/dfs_bfs.cpp \
    DynamicProgramming/dynamicprogramming.cpp \
    GreedyAlgorithm/greedyalg.cpp \
    HashTable/hashtable.cpp \
    HashTable/hashtable_add.cpp \
    HashTable/hashtable_search.cpp \
    HeapSort/heapsort.cpp \
    HeapSort/heapsort_add.cpp \
    HeapSort/list.cpp \
    Huffman/huffman.cpp \
    ShortestPath/shortest_path.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BTree/btree.h \
    BTree/btree_add.h \
    DFS_BFS/dfs_bfs.h \
    DynamicProgramming/dynamicprogramming.h \
    GreedyAlgorithm/greedyalg.h \
    HashTable/hashtable.h \
    HashTable/hashtable_add.h \
    HashTable/hashtable_search.h \
    HeapSort/heapsort.h \
    HeapSort/heapsort_add.h \
    HeapSort/list.h \
    Huffman/huffman.h \
    ShortestPath/shortest_path.h \
    mainwindow.h

FORMS += \
    BTree/btree.ui \
    BTree/btree_add.ui \
    DFS_BFS/dfs_bfs.ui \
    DynamicProgramming/dynamicprogramming.ui \
    GreedyAlgorithm/greedyalg.ui \
    HashTable/hashtable.ui \
    HashTable/hashtable_add.ui \
    HashTable/hashtable_search.ui \
    HeapSort/heapsort.ui \
    HeapSort/heapsort_add.ui \
    Huffman/huffman.ui \
    ShortestPath/shortest_path.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
