# plalloc
PLALLOC - dynamic linear pool allocator, based on unrolled linked list

from [allocator source file](plalloc.h) : ```
 * This allocator is my only work, that was evolved during years and years in
 * my head and in my different projects, and now... it's here. Headeronly,
 * easy to add in project and use, dependent only on the stdlib and 
 * c89threads(optional), dynamic linear allocator lib :D

# commenntary : now i know that this is similar with how unrolled linked list is working...
# anyways, this may be not the perfect, but good enough implementation. Some uncompatability eith C89
# may be optionally fixed too

 * To add this in your project, you may also need to create empty .c file with 
 * this content : ```
 * #define PLALLOC_IMPLEMENTATION
 * #include "plalloc.h"
 * ```
 * Do this only once. You may also come with different approaches, like include
 * this text in exact same rder directly to your main.c, or miniaudio.c... Does
 * not matter.
 *
 * This project activates all SANITY_CHECK() macro, if you define PLALLOC_DEBUG
 * above `#include "plalloc.h"` in your implementation file. This is useful for
 * debug builds of your program to catch bad things early and with conclusion 
 * about where(in allocator) and why it's happened. Altrough, it will make this
 * allocator a bit slower.
 * Without PLALLOC_DEBUG, some assertions will still be checked, but they are rare,
 * and located at the end of all fun, when everything may be already very broken. 
 *
 * "c89threads.h" is used by this allocator to make it threadsafe in multithreaded
 * enviroment. You can get rid of this dependency by defining PLALLOC_OMIT_THREADSAFETY
 * above `#include "plalloc.h"`.

# commentary : yeah, no c89 support is guaranteed, but c89threads are used instead of pthreads or c11 threads :D
# btw, this lib is very good in what it does, and it does it pretty crossplatformy.
# anyway, this lib is OPTIONAL, and it's included by default OBLY for threadsafety, that may be easly disabled at compiletime

 *
 * And for extra crazy guys : 
 * You can change default malloc() and free() functions, used by this
 * allocator, by redefining MEM_ALLOC(), MEM_FREE() and MEM_CHECK()
 * macros, inside source file with defined PLALLOC_IMPLEMENTATION, 
 * above `#include "plalloc.h"`!
 *
 * Also, you can direcly edit this file and macros values for your own needs :)
 * Altrogh be careful, some values, like PAGE_SIZE_MIN and ITEMS_COUNT_DEFAULT 
 * must not be setted to ultra crazy low, or ultra crazy high values, since allcator
 * code does not make checks for that.
```
