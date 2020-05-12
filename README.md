# Lecture 10-3: MOVING AND COPYING

This contains the slides PDF and sample code for a lecture
discussing copying and moving objects in C++.

## A note on Homework 09:

* There are only three exercises and the first has two parts.
* I accidentally numbered them Exercises 1, 3, and 4.
* (I probably should have named Exercise 1 Part 2 as "Exercise 2".)

`Slide 01` [Part 01. Homework 09 Corrections](https://ensemble.reed.edu/Watch/Qi3p4N9M) *08m15s*  
`Slide 11` [Part 02. Bad `dc` Passing *by Value*](https://ensemble.reed.edu/Watch/Yr6s8TLt) *04m15s*  
`Slide 17` [Part 03. Two Container Classes](https://ensemble.reed.edu/Watch/Hb34RxEc) *06m30s*  
`Slide 23` [Part 04. Copy Constructor](https://ensemble.reed.edu/Watch/b9RNg56G) *08m15s*  
`Slide 31` [Part 05. Copy Assignment](https://ensemble.reed.edu/Watch/q9GRz78P) *05m30s*  
`Slide 34` [Part 06. Move Assignment](https://ensemble.reed.edu/Watch/a7M2Lie3) *05m45s*  
`Slide 40` [Part 07. Move Constructor](https://ensemble.reed.edu/Watch/t8P7Ejp6) *03m15s*  
`Slide 45` [Part 08. All Four](https://ensemble.reed.edu/Watch/q5NMw37A) *09m45s*  
`Slide 62` [Part 09. `dc` Revisted; Week 11 Preview](https://ensemble.reed.edu/Watch/p4F3CoGs) *03m00s*  


## Overview of the lecture

Today's lecture works to address a problem introduced in the code
for a *slightly modified* `dc`, found in `samples/Stck_p`. The
mistake there is that the helper function I added passes a `Stck` by
value, rather than by reference. The code says:

    void output_top(Stck s) {
      if (!s.is_empty()) {
        std::cout << s.top() << std::endl;
      }
    }

This introduces a bug because the default copy constructor performs
a *shallow copy* of the array referenced by `s`, and then the 
destructor calls `delete` on it when `output_top` returns. Today's
lecture works to explain what I just said in that last sentence.
It does so by explaining copy constructors, shallow copying, deep
copying, and more. Ultimately, it ends by fixing this bug like so:

    void output_top(Stck& s) {
      if (!s.is_empty()) {
        std::cout << s.top() << std::endl;
      }
    }

where `Stck s` is now passed by reference (and so is not copied).

Along the way you learn about *copy* and *move* constructors,
*copy* and *move* assignment operators, and R-value references.

## A word on the `cm` sample folder

The code in `samples/cm` was what I used to verify that my
understanding of these concepts was correct. In it, it defines
two different object classes

    class V {
      int x;
      V(int x0) : x {x0} {}
      ...
    }
 
    class R P
      int* a;
      V(int x0) : a { new int[1]; } { a[0] = x0; }
      ...
    }

and works to develop their move/copy members according to the
lecture. The code for `cm_array.cc` and `cm_array_debug.cc` are
purposely broken. The code for `cm_array_fixed.cc` fixes those.



