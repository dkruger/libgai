#include <gmock/gmock.h>
#include "libgai/assoc_array.h"



class GaiAssocArrayTest : public ::testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();

    struct gai_assoc_array* array;
};



void GaiAssocArrayTest::SetUp()
{
    array = gai_assoc_array_new();
}



void GaiAssocArrayTest::TearDown()
{
    gai_assoc_array_free(array);
    array = NULL;
}



TEST_F(GaiAssocArrayTest, aNewInstanceShouldNotBeNull)
{
    EXPECT_TRUE(array != NULL);
}



TEST_F(GaiAssocArrayTest, retrievingAnEntryFromAnEmptyArrayReturnsNull)
{
    EXPECT_EQ(NULL, gai_assoc_array_get(array, "key"));
}



TEST_F(GaiAssocArrayTest, retrievingAnEntryThatHasNotBeenAddedReturnsNull)
{
    gai_assoc_array_set(array, "a", "b");

    EXPECT_EQ(NULL, gai_assoc_array_get(array, "key"));
}



TEST_F(GaiAssocArrayTest, anEntryAddedToTheArrayCanBeRetrieved)
{
    const char* entry_value = "some_value";

    gai_assoc_array_set(array, "key", entry_value);

    EXPECT_STREQ(entry_value, gai_assoc_array_get(array, "key"));
    EXPECT_NE(entry_value, gai_assoc_array_get(array, "key"));
}



TEST_F(GaiAssocArrayTest, anEntryAddedToTheArryWillBeOverwrittenWhenSetTwice)
{
    gai_assoc_array_set(array, "key", "original_value");
    gai_assoc_array_set(array, "key", "some_new_value");

    EXPECT_STREQ("some_new_value", gai_assoc_array_get(array, "key"));
}



TEST_F(GaiAssocArrayTest, anEntryCanBeAddedWithANullName)
{
    gai_assoc_array_set(array, NULL, "null_value");

    EXPECT_STREQ("null_value", gai_assoc_array_get(array, NULL));
}



TEST_F(GaiAssocArrayTest, anEntryCanBeAddedWithANullValue)
{
    gai_assoc_array_set(array, "key", NULL);

    EXPECT_EQ(NULL, gai_assoc_array_get(array, "key"));
}



TEST_F(GaiAssocArrayTest, multipleEntriesMayRetrievedFromASingleArray)
{
    gai_assoc_array_set(array, "key1", "abc");
    gai_assoc_array_set(array, "key2", "def");
    gai_assoc_array_set(array, "key3", "ghi");

    EXPECT_STREQ("abc", gai_assoc_array_get(array, "key1"));
    EXPECT_STREQ("def", gai_assoc_array_get(array, "key2"));
    EXPECT_STREQ("ghi", gai_assoc_array_get(array, "key3"));
}
