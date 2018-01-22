#include <gtest/gtest.h>
#include <nvs/pool_id.h>
#include <nvs/memory_manager.h>

#include "../test.h"


using namespace nvs;

TEST(MemoryManager, Log)
{

    PoolId poolId = 1;
    size_t size = 10 * 1024 * 1024LLU; // 10 MB

    MemoryManager *mm = MemoryManager::GetInstance();
    Log *log = NULL;


    EXPECT_EQ(ID_NOT_FOUND, mm->FindLog(poolId, &log));
    EXPECT_EQ(NO_ERROR, mm->CreateLog(poolId, size));
    EXPECT_EQ(ID_IN_USE, mm->CreateLog(poolId,size));
    EXPECT_EQ(NO_ERROR, mm->FindLog(poolId, &log));
    assert(log != NULL);

    //EXPECT_EQ(NO_ERROR,mm->DestroyLog(poolId))

}




TEST(MemoryManager, append)
{

    PoolId poolId = 1;
    size_t size = 10 * 1024 * 1024LLU; // 10 MB

    MemoryManager *mm = MemoryManager::GetInstance();
    Log *log = NULL;


   //EXPECT_EQ(NO_ERROR, mm->(poolId, size));
    EXPECT_EQ(NO_ERROR, mm->FindLog(poolId, &log));

    char *data = "hello world";
    //append value
    EXPECT_EQ(NO_ERROR,log->append(data,12));

    //EXPECT_EQ(NO_ERROR,mm->DestroyLog(poolId))

}



int main(int argc, char** argv)
{
    InitTest(nvs::fatal, true);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}