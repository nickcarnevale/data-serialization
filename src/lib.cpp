#include <vector>
#include <stdio.h>
#include "pack109.hpp"

// -----------------------
// PACK109_BOOL
// -----------------------

//given
vec pack109::serialize(bool item) {
  vec bytes;
  if (item == true) {
    bytes.push_back(PACK109_TRUE);
  } else {
    bytes.push_back(PACK109_FALSE);
  }
  return bytes;
}

//given
bool pack109::deserialize_bool(vec bytes) {
  if (bytes.size() < 1) {
     throw;
  }

  if (bytes[0] == PACK109_TRUE) {
    return true;
  } else if (bytes[0] == PACK109_FALSE) {
    return false;
  } else {
    throw;
  }
}

// -----------------------
// PACK109_U8
// -----------------------

//given
vec pack109::serialize(u8 item) {
  vec bytes;
  bytes.push_back(PACK109_U8);
  bytes.push_back(item);
  return bytes;
}

//given
u8 pack109::deserialize_u8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_U8) {
    return bytes[1];
  } else {
    throw;
  }
}

// -----------------------
// PACK109_U32
// -----------------------

vec pack109::serialize(u32 item) {
  vec bytes;
  bytes.push_back(PACK109_U32);
  //if u8 is 1 byte u32 is 4 bytes
  //need to iterate through each bytes passing one at a time
  for (int i = 0; i < 4; i++) {
    bytes.push_back((item >> (i * 8)) & 0xFF); // 0XFF is a mask
  }
  return bytes;
}

u32 pack109::deserialize_u32(vec bytes) {
  if (bytes.size() < 5) {
    throw;
  }
  u32 item = 0;
  if (bytes[0] == PACK109_U32) {
    int j = 0;
    //need to iterate through those bytes backwards because they were serialized backwards and add them to item
    for (int i = 4; i > 0; i--) {
      item |= (u32) bytes[i] << (24 - j * 8);
      j++;
    }
    return item;
  } else {
    throw;
  }
}

// -----------------------
// PACK109_U64
// -----------------------


vec pack109::serialize(u64 item) {
  vec bytes;
  bytes.push_back(PACK109_U64);
  //same loop as u32 but for 8 bytes not 4
  for (int i = 0; i < 8; i++) {
    bytes.push_back((item >> (i * 8)) & 0xFF);
  }
  return bytes;
}

u64 pack109::deserialize_u64(vec bytes) {
  if (bytes.size() < 9) {
    throw;
  }
  u64 item = 0;
  if (bytes[0] == PACK109_U64) {
    int j = 0;
    for (int i = 8; i > 0; i--) {
      item |= (u64) bytes[i] << (56 - j * 8);
      j++;
    }
    return item;
  } else {
    throw;
  }
}


// -----------------------
// PACK109_I8
// -----------------------

vec pack109::serialize(i8 item) {
  vec bytes;
  bytes.push_back(PACK109_I8);
  //cast the i8 to a u8
  bytes.push_back((u8)item);
  return bytes;
}

i8 pack109::deserialize_i8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_I8) {
    //for the return cast the u8 back to an i8
    return (i8) bytes[1];
  } else {
    throw;
  }
}


// -----------------------
// PACK109_I32
// -----------------------

vec pack109::serialize(i32 item) {
  vec bytes;
  bytes.push_back(PACK109_I32);
  //same as u32 and cast to u8
  for (int i = 0; i < 4; i++) {
    bytes.push_back((u8)((item >> (i * 8)) & 0xFF));
  }
  return bytes;
}

i32 pack109::deserialize_i32(vec bytes) {
  if (bytes.size() < 5) {
    throw;
  }
  i32 item = 0;
  if (bytes[0] == PACK109_I32) {
    int j = 0;
    for (int i = 4; i > 0; i--) {
      //cast back to i32
      item |= (i32) bytes[i] << (24 - j * 8);
      j++;
    }
    return item;
  } else {
    throw;
  }
}


// -----------------------
// PACK109_I64
// -----------------------

vec pack109::serialize(i64 item) {
  vec bytes;
  bytes.push_back(PACK109_I64);
  //same as u64
  for (int i = 0; i < 8; i++) {
    bytes.push_back((u8)((item >> (i * 8)) & 0xFF));
  }
  return bytes;
}

i64 pack109::deserialize_i64(vec bytes) {
  if (bytes.size() < 9) {
    throw;
  }
  i64 item = 0;
  if (bytes[0] == PACK109_I64) {
    int j = 0;
    for (int i = 8; i > 0; i--) {
      //cast back to i64
      item |= (i64) bytes[i] << (56 - j * 8);
      j++;
    }
    return item;
  } else {
    throw;
  }
}


// -----------------------
// PACK109_F32
// -----------------------


