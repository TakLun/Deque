#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <random>
#include "Deque.hpp"

// May assume memcpy()-able.
// May assume = operator.

/*
 * Test for class MyClass.
 */

struct MyClass {
    int id;
    char name[10];
};

bool
MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

void
MyClass_print(const MyClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}

Deque_DEFINE(MyClass)

/*
 * Test for int.
 */

bool
int_less(const int &o1, const int &o2) {
    return o1 < o2;
}
Deque_DEFINE(int)

int
main() {

    {
        Deque_MyClass deq;
        Deque_MyClass_ctor(&deq, MyClass_less_by_id);

        assert(deq.size(&deq) == 0);
        assert(deq.empty(&deq));

        // Should print "---- Deque_MyClass, 14".
        printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));
        // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
        assert(sizeof deq.type_name == 14);

        deq.push_back(&deq, MyClass{1, "Joe"});
        deq.push_back(&deq, MyClass{2, "Mary"});
        deq.push_back(&deq, MyClass{3, "Tom"});
        deq.push_front(&deq, MyClass{0, "Mike"});
        deq.push_front(&deq, MyClass{-1, "Mary"});

        MyClass_print(&deq.front(&deq));
        MyClass_print(&deq.back(&deq));
        assert(deq.front(&deq).id == -1);
        assert(deq.back(&deq).id == 3);

        deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq).id == 0);
        assert(deq.back(&deq).id == 2);

        assert(deq.size(&deq) == 3);

        for (Deque_MyClass_Iterator it = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
            MyClass_print(&it.deref(&it));
        }

        // Multiple iterators?
        for (Deque_MyClass_Iterator it1 = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it1, deq.end(&deq)); it1.inc(&it1)) {
            MyClass_print(&it1.deref(&it1));
            for (Deque_MyClass_Iterator it2 = deq.begin(&deq);
             !Deque_MyClass_Iterator_equal(it2, deq.end(&deq)); it2.inc(&it2)) {
                MyClass_print(&it2.deref(&it2));
                for (Deque_MyClass_Iterator it3 = deq.begin(&deq);
                 !Deque_MyClass_Iterator_equal(it3, deq.end(&deq)); it3.inc(&it3)) {
                    MyClass_print(&it3.deref(&it3));
                }
            }
        }

        // Test decrement.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
        }

        // printf("Using at.\n");

        for (size_t i = 0; i < 3; i++) {
            MyClass_print(&deq.at(&deq, i));
        }

        deq.clear(&deq);

        deq.dtor(&deq);

        // Test equality.  It is undefined behavior if the two deques were constructed with different
        // comparison functions.
        {
            Deque_MyClass deq1, deq2;
            Deque_MyClass_ctor(&deq1, MyClass_less_by_id);
            Deque_MyClass_ctor(&deq2, MyClass_less_by_id);

            deq1.push_back(&deq1, MyClass{1, "Joe"});
            deq1.push_back(&deq1, MyClass{2, "Jane"});
            deq1.push_back(&deq1, MyClass{3, "Mary"});
            deq2.push_back(&deq2, MyClass{1, "Joe"});
            deq2.push_back(&deq2, MyClass{2, "Jane"});
            deq2.push_back(&deq2, MyClass{3, "Mary"});

	    assert(Deque_MyClass_equal(deq1, deq2));

            deq1.pop_back(&deq1);
            assert(!Deque_MyClass_equal(deq1, deq2));
            deq1.push_back(&deq1, MyClass{4, "Mary"});
            assert(!Deque_MyClass_equal(deq1, deq2));
	    
            deq1.dtor(&deq1);
            deq2.dtor(&deq2);
        }
    }

    // Test that it can handle other types.  Tests are the same, more or less.
    {
        Deque_int deq;
        Deque_int_ctor(&deq, int_less);

        assert(deq.size(&deq) == 0);
        assert(deq.empty(&deq));
	
        // Should print "---- Deque_int, 10".
        printf("---- %s, %d\n", deq.type_name, int(sizeof(deq.type_name)));
        // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
        assert(sizeof deq.type_name == 10);

        deq.push_back(&deq, 1);
        deq.push_back(&deq, 2);
        deq.push_back(&deq, 3);
        deq.push_front(&deq, 0);
        deq.push_front(&deq, -1);

        printf("%d\n", deq.front(&deq));
        printf("%d\n", deq.back(&deq));
        assert(deq.front(&deq) == -1);
        assert(deq.back(&deq) == 3);

        deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq) == 0);
        assert(deq.back(&deq) == 2);

        assert(deq.size(&deq) == 3);

        for (Deque_int_Iterator it = deq.begin(&deq);
         !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
            printf("%d\n", it.deref(&it));
        }

        // Test decrement.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it) == 2);
        }

        printf("Using at.\n");

        for (size_t i = 0; i < 3; i++) {
            printf("%d: %d\n", int(i), deq.at(&deq, i));
        }

        deq.clear(&deq);

        deq.dtor(&deq);
	
        // Test equality.  It is undefined behavior if the two deques were constructed with different
        // comparison functions.
        {
            Deque_int deq1, deq2;
            Deque_int_ctor(&deq1, int_less);
            Deque_int_ctor(&deq2, int_less);

            deq1.push_back(&deq1, 1);
            deq1.push_back(&deq1, 2);
            deq1.push_back(&deq1, 3);
            deq2.push_back(&deq2, 1);
            deq2.push_back(&deq2, 2);
            deq2.push_back(&deq2, 3);

            assert(Deque_int_equal(deq1, deq2));

            deq1.pop_back(&deq1);
            assert(!Deque_int_equal(deq1, deq2));
            deq1.push_back(&deq1, 4);
            assert(!Deque_int_equal(deq1, deq2));

            deq1.dtor(&deq1);
            deq2.dtor(&deq2);
        }

        // Test performance.
        {
            std::default_random_engine e;
            using rand = std::uniform_int_distribution<int>;
            std::uniform_real_distribution<float> action;
            Deque_int deq;
            Deque_int_ctor(&deq, int_less);

            // In one end, out the other.
            for (int i = 0; i < 10000000; i++) {
                // fprintf(stderr, "iter: %d\n", i);
                deq.push_back(&deq, i);
                deq.pop_front(&deq);
            }
            for (int i = 0; i < 10000000; i++) {
                deq.push_front(&deq, i);
                deq.pop_back(&deq);
            }
            // Random.
            int pf = 0, pb = 0, pof = 0, pob = 0;
            for (int i = 0; i < 10000000; i++) {
                if (action(e) > .51) {
                    if (rand(0, 1)(e) == 0) {
		        deq.push_back(&deq, i);
                        pf++;
                    } else {
		        deq.push_front(&deq, i);
                        pb++;
                    }
                } else {
                    if (deq.size(&deq) > 0) {
                        if (rand(0, 1)(e) == 0) {
			    deq.pop_back(&deq);
                            pob++;
                        } else {
			    deq.pop_front(&deq);
                            pof++;
                        }
                    }
                }
            }
            printf("%d push_backs, %d push_fronts, %d pop_backs, %d pop_fronts, %d size\n", pb, pf, pob, pof, (int) deq.size(&deq));
            deq.dtor(&deq);
        }
    }
}
