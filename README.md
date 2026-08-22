# Tool Lib

<p>
My own custom Library for me to use my own custom memory allocator for my own c projects.
Currently this only implements basic types like Strings and Vectors, however more gets added as I need it
</p>
---

## Library Usage Notes

### tlVectors

<p>
For most constructors that I have specified (not really a whole lot but there are some). These will have their own inbuilt constructor/destructor (mostly namely for tlVectors)
</p>

<p>
For instance this is how a tlVector is Destructed
</p>
```c
int main()
{
 // This argument here takes the void* pData, length and the dataType size.
 tlVector newVector = tlVecCreate((float[]){1.0f, 2.0f}, 2, sizeof(float));
 tlVecClear(&newVector);
 return 1;
}
```

### Memory Access

<p>
This library uses a bump allocator with a linked list with responsibilities delegated for dynamic and static variables separated.
For DynamicAllocations there will be its own allocator defined for the function as shown in the `tlVecCreate` above. However you can do manual dynamic allocations for features of your own. as shown below.
</p>

```c
int main()
{
 // For a dynamic list for instance
  const int64_t dynamicList* = tlNewDynamicAlloc(sizeof(int64_t));

 // If you were to increase the size can simply do this
 int8_t previousSize = 1;
 int8_t newSize = 3;
 const int64_t dynamicListBigger = tlDynamicAlloc(newSize, previousSize);

 // tlDynamicAlloc(newSize, 0) is the same as tlNewDynamicAlloc. just a clearer way of doing it
 // For static allocations e.g. a constant project state
 const int64_t *staticNumber = tlStaticAlloc(sizeof(int64_t));
 // You are able to allocate dynamic things in here, but dynamic types expand their own buffer and allocate extra memory depending on size reallocations. e.g. Vectors allocate double the size of the contents on reallocation.
 // allocating them in here means you're more likely to force the entire memory buffer to move, which is just slower.
 return 1;
}
```