vec pack109::serialize(f32 item) {
  //inititally cast the f32 to an unsigned int*
  unsigned int* f32_pointer = (unsigned int*) (&item);
  vec bytes;
  bytes.push_back(PACK109_F32);
  for (int i = 0; i < 4; i++) {
    //same as u32
    bytes.push_back((u8)((*f32_pointer >> (i * 8)) & 0xFF));
  }
  return bytes;
}

f32 pack109::deserialize_f32(vec bytes) {
  if (bytes.size() < 5) {
    throw;
  }
  u32 item = 0;
  if (bytes[0] == PACK109_F32) {
    int j = 0;
    for (int i = 4; i > 0; i--) {
      item |= (u32) bytes[i] << (24 - j * 8);
      j++;
    }
    //cast the u32 to a f32
    f32* de_f32 = (f32*) (&item);
    return *de_f32;
  } else {
    throw;
  }
}


// -----------------------
// PACK109_F64
// -----------------------

//same as f32 but for 4 more bytes
vec pack109::serialize(f64 item) {
  u64* f64_pointer = (u64*) (&item);
  vec bytes;
  bytes.push_back(PACK109_F64);
  for (int i = 0; i < 8; i++) {
    bytes.push_back((u8)((*f64_pointer >> (i * 8)) & 0xFF));
  }
  return bytes;
}

//same as f32 but for 4 more bytes
f64 pack109::deserialize_f64(vec bytes) {
  if (bytes.size() < 9) {
    throw;
  }
  u64 item = 0;
  if (bytes[0] == PACK109_F64) {
    int j = 0;
    for (int i = 8; i > 0; i--) {
      item |= (u64) bytes[i] << (56 - j * 8);
      j++;
    }
    f64* de_f64 = (f64*) (&item);
    return *de_f64;
    return item;
  } else {
    throw;
  }
}


// ------------------------
// PACK109_S8 & PACK109_S16
// ------------------------

vec pack109::serialize(string item){
  vec bytes;
  if(item.size() < 256){
    bytes.push_back(PACK109_S8);
    //push the size
    bytes.push_back((u8)item.size()); // YYYYYYYY is a 8-bit unsigned integer which represents the length of the data
    //loop through the string and push each char
    for(int i = 0; i < item.size(); i++){
      bytes.push_back(item[i]);
    }
  }else if(item.size() < 65536){
    bytes.push_back(PACK109_S16);
    u32 len = (u32) item.size();
    //push the size in 2 bytes
    bytes.push_back((u8)(len >> 8));    
    bytes.push_back((u8)len);
    //loop through the string and push each char
    for (int i = 0; i < item.size(); i++) {
      bytes.push_back((u8)item[i]);
    }
  }else{
    throw;
  }
  return bytes;
}

string pack109::deserialize_string(vec bytes){
  if(bytes.size() < 3) {
      throw;
  }
  string item = "";
  if(bytes[0] == PACK109_S8){
    int len = bytes[1];
    for(int i = 2; i < (len + 2); i++){
      item += bytes[i];
    }
  }else if(bytes[0] == PACK109_S16){
    int len = (bytes[1]<<8) | bytes[2];
    for(int i = 3; i < (len + 3); i++){
      item += bytes[i];
    }
  }
  return item;
}


// ------------------------
// PACK109_A8 / A16
// ------------------------

//method to split vectors arrays to make it easier to deserialize
vec slice(vec& bytes, int start, int end) {
  vec result;
  for (int i = start; i < end; i++){
    result.push_back(bytes[i]);
  }
  return result;
}

vec pack109::serialize(std::vector<u8> item){
  vec bytes;
  if(item.size() < 256){
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
    for(int i = 0; i < item.size(); i++){ // goes through each byte in array
      vec temp = serialize(item[i]);  //serializes each byte
      for(int j = 0; j < temp.size(); j++){ // addes each component of the vector to the byte
        bytes.push_back(temp[j]);
      }
    }
  }else if (item.size() < 65536) {
    bytes.push_back(PACK109_A16);
    u32 item_length = (u32)item.size();
    bytes.push_back((u8)(item_length >> 8));
    bytes.push_back((u8)(item_length));
    for (int i = 0; i < item.size(); i++) {
      vec element = serialize(item[i]);
      bytes.insert(end(bytes), begin(element), end(element));
    }
  } else {
    throw;
  }
  return bytes;
}

std::vector<u8> pack109::deserialize_vec_u8(vec bytes){
  if(bytes.size() < 3) {
    throw;
  }
  int el_size = 2;
  std::vector<u8> result;
  if(bytes[0] == PACK109_A8) {
    int size = el_size * bytes[1];
    for (int i = 2; i < (size + 2); i += el_size) {
      vec sub_vec = slice(bytes, i, i + el_size);
      u64 element = deserialize_u8(sub_vec);
      result.push_back(element);
    }
  } else if(bytes[0] == PACK109_A16) {
    int size = el_size * (((int)bytes[1])<<8 | (int)bytes[2]);
    for(int i = 2; i < (size + 2); i += el_size) {
      vec sub_vec = slice(bytes, i + 1, i + el_size);
      u64 element = deserialize_u8(sub_vec);
      result.push_back(element);
    }
  }
  return result;
}


