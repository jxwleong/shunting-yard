#include "unity.h"
#include "ShuntingYard.h"
#include "LinkedList.h"
#include "Error.h"
#include "CException.h"
#include "Exception.h"
#include <stdarg.h>
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

// If any Data trying to add is NULL, throw exception
void test_LinkedListAddToHead_given_empty_linked_list_add_NULL_expect_ERR_DATA_NULL(void){
  CEXCEPTION_T e;
  int value = NULL ;
  LinkedList List = {NULL, NULL , 0};
  ListItem Item = {NULL, (void*) &value};

  Try{
    printf("%d\n",sizeof(value));
    LinkedListAddToHead(&List,&value);
    TEST_FAIL_MESSAGE("Expect ERR_DATA_NULL. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_DATA_NULL, e->errorCode);
    freeError(e);
  }

  //TEST_ASSERT_EQUAL(NULL,List.head);      // it's point to newData struct which is not null
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(NULL,Item.next);
  TEST_ASSERT_EQUAL(0,List.count);

}


// add char into the linked list
void test_LinkedListAddToHead_given_empty_linked_list_add_char_a_expect_item_inserted(void){
  CEXCEPTION_T e;
  char value = 'a';
  LinkedList List = {NULL, NULL , 0};
  ListItem Item = {NULL, (void*) &value};
  printf("%c\n",sizeof(value));
  LinkedListAddToHead(&List,&value);

  //TEST_ASSERT_EQUAL(NULL,List.head);      // it's point to newData struct which is not null
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(NULL,Item.next);
  TEST_ASSERT_EQUAL(1,List.count);

}


/*
 *  Starting from an empty linked-list, add item 1 into it
 *  BEFORE          AFTER
 *  head ------     head-----> item1 ---> address unknown
 *            |           next-----
 *  tail ------     tail----^     |
 *            |                   --
 *  count =0  --    count =1
 */
void test_LinkedListAddToHead_given_empty_linked_list_add_1_expect_item_inserted(void){
  int value =1 ;
  LinkedList List = {NULL, NULL , 0};
  ListItem Item = {NULL, (void*) &value};

  LinkedListAddToHead(&List,&value);


   // it's point to newData struct which is not null
  //TEST_ASSERT_EQUAL(&Item,List.tail);
  TEST_ASSERT_EQUAL(NULL,Item.next);
  TEST_ASSERT_EQUAL(1,List.count);

}

/*
 *  Starting from an linked-list with item 1 ,add item 2 into it
 *  BEFORE                 AFTER
 *  head ------> item1     head ------> newLinkedList
 *              next---             next-----> next----
 *  tail --------^    |    tail------------------^    |
 *  count=1          --     count=2                  --
 */

void test_LinkedListAddToHead_given_linked_list_with_item_1_add_item_2_expect_item_2_then_item_1(void){
  int value1 =1, new_value =2;
  ListItem Item1 = {NULL,(void*) &value1};
  ListItem newLinkedList = {NULL,(void*) &new_value};
  LinkedList List = {&Item1, NULL , 1};


  LinkedListAddToHead(&List,&new_value);

  //TEST_ASSERT_EQUAL(NULL,List.head);    // pointed at new node (unknown address)

  TEST_ASSERT_EQUAL(NULL,Item1.next);
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(2,List.count);
}

/*
 *  Starting from an empty linked-list, try to remove item but nothing to remove so should be NULL
 *  BEFORE          AFTER
 *  head ------     head----------|
 *            |           next-----
 *  tail ------     tail          |
 *            |       |------->  --
 *  count =0  --    count=1
 * return ERR_LINKEDLIST_EMPTY
 */

void test_LinkedListRemoveFromHead_given_empty_linked_list_remove_expect_ERR_LINKEDLIST_NULL(void){
  CEXCEPTION_T e;
  LinkedList List = {NULL, NULL ,  0};
  ListItem Item = {NULL,  (void *) NULL};


  Try{
    LinkedListRemoveFromHead(&List,&Item);
    TEST_FAIL_MESSAGE("Expect ERR_LINKEDLIST_NULL. But no exception thrown.");
  }
  Catch(e){
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_LINKEDLIST_NULL, e->errorCode);
    freeError(e);
  }

  TEST_ASSERT_EQUAL(NULL,List.head);
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(0,List.count);
}

/*
 *  Starting from an linked-list with item 1 then,remove it
 *  BEFORE                 AFTER
 *  head ------> item1     head------------->NULL
 *              next---    next------------->NULL
 *  tail --------^    |    tail------------->NULL
 *  count=1          --     count=0
 */

void test_LinkedListRemoveFromHead_given_linked_list_with_item_1_expect_NULL_after_remove(void){

  int value1 = 1;

  ListItem Item1 = {NULL,  (void *) &value1};
  LinkedList List = {&Item1, NULL , 1};

  LinkedListRemoveFromHead(&List,&Item1);

  TEST_ASSERT_EQUAL(NULL,List.head);

  TEST_ASSERT_EQUAL(NULL,Item1.next);
  TEST_ASSERT_EQUAL(NULL,List.tail);
  TEST_ASSERT_EQUAL(0,List.count);
}

/*
 *  Starting from an linked-list with item 1 ,remove item 2 from it
 *  BEFORE                                      AFTER
 *  head ------> item1                        head-----> item2
 *              next-----> item2                   next----->NULL
 *  tail --------^    next.item2----->NULL    tail---^
 *  count=1           tail----> item2
 */

 void test_LinkedListRemoveFromHead_given_linked_list_with_item_2_expect_item1_remove(void){

   int value1 =1, value2 =2;
   ListItem Item2 = {NULL,(void*) &value2};
   ListItem Item1 ={&Item2,(void*) &value1};
   LinkedList List = {&Item1, NULL , 1};

   LinkedListRemoveFromHead(&List,&Item1);

   TEST_ASSERT_EQUAL(NULL,Item1.next);
   TEST_ASSERT_EQUAL_PTR(&Item2, List.head);
   TEST_ASSERT_EQUAL(NULL,List.tail);
   TEST_ASSERT_EQUAL(0,List.count);
 }
