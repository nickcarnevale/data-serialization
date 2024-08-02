#include <stdexcept>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include"pack109.hpp"

template <class T>
int test(const char* label, T lhs, T rhs) {
  printf("%s: ", label);
  if ((T)lhs==(T)rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs=%x\n", lhs);
    printf("  rhs=%x\n", rhs);
    exit(1);
  }
}

//special class to test the person function because we can't use test()
int testPerson(const char* label, struct Person lhs, struct Person rhs){
  printf("%s: ", label);
  if(lhs.age == rhs.age && lhs.height == rhs.height && lhs.name == rhs.name){
    printf("Passed\n");
    return 1;
  }
  else {
    printf("Failed\n");
    exit(1);
  }
}

//test file
int testFile(const char* label, struct File lhs, struct File rhs){
  printf("%s: ", label);
  if(lhs.name == rhs.name && lhs.bytes == rhs.bytes){
    printf("Passed\n");
    return 1;
  }
  else {
    printf("Failed lhs:%s, rhs:%s\n", lhs.bytes, rhs.bytes);
    exit(1);
  }
}

int testRequest(const char* label, struct Request lhs, struct Request rhs){
  printf("%s: ", label);
  if(lhs.name == rhs.name){
    printf("Passed\n");
    return 1;
  }
  else {
    printf("Failed lhs:%s, rhs:%s\n", lhs.name.c_str(), rhs.name.c_str());
    exit(1);
  }
}

int testvec(const char* label, vec lhs, vec rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs="); pack109::printVec(lhs); printf("\n");
    printf("  rhs="); pack109::printVec(rhs); printf("\n");
    exit(1);
  }
}


