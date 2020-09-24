#ifndef UT_MEMORYITEMDELEGATE_H
#define UT_MEMORYITEMDELEGATE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QTest>
#include <DApplicationHelper>

class Ut_MemoryItemDelegate : public ::testing::Test
{
public:
    Ut_MemoryItemDelegate();

public:
    virtual void SetUp();

    virtual void TearDown();
};

#endif // UT_MEMORYITEMDELEGATE_H
