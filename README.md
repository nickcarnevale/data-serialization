# Overview

In the table below I've listed the 16 available objects in the Pack109 serialization format.

| Type                    | Tag (Hex) | 
| ----------------------- | --------- |
| Bool (true)             |   0xa0    |
| Bool (false)            |   0xa1    |
| Unsigned 8-bit Integer  |   0xa2    |
| Unsigned 32-bit Integer |   0xa3    |
| Unsigned 64-bit Integer |   0xa4    |
| Signed 8-bit Integer    |   0xa5    |
| Signed 32-bit Integer   |   0xa6    |
| Signed 64-bit Integer   |   0xa7    |
| 32-bit Floating Number  |   0xa8    |
| 64-bit Floating Number  |   0xa9    |
| 8-bit String            |   0xaa    |
| 16-bit String           |   0xab    |
| 8-bit Array             |   0xac    |
| 16-bit Array            |   0xad    |
| 8-bit Map               |   0xae    |
| 16-bit Map              |   0xaf    |

#### Notation Key

```
one byte:
┌────────┐
│        │
└────────┘

a variable number of bytes:
╔════════╗
║        ║
╚════════╝

variable number of objects stored in Pack109 format:
╭╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮
┆                 ┆
╰╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╯
```

#### Bool

Bool is for serializing `true` and `false` boolean values. Although we can represent these values in one bit in C and C++, we have to use 8 bits to represent them in our serialized format.

```
true:
┌────────┐
│  0xa0  │
└────────┘ 

false:
┌────────┐
│  0xa1  │
└────────┘ 
```

#### Integers

Integers are for storing signed and unsigned `chars`, `ints`, and `longs`.

```
u8 stores a 8-bit unsigned integer
┌────────┬────────┐
│  0xa2  │ZZZZZZZZ│
└────────┴────────┘ 

u32 stores a 32-bit big-endian unsigned integer
┌────────┬────────┬────────┬────────┬────────┐
│  0xa3  │ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│
└────────┴────────┴────────┴────────┴────────┘ 

u64 stores a 64-bit big-endian unsigned integer
┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
│  0xa4  │ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│
└────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘ 

i8 stores a 8-bit signed integer
┌────────┬────────┐
│  0xa5  │ZZZZZZZZ│
└────────┴────────┘ 

i32 stores a 32-bit big-endian signed integer
┌────────┬────────┬────────┬────────┬────────┐
│  0xa6  │ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│
└────────┴────────┴────────┴────────┴────────┘


i64 stores a 64-bit big-endian signed integer
┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
│  0xa7  │ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│
└────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘

```

#### Floats

Floats are for serializing big-endian IEEE 754 single and double precision floating point numbers like `floats` and `doubles`. Extension of precision from single-precision to double-precision does not lose precision.

```
f32 stores a single-width floating point number
┌────────┬────────┬────────┬────────┬────────┐
│  0xa8  │ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│
└────────┴────────┴────────┴────────┴────────┘

f64 stores a double-width floating point number
┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
│  0xa9  │ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│ZZZZZZZZ│
└────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘
```

#### Strings

Strings are for serializing strings and c-strings. If you want to serialize an array of bytes that aren't meant to represent characters, use an Array instead (see below).

```
s8 stores a byte array whose length is up to (2^8)-1 bytes:
┌────────┬────────┬════════╗
│  0xaa  │YYYYYYYY│  data  ║
└────────┴────────┴════════╝

YYYYYYYY is a 8-bit unsigned integer which represents the length of the data

s16 stores a byte array whose length is up to (2^16)-1 bytes:
┌────────┬────────┬────────┬════════╗
│  0xab  │ZZZZZZZZ│ZZZZZZZZ│  data  ║
└────────┴────────┴────────┴════════╝

ZZZZZZZZZZZZZZZZ is a 16-bit unsigned integer which represents the length of the data
```

#### Arrays

Arrays are for serializing arrays of homogenous datatypes. Each object in the serialized array should be one of the other objects in the Pack109 spec. For example, you can serialize an array of u8s, an array of strings, or even an array of arrays.

```
a8 stores an array whose length is up to (2^8)-1 elements:
┌────────┬────────┬╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮
│  0xac  │YYYYYYYY│    N objects    ┆
└────────┴────────┴╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╯

YYYYYYYY is a 8-bit unsigned integer which represents the length of the data

a16 stores an array whose length is up to (2^16)-1 elements:
┌────────┬────────┬────────┬╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮
│  0xad  │ZZZZZZZZ│ZZZZZZZZ│    N objects    ┆
└────────┴────────┴────────┴╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╯

ZZZZZZZZZZZZZZZZ is a 16-bit unsigned integer which represents the length of the data
```

#### Maps

Maps are for serializing datastructures that can be represented by key-value pairs. This includes associative arrays, structs, and objects.

```
m8 stores a map whose length is upto (2^8)-1 elements
┌────────┬────────┬╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮
│  0xae  │YYYYYYYY│   N*2 objects   ┆
└────────┴────────┴╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╯

YYYYYYYY is a 8-bit unsigned integer which represents the length of the data

m16 stores a map whose length is upto (2^16)-1 elements
┌────────┬────────┬────────┬╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╮
│  0xaf  │ZZZZZZZZ│ZZZZZZZZ│   N*2 objects   ┆
└────────┴────────┴────────┴╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╯

ZZZZZZZZZZZZZZZZ is a 16-bit unsigned integer which represents the length of the data
```

For example, consider the following struct:

```
struct Person {
  char age;
  float height;
  string name;
}
```

You can serialize this into a map of maps. Let's say we have the following values in our struct:

```
struct Person ann = { age: 10, height: 3.4, name: "Ann" };
```

We could serialize this into the following byte vector:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│0xae   // map tag                                                            │
│0x01   // 1 kv pair                                                          │
├─────────────────────────────────────────────────────┬───────────┬───────────┤
│0xaa   // string8 tag                                │           │           │
│0x06   // 6 characters                               │ key       │           │
│Person // the string "Person"                        │           │           │
├─────────────────────────────────────────────────────┼───────────┤  pair 1   │
│0xae   // the value associated with the key is a map │           │           │
│0x03   // 3 kv pairs                                 │           │           │
├──────────────────────────────┬───────────┬──────────┤           │           │
│0xaa   // string8 tag         │           │          │           │           │
│0x03   // 3 characters        │ key       │          │           │           │
│age    // the string "age"    │           │          │           │           │
├──────────────────────────────┼───────────┤ pair 1   │           │           │
│0xa2   // u8 tag              │ value     │          │           │           │
│0x0a   // 10                  │           │          │           │           │
├──────────────────────────────┼───────────┼──────────┤           │           │
│0xaa   // string8 tag         │           │          │ value     │           │
│0x06   // 6 characters        │ key       │          │           │           │
│height // the string "height" │           │          │           │           │
├──────────────────────────────┼───────────┤ pair 2   │           │           │
│0xa8   // f32 tag             │ value     │          │           │           │
│3.4    // float value 3.4     │           │          │           │           │
├──────────────────────────────┼───────────┼──────────┤           │           │
│0xaa   // string8 tag         │           │          │           │           │
│0x04   // 4 characters        │ key       │          │           │           │
│name   // the string "name"   │           │          │           │           │
├──────────────────────────────┼───────────┤ pair 3   │           │           │
│0xaa   // string8 tag         │           │          │           │           │
│0x03   // 3 characters        │ value     │          │           │           │
│Ann    // the string "Ann"    │           │          │           │           │
└──────────────────────────────┴───────────┴──────────┴───────────┴───────────┘           
```

The total length of this byte vector would be 43 bytes.