int main() {

// -----------------------
// PACK109_TRUE
// -----------------------

  vec v1{0xa0};
  vec bytes1 = pack109::serialize(true);
  testvec("Test 1 - true ser", bytes1, v1);

  bool bool_true = pack109::deserialize_bool(bytes1);
  test("Test 2 - true de", bool_true, true);
 

// -----------------------
// PACK109_FALSE
// -----------------------

  vec v2{0xa1};
  vec bytes2 = pack109::serialize(false);
  testvec("Test 3 - false ser", bytes2, v2);

  bool bool_false = pack109::deserialize_bool(bytes2); 
  test("Test 4 - false de", bool_false, false);


// -----------------------
// PACK109_U8
// -----------------------

  u8 item_u8 = 0x42;
  vec v3{0xa2, 0x42};  // This test is wrong on purpose to demonstrate a failed test. Fix it.
  vec bytes_u8 = pack109::serialize(item_u8);
  testvec("Test 5 - u8 ser", bytes_u8, v3);
  
  u8 int_u8 = pack109::deserialize_u8(bytes_u8);  
  test("Test 6 - u8 de", int_u8, item_u8);


// -----------------------
// PACK109_U32
// -----------------------

  u32 item_u32 = 0x12345678;
  vec v4{0xa3, 0x78, 0x56, 0x34, 0x12};
  vec bytes_u32 = pack109::serialize(item_u32);
  testvec("Test 7 - u32 ser", bytes_u32, v4);

  u32 int_u32 = pack109::deserialize_u32(bytes_u32);
  test("Test 8 - u32 de", int_u32, item_u32);


// -----------------------
// PACK109_U64
// -----------------------

  u64 item_u64 = 0x123456789abcdef0;
  vec v5{0xa4, 0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12};
  vec bytes_u64 = pack109::serialize(item_u64);
  testvec("Test 9 - u64 ser", bytes_u64, v5);

  u64 int_u64 = pack109::deserialize_u64(bytes_u64);
  test("Test 10 - u64 de", int_u64, item_u64);

// -----------------------
// PACK109_I8
// -----------------------

  i8 item_i8 = 0x80;
  vec v6{0xa5, 0x80}; 
  vec bytes_i8 = pack109::serialize(item_i8);
  testvec("Test 11 - i8 ser", bytes_i8, v6);
  
  i8 int_i8 = pack109::deserialize_i8(bytes_i8);  
  test("Test 12 - i8 de", int_i8, item_i8);

// -----------------------
// PACK109_I32
// -----------------------

  i32 item_i32 = 0xFFFFFFF0;
  vec v7{0xa6, 0xF0, 0xFF, 0xFF, 0xFF}; 
  vec bytes_i32 = pack109::serialize(item_i32);
  testvec("Test 13 - i32 ser", bytes_i32, v7);
  
  i32 int_i32 = pack109::deserialize_i32(bytes_i32);  
  test("Test 14 - i32 de", int_i32, item_i32);

// -----------------------
// PACK109_I64
// -----------------------

  i64 item_i64 = 0x7F6A5B4C3D2E1F0F;
  vec v8{0xa7, 0x0F, 0x1F, 0x2E, 0x3D, 0x4C, 0x5B, 0x6A, 0x7F}; 
  vec bytes_i64 = pack109::serialize(item_i64);
  testvec("Test 15 - i64 ser", bytes_i64, v8);
  
  i64 int_i64 = pack109::deserialize_i64(bytes_i64);  
  test("Test 16 - i64 de", int_i64, item_i64);


// -----------------------
// PACK109_F32
// -----------------------

  f32 item_f32 = 3.141592;
  vec v9{0xa8, 0xd8, 0x0f, 0x49, 0x40}; 
  vec bytes_f32 = pack109::serialize(item_f32);
  testvec("Test 17 - f32 ser", bytes_f32, v9);
  
  f32 float_f32 = pack109::deserialize_f32(bytes_f32); 
  test("Test 18 - f32 de", float_f32, item_f32);


// -----------------------
// PACK109_F64
// -----------------------

  f64 item_f64 = 3.14159265358979323846;
  vec v10{0xa9, 0x18, 0x2d, 0x44, 0x54, 0xfb, 0x21, 0x09, 0x40}; 
  vec bytes_f64 = pack109::serialize(item_f64);
  testvec("Test 19 - f64 ser", bytes_f64, v10);
  
  f64 float_f64 = pack109::deserialize_f64(bytes_f64); 
  test("Test 20 - f64 de", float_f64, item_f64);

// -----------------------
// PACK109_S8
// -----------------------

  string item_s8 = "NickCarnevaleCSE109Program4";
  vec v11{0xaa, 0x1b, 0x4e, 0x69, 0x63, 0x6b, 0x43, 0x61, 0x72, 0x6e, 0x65, 0x76, 0x61, 0x6c, 0x65, 0x43, 0x53, 0x45, 0x31, 0x30, 0x39, 0x50, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x34}; 
  vec bytes_s8 = pack109::serialize(item_s8);
  testvec("Test 21 - s8 ser", bytes_s8, v11);
  
  string string_s8 = pack109::deserialize_string(bytes_s8); 
  test("Test 22 - s8 de", string_s8, item_s8);

// ------------------------
// PACK109_A8
// ------------------------

  std::vector<u8> item_a8 {0x01,0x02,0x03,0x04,0x05};
  vec bytes_a8 = pack109::serialize(item_a8);
  vec v12{0xac, 0x05, 0xa2, 0x01, 0xa2, 0x02, 0xa2, 0x03, 0xa2, 0x04, 0xa2, 0x05}; 
  testvec("Test 23 - a8 ser", bytes_a8, v12); 

  std::vector<u8> array_a8 = pack109::deserialize_vec_u8(bytes_a8);
  test("Test 24 - a8 de", array_a8, item_a8);


// ------------------------
// PACK109_M8
// ------------------------

  Person item_m8;
  item_m8.age = 10;
  item_m8.height = 3.4;
  item_m8.name = "Ann";
  
  vec bytes_m8 = pack109::serialize(item_m8);
  vec v13{0xae, 0x1, 0xaa, 0x06, 0x50, 0x65, 0x72, 0x73, 0x6f, 0x6e, 0xae, 0x03, 0xaa, 0x03, 0x61, 0x67, 0x65, 0xa2, 0x0a, 0xaa, 0x06, 0x68, 0x65, 0x69, 0x67, 0x68, 0x74, 0xa8, 0x9a, 0x99, 0x59, 0x40, 0xaa, 0x04, 0x6e, 0x61, 0x6d, 0x65, 0xaa, 0x03, 0x41, 0x6e, 0x6e};
  testvec("Test 25 - m8 ser", bytes_m8, v13); 

  Person person_m8 = pack109::deserialize_person(bytes_m8);
  testPerson("Test 26 - m8 de", person_m8, item_m8);


  File file;
  file.name = "file.txt";
  vec bytes{0x48, 0x65, 0x6C, 0x6C, 0x6F};
  file.bytes = bytes;
  vec bytes_file = pack109::serialize(file);
  vec v15 = {0xAE, 0x01, 0xAA, 0x04, 0x46, 0x69, 0x6C, 0x65, 0xAE, 0x02, 0xAA, 0x04, 0x6E, 0x61, 0x6D, 0x65, 0xAA, 0x08, 0x66, 0x69, 0x6C, 0x65, 0x2E, 0x74, 0x78, 0x74, 0xAA, 0x05, 0x62, 0x79, 0x74, 0x65, 0x73, 0xAC, 0x05, 0xA2, 0x48, 0xA2, 0x65, 0xA2, 0x6C, 0xA2, 0x6C, 0xA2, 0x6F};
  testvec("Test File Serialization", bytes_file, v15); 

  File fileFromMethods = pack109::deserialize_file(bytes_file);
  testFile("Test File Deserialization", fileFromMethods, file);


  //Deserialize

  Request request;
  request.name = "file.txt";
  vec v16 = {0xAE, 0x01, 0xAA, 0x07, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0xAE, 0x01, 0xAA, 0x04, 0x6E, 0x61, 0x6D, 0x65, 0xAA, 0x08, 0x66, 0x69, 0x6C, 0x65, 0x2E, 0x74, 0x78, 0x74};

  Request requestFromMethods = pack109::deserialize_request(v16);
  testRequest("Test Request Deserialization", requestFromMethods, request);



  return 0;
}
