#include "minunit.h"
#include <lcthw/hashmap.h>
#include <assert.h>
#include <lcthw/bstrlib.h>

Hashmap *map = NULL;
struct tagbstring key = bsStatic("key");
struct tagbstring value_a = bsStatic("value a");
struct tagbstring value_b = bsStatic("value b");


int main()
{
    int rc = 0;
    bstring result;

    map = Hashmap_create(NULL, NULL);

    // put (key, value_a)
    rc = Hashmap_set(map, &key, &value_a);
    check(rc == 0, "Failed to set &key");
    result = Hashmap_get(map, &key);
    check(result == &value_a, "Wrong value for key.");

    // put (key, value_b)....
    rc = Hashmap_set(map, &key, &value_b);
    check(rc == 0, "Failed to set &key");
    result = Hashmap_get(map, &key);
    check(result == &value_a, "Wrong value for key.");

    // But... get(key) still returns value_a

    Hashmap_destroy(map);

 error:
    return 0; // always return this
}