vec pack109::serialize(std::vector<u64> item){
  vec bytes;
  if(item.size() < 256){
    bytes.push_back(PACK109_A8);
    u8 size = (u8) item.size();
    bytes.push_back(size);
    for(int i = 0; i < item.size(); i++){
      vec temp = serialize(item[i]);
      for(int j = 0; j < temp.size(); j++){
        bytes.push_back(temp[j]);
      }
    }
  }else if(item.size() < 65536){
    bytes.push_back(PACK109_A16);
    u32 item_length = (u32)item.size();
    bytes.push_back((u8)(item_length >> 8));
    bytes.push_back((u8)(item_length));
    for (int i = 0; i < item.size(); i++) {
      vec element = serialize(item[i]);
      bytes.insert(end(bytes), begin(element), end(element));
    }
  } else {
    throw;
  }
  return bytes;
}

std::vector<u64> pack109::deserialize_vec_u64(vec bytes){
  if(bytes.size() < 3) {
    throw;
  }
  int element_size = 9;
  std::vector<u64> result;
  if(bytes[0] == PACK109_A8) {
    int size = element_size * bytes[1]; // each element is 9 bytes long
    for (int i = 2; i < (size + 2); i += element_size) {
      vec sub_vec = slice(bytes, i, i + element_size);
      u64 element = deserialize_u64(sub_vec);
      result.push_back(element);
    }
  } else if(bytes[0] == PACK109_A16) {
    int size = element_size * (((int)bytes[1])<<8 | (int)bytes[2]);
    for(int i = 2; i < (size + 2); i += element_size) {
      vec sub_vec = slice(bytes, i + 1, i + element_size);
      u64 element = deserialize_u64(sub_vec);
      result.push_back(element);
    }
  }
  return result;
}

vec pack109::serialize(std::vector<f64> item){
  vec bytes;
  if (item.size() < 256) {
    bytes.push_back(PACK109_A8);
    u8 size = (u8)item.size();
    bytes.push_back(size);
    for (int i = 0; i < item.size(); i++) {
      vec temp = serialize(item[i]);
      for (int j = 0; j < temp.size(); j++) {
        bytes.push_back(temp[j]);
      }
    }
  } else if (item.size() < 65536) {
    bytes.push_back(PACK109_A16);
    u32 item_length = (u32)item.size();
    bytes.push_back((u8)(item_length >> 8));
    bytes.push_back((u8)(item_length));
    for (int i = 0; i < item.size(); i++) {
      vec element = serialize(item[i]);
      bytes.insert(end(bytes), begin(element), end(element));
    }
  } else {
    throw;
  }
  return bytes;
}

std::vector<f64> pack109::deserialize_vec_f64(vec bytes){
  if(bytes.size() < 3) {
    throw;
  }
  int element_size = 9;
  std::vector<f64> result;
  if(bytes[0] == PACK109_A8) {
    int size = element_size * bytes[1];
    for (int i = 2; i < (size + 2); i += element_size) {
      vec sub_vec = slice(bytes, i, i + element_size);
      u64 element = deserialize_f64(sub_vec);
      result.push_back(element);
    }
  } else if(bytes[0] == PACK109_A16) {
    int size = element_size * (((int)bytes[1])<<8 | (int)bytes[2]);
    for(int i = 2; i < (size + 2); i += element_size) {
      vec sub_vec = slice(bytes, i + 1, i + element_size);
      u64 element = deserialize_f64(sub_vec);
      result.push_back(element);
    }
  }
  return result;
}

vec pack109::serialize(std::vector<string> item){
  vec bytes;
  if (item.size() < 256) {
    bytes.push_back(PACK109_A8);
    u8 size = (u8)item.size();
    bytes.push_back(size);
    for (int i = 0; i < item.size(); i++) {
      vec temp = serialize(item[i]);
      for (int j = 0; j < temp.size(); j++) {
        bytes.push_back(temp[j]);
      }
    }
  } else if (item.size() < 65536) {
    bytes.push_back(PACK109_A16);
    u32 item_length = (u32)item.size();
    bytes.push_back((u8)(item_length >> 8));
    bytes.push_back((u8)(item_length));
    for (int i = 0; i < item.size(); i++) {
      vec element = serialize(item[i]);
      bytes.insert(end(bytes), begin(element), end(element));
    }
  } else {
    throw;
  }
  return bytes;
}


