#include <gtest/gtest.h>
#include <nvs/store_manager.h>

#include "../test.h"


using namespace nvs;

TEST(StoreManager, store)
{

    Store *st = StoreManager::GetInstance("my_store");

    char *srcp;
    char *retp = (char *)malloc(15 * sizeof(char));


    EXPECT_EQ(NO_ERROR,
              st->create_obj("foo", 15, (void **)&srcp));

    snprintf(srcp,15, "hello world!");

    EXPECT_EQ(NO_ERROR, st->put("foo",1));
    EXPECT_EQ(NO_ERROR, st->get("foo", 1, (void **) &retp ));
    //compare the returned object content
    EXPECT_EQ(0,strncmp(srcp,retp,15));

}

int main(int argc, char** argv)
{
    InitTest(nvs::fatal, true);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
