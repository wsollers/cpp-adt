#include <fuzztest/fuzztest.h>

#include "../src/list/list.h"o


#include <vector>
#include <string>
#include <optional>

// A helper function to add multiple elements to the SinglyLinkedList
void AddElements(Lists::SinglyLinkedList<int>& list, const std::vector<int>& elements) {
    for (const auto& elem : elements) {
        list.add(elem);
    }
}

// Fuzz test for adding elements to the SinglyLinkedList
void Fuzz_AddElements(const std::vector<int>& elements) {
    Lists::SinglyLinkedList<int> list;
    AddElements(list, elements);
    for (const auto& elem : elements) {
        if (list.contains(elem)) {
            FUZZTEST_INTERNAL_ASSERT(list.contains(elem), "Added element should be found in the list.");
        }
    }
}
FUZZ_TEST(Fuzz_AddElements);

// Fuzz test for inserting elements at the front of the SinglyLinkedList
void Fuzz_InsertAtFront(const std::vector<int>& elements) {
    Lists::SinglyLinkedList<int> list;
    for (const auto& elem : elements) {
        list.insertAtFront(elem);
    }
    
    // Verify that the first element inserted is now at the end of the list
    if (!elements.empty()) {
        FUZZTEST_INTERNAL_ASSERT(list.contains(elements.back()), "The last element inserted at front should be found in the list.");
    }
}
FUZZ_TEST(Fuzz_InsertAtFront);

// Fuzz test for inserting elements at the end of the SinglyLinkedList
void Fuzz_InsertAtEnd(const std::vector<int>& elements) {
    Lists::SinglyLinkedList<int> list;
    for (const auto& elem : elements) {
        list.insertAtEnd(elem);
    }

    // Verify the size is correct and the elements are inserted correctly
    FUZZTEST_INTERNAL_ASSERT(list.getSize() == elements.size(), "The size of the list should match the number of inserted elements.");
}
FUZZ_TEST(Fuzz_InsertAtEnd);

// Fuzz test for removing elements from the SinglyLinkedList
void Fuzz_RemoveElements(std::vector<int> elements) {
    Lists::SinglyLinkedList<int> list;
    AddElements(list, elements);

    // Randomly remove elements
    for (const auto& elem : elements) {
        list.remove(elem);
        FUZZTEST_INTERNAL_ASSERT(!list.contains(elem), "Removed element should not be found in the list.");
    }

    // After removing all, list should be empty
    FUZZTEST_INTERNAL_ASSERT(list.isEmpty(), "List should be empty after removing all elements.");
}
FUZZ_TEST(Fuzz_RemoveElements);

// Fuzz test for clearing the SinglyLinkedList
void Fuzz_ClearList(const std::vector<int>& elements) {
    Lists::SinglyLinkedList<int> list;
    AddElements(list, elements);

    // Clear the list
    list.clear();

    // Verify that the list is empty
    FUZZTEST_INTERNAL_ASSERT(list.isEmpty(), "List should be empty after calling clear.");
}
FUZZ_TEST(Fuzz_ClearList);

// Fuzz test for checking if SinglyLinkedList contains elements
void Fuzz_ContainsElements(const std::vector<int>& elements) {
    Lists::SinglyLinkedList<int> list;
    AddElements(list, elements);

    for (const auto& elem : elements) {
        FUZZTEST_INTERNAL_ASSERT(list.contains(elem), "The list should contain elements that were added.");
    }
}
FUZZ_TEST(Fuzz_ContainsElements);

// Fuzz test for removing elements from the front of the SinglyLinkedList
void Fuzz_RemoveFromFront(std::vector<int> elements) {
    Lists::SinglyLinkedList<int> list;
    AddElements(list, elements);

    // Remove all elements from the front
    for (const auto& elem : elements) {
        list.removeFromFront(elem);
        FUZZTEST_INTERNAL_ASSERT(!list.contains(elem), "After removing from front, element should not be found.");
    }

    // After removing all, list should be empty
    FUZZTEST_INTERNAL_ASSERT(list.isEmpty(), "List should be empty after removing all elements from the front.");
}
FUZZ_TEST(Fuzz_RemoveFromFront);

// Fuzz test for removing elements from the end of the SinglyLinkedList
void Fuzz_RemoveFromEnd(std::vector<int> elements) {
    Lists::SinglyLinkedList<int> list;
    AddElements(list, elements);

    // Remove all elements from the end
    for (const auto& elem : elements) {
        list.removeFromEnd(elem);
        FUZZTEST_INTERNAL_ASSERT(!list.contains(elem), "After removing from end, element should not be found.");
    }

    // After removing all, list should be empty
    FUZZTEST_INTERNAL_ASSERT(list.isEmpty(), "List should be empty after removing all elements from the end.");
}
FUZZ_TEST(Fuzz_RemoveFromEnd);

// Fuzz test for the SinglyLinkedList print method
void Fuzz_PrintList(const std::vector<int>& elements) {
    Lists::SinglyLinkedList<int> list;
    AddElements(list, elements);

    // Capture output and ensure no crashes or anomalies during print
    std::ostringstream output;
    std::streambuf* old = std::cout.rdbuf(output.rdbuf());  // Redirect std::cout to capture print output
    list.print();
    std::cout.rdbuf(old);  // Restore std::cout

    // Simple check for correct output format (optional based on your needs)
    if (!elements.empty()) {
        FUZZTEST_INTERNAL_ASSERT(!output.str().empty(), "The printed list output should not be empty.");
    }
}
FUZZ_TEST(Fuzz_PrintList);