std::vector<string> pack109::deserialize_vec_string(vec bytes){
  if(bytes.size() < 3) {
    throw;
  }
  int element_size = 9;
  std::vector<string> result;
  if(bytes[0] == PACK109_A8) {
    int size = element_size * bytes[1];
    for (int i = 2; i < (size + 2); i += element_size) {
      vec sub_vec = slice(bytes, i, i + element_size);
      string element = deserialize_string(sub_vec);
      result.push_back(element);
    }
  } else if(bytes[0] == PACK109_A16) {
    int size = element_size * (((int)bytes[1])<<8 | (int)bytes[2]);
    for(int i = 2; i < (size + 2); i += element_size) {
      vec sub_vec = slice(bytes, i + 1, i + element_size);
      string element = deserialize_string(sub_vec);
      result.push_back(element);
    }
  }
  return result;
}


// ------------------------
// PACK109_M8
// ------------------------

vec pack109::serialize(struct Person item){
  vec bytes;
  bytes.push_back(PACK109_M8);
  bytes.push_back(0x01); // 1 k/v pair
  string p = "Person";
  vec person = serialize(p); 
  bytes.insert(end(bytes), begin(person), end(person));

  bytes.push_back(PACK109_M8);
  bytes.push_back(0x03); // 3 k/v pairs
  
  //1st pair
  //key
  string a = "age"; 
  vec age = serialize(a);
  bytes.insert(end(bytes), begin(age), end(age));
  //value
  vec agev = serialize(item.age);
  bytes.insert(end(bytes), begin(agev), end(agev));

  //second pair
  //key
  string h = "height";
  vec height = serialize(h);
  bytes.insert(end(bytes), begin(height), end(height));
  //value
  vec heightv = serialize(item.height);
  bytes.insert(end(bytes), begin(heightv), end(heightv));

  //third pair
  //key
  string n = "name";
  vec name = serialize(n);
  bytes.insert(end(bytes), begin(name), end(name));
  //value
  vec namev = serialize(item.name);
  bytes.insert(end(bytes), begin(namev), end(namev));
  
  return bytes;
}

struct Person pack109::deserialize_person(vec bytes){
  string person;
  u8 age;
  f32 height;
  string name;
  
  if(bytes.size() < 43){
    throw;
  }
  vec vec_person = slice(bytes,2,10);
  person = deserialize_string(vec_person);
  if(person != "Person"){
    throw;
  }

  vec vec_age = slice(bytes,17, 19);
  age = deserialize_u8(vec_age);

  vec vec_height = slice(bytes, 27, 32);
  height = deserialize_f32(vec_height);

  vec vec_name = slice(bytes,38,43);
  name = deserialize_string(vec_name);

  Person person_m8{age, height, name};
  return person_m8;

}

//Serializes Correctly
vec pack109::serialize(struct File item){
  vec bytes;
  bytes.push_back(PACK109_M8);
  bytes.push_back(0x01); // 1 k/v pair
  string p = "File";
  vec file = serialize(p); 
  bytes.insert(end(bytes), begin(file), end(file));

  bytes.push_back(PACK109_M8);
  bytes.push_back(0x02); // 2 k/v pairs
  
  //1st pair
  //key
  string n = "name"; 
  vec name = serialize(n);
  bytes.insert(end(bytes), begin(name), end(name));
  //value
  vec namev = serialize(item.name);
  bytes.insert(end(bytes), begin(namev), end(namev));

  //second pair
  //key
  string b = "bytes";
  vec by = serialize(b);
  bytes.insert(end(bytes), begin(by), end(by));
  
  //value
  vec byv = serialize(item.bytes);
  bytes.insert(end(bytes), begin(byv), end(byv));
  
  return bytes;
}

struct File pack109::deserialize_file(vec bytes){
  string file;
  string name;
  vec returnBytes;
  int count = 0;
  
  if(bytes.size() < 34){
    throw;
  }
  vec vec_file = slice(bytes,2,8);
  file = deserialize_string(vec_file);
  if(file != "File"){
    throw;
  }
  count = 16 + bytes[17] + 2;
  vec vec_name = slice(bytes,16,count);
  name = deserialize_string(vec_name);
  count += 7;
  int end = count + 1 + bytes[count];
  vec vec_bytes = slice(bytes,count,end);
  returnBytes = deserialize_vec_u8(vec_bytes);

  File file_m8{name, returnBytes};
  
  return file_m8;

}

struct Request pack109::deserialize_request(vec bytes){
  string request;
  string name;
  int count = 0;
  
  if(bytes.size() < 24){
    throw;
  }
  vec vec_file = slice(bytes,2,11);
  request = deserialize_string(vec_file);
  if(request != "Request"){
    throw;
  }
  count = 19 + bytes[20] + 2;
  vec vec_name = slice(bytes,19,count);
  name = deserialize_string(vec_name);

  Request request_m8{name};
  
  return request_m8;
}

void pack109::printVec(vec &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}